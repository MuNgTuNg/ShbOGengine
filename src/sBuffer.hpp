 
//»»»external«««
//glfw/glad
#include <glad/glad.h> //include glad/glad.h instead of glad.c to avoid multiple definitions of functions as glad likes to cry about this
#include <GLFW/glfw3.h> 


#include <iostream>
#include <vector>


 //does not need to be created just yet as i'm not sure how it would be used
 
 //»Constructor«
  //1.generate vertex attribute array             (glGenVertexArrays)
  //2.bind vertex attribute array                 (glBindVertexArray)
  //3.initialise buffer handle                    (glGenBuffers)

//»Member Functions
  //4.bind buffer                                 (glBindBuffer)
  //5.specify usage and data                      (glBufferData)
  //6.set vertex attribute array info for shader  (glVertexAttribPointer)

//»Static incrementing index«
  //7.choose an input slot for shader             (glEnableVertexAttribArray)

//»Destructor«
  //8. unbind buffer and vertex array             (glBindBuffer, glBindVertexArray) <- to zero
  //9.delete vertex array
  //10.delete buffers
  

//»Member variables«
  //buffer handle (GLuint)
  //index of shader input slot (GLuint)
  //buffer data (reference???)

namespace shb{

//index/vertex
class BufferObject{
 public:
  //inits buffer handles (can be array) »[num of buffers, pointer to buffers]
  BufferObject() { 
     //specifies usage of buffer and allows handle to be used »[usage of buffer, buffer handle]
    glGenBuffers(1,&m_Handle);
  }


  void bindBuffer(GLenum bufferType){
    glBindBuffer(bufferType, m_Handle);  
  }


 template<typename T>
//allocates and fills currently bound buffer and specifies usage [DYNAMIC,STATIC,STREAM][DRAW,READ,COPY]
  void fillBuffer(std::vector<T>& data, GLenum arraytype, GLenum drawType){
    glBufferData(arraytype, data.size()*sizeof(GLfloat),&data[0], drawType); 
  }
  

  void unBind(){
    glBindBuffer(GL_ARRAY_BUFFER,0);
  }


  void deleteBuffer(){
    glDeleteBuffers(1,&m_Handle);
  }


 private:
    GLuint m_Handle;

};





class VertexArrayObject{
 public:
    VertexArrayObject() {  //creates a handle for the array object
      glGenVertexArrays(1,&m_Handle);
      
    }


    void bind(){  //selects it for use (should be used after bindng the chosen vertex buffer)
      glBindVertexArray(m_Handle);
    }
    void unBind(){
      glBindVertexArray(0);
    }
    

    virtual void formatSegmentOfArray(int shaderSlot,   //this is used to describe the vertex input
                              GLint amountOfvalues,
                              GLenum typeOfValue,
                              bool normalised,
                              GLsizei stride,
                              const void* offset){
      glVertexAttribPointer(shaderSlot,amountOfvalues,typeOfValue,normalised,stride,offset);
    }


    void setToShaderSlot(int slot){ //sets the input slot for selected values (xyz goes to 0, rgb goes to 1, etc)
      glEnableVertexAttribArray(slot);
    }


    void deleteVAO(){
      glDeleteVertexArrays(1,&m_Handle);
    }


 private:
    GLuint m_Handle;

};

//xyz,rgb.texxtexy
class defaultVAO : public VertexArrayObject{
 public:
       //default format of vertices being initialised
  void init(){

    //xyz
    formatSegmentOfArray(0,3, GL_FLOAT,GL_FALSE, 8* sizeof(float), (void*)0);
    setToShaderSlot(0);
    
    //rgb
    formatSegmentOfArray(1,3, GL_FLOAT,GL_FALSE, 8* sizeof(float), (void*)(3*sizeof(float)));
    setToShaderSlot(1);

    //texx texy
    formatSegmentOfArray(2,2, GL_FLOAT,GL_FALSE, 8* sizeof(float), (void*)(6*sizeof(float)));
    setToShaderSlot(2);
  }
};

}//namespace shb