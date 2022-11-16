#include <sApp.hpp>
#include <glad.c>


namespace shb{


    std::vector<char> createShaderSource(const std::string& filePath){
 //open file at the end of the file (ate) in binary form, and open for input
  char* cwd = get_current_dir_name();

 std::ifstream file;
  file.open(filePath.c_str(), std::ios::ate |  std::ios::binary | std::ios::in );

 //check file is open
  if(!file.is_open()){
     std::cout << cwd;
    std::cout << "Failed to open file\n";
   
  
  }else{
    std::cout <<"Successfully opened file\n" ;
  }
 //save size of file, pointer is at the end of file 
  int size = file.tellg();
  
 //look for the beginning of the file
  file.seekg(0, std::ios::beg);

 //create vector to hold all of the code
  std::vector<char> code(size);
 //read all of the data into the vector (like malloc())
  file.read(code.data(),code.size()); 

 //close the file 
  file.close();

  return code;

}



 GLfloat vertices[] = 
  {
    -0.5f,     -0.5f * float(sqrt(3)) / 3,     0.0f, //lower left
     0.5f,     -0.5f * float(sqrt(3)) / 3,     0.0f, //lower right
     0.0f,      0.5f * float(sqrt(3)) *2/3,    0.0f, //upper

    -0.5f/2,   0.5f * float(sqrt(3)) / 6,     0.0f, //inner left
     0.5f/2,   0.5f * float(sqrt(3)) / 6,     0.0f, //inner right
     0.0f,    -0.5f * float(sqrt(3)) / 3,     0.0f

  
  };

  GLuint indices[] = 
  {
    0, 3, 5, //lower left
    3, 2, 4, //lower right
    5, 4, 1

};


sApp::sApp(){}


void sApp::run(){


_window.initWindow();
_window.makeContextCurrent();

//glad is loaded on current context so it must be after window creation and 
//contextualisation
gladLoadGL();
  
 

// »»» SHADERS «««
 //create shader source code
  //fragShader
  auto fragCode =  createShaderSource("../shaders/fragment_shader.frag");
  const char* fragShaderSource = reinterpret_cast<const char*>(fragCode.data());
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);  //creates handle
  glShaderSource(fragShader, 1, &fragShaderSource, NULL);  //handle, number of strings for source, source code, array of string lengths  
  glCompileShader(fragShader);                             //compiles shader

  GLint isCompiled = 0;
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
{
	GLint maxLength = 0;
	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

	// The maxLength includes the NULL character
	std::vector<GLchar> errorLog(maxLength);
	glGetShaderInfoLog(fragShader, maxLength, &maxLength, &errorLog[0]);

  for(GLchar word : errorLog){
    std::cout << word;
  }
	// Provide the infolog in whatever manor you deem best.
	// Exit with failure.
	glDeleteShader(fragShader); // Don't leak the shader.
	
}

  //vertShader
  auto vertCode = createShaderSource("../shaders/vertex_shader.vert");
  const char* vertShaderSource = reinterpret_cast<const char*>(vertCode.data());
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vertShaderSource, NULL);
  glCompileShader(vertShader);

  _shaderProgram = glCreateProgram(); //creates a program object to which you can attach a shader object
  glAttachShader(_shaderProgram,vertShader); //specifies shader objects that will be linked to create a program
  glAttachShader(_shaderProgram,fragShader); //can check compatibility of shaders

  glLinkProgram(_shaderProgram);  //links program to create executables to run on processors (vertex, fragment, geometry)

  glDeleteShader(fragShader); //no longer need shaders
  glDeleteShader(vertShader);




// »»» BUFFERS «««
  
  glGenVertexArrays(1,&_VAO); //generate before vertex buffer (essentially manages vertex attributes)
  glGenBuffers(1, &_VBO);               //inits buffer handles (can be array) »[num of buffers, pointer to buffers]

  glGenBuffers(1, &_IBO);
  
  glBindVertexArray(_VAO); 

  glBindBuffer(GL_ARRAY_BUFFER, _VBO);  //specifies usage of buffer and allows handle to be used »[usage of buffer, buffer handle]
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW); //allocates and fills currently bound buffer and specifies usage [DYNAMIC,STATIC,STREAM][DRAW,READ,COPY]
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 3* sizeof(float), (void*)0); //tell opengl how we want to feed it to the shader we are using (how it's formatted)
  glEnableVertexAttribArray(0); //tell opengl to use slot 0 for the shader
  
  glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind so they cannot be modified after the fact 
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


// »»» RENDERING LOOP «««

//set the viewport            todo:: viewport does not draw whole screen in fullscreen mode
  glViewport(0,0,_window._height,_window._width);

  float r = 0;
  float g = 0;
  float b = 0;
  
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(_window._handle))
  {
    
    r += 0.001;
    g += 0.003;
    b += 0.004;
    
    if(r >= 1){
      r = 0;
    }
    if(g >= 1){
      g = 0;
    }
    if(b >= 1){
      b = 0;
    }
   
    glBindVertexArray(_VAO);      //says that we want to feed the shader this specific way
    glUseProgram(_shaderProgram); //uses executable created earlier
    
    //set clear color
    
    glClearColor(r,g,b,1.f);
    
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW]
   
   //swap buffers
    glfwSwapBuffers(_window._handle); 

   
    
   
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 

 
}


sApp::~sApp(){
     
 //cleanup
  glDeleteVertexArrays(1, & _VAO);
  glDeleteBuffers(1,&_VBO);
  glDeleteBuffers(1,&_IBO);
  glDeleteProgram(_shaderProgram);
  _window.destroy();
  glfwTerminate();
}

}//namespace shb