

#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>

#define DEBUG true
#define DEBUGLOG(x) log(x)

namespace shb{


void log(const char* msg);


std::vector<char> readFile(const std::string& filePath);


} // namespace shb