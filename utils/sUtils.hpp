

#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>

//glfw/glad
#include <glad/glad.h> //include glad/glad.h instead of glad.c to avoid multiple definitions of functions as glad likes to cry about this
#include <GLFW/glfw3.h> 

#define DEBUG true
#define DEBUGLOG(x) log(x)

namespace shb{


void log(const char* msg);
void log(const std::string& msg);

GLenum checkError(const char *file, int line);

std::vector<char> readFile(const std::string& filePath);


} // namespace shb