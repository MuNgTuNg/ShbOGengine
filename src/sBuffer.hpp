 
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