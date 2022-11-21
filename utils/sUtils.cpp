#include <sUtils.hpp>

namespace shb{


void log(const char* msg){
  if(DEBUG){
    std::cout<< msg << "\n";
  }
}


std::vector<char> readFile(const std::string& filePath){
 //open file at the end of the file (ate) in binary form, and open for input
  char* cwd = get_current_dir_name();

  std::ifstream file;
  file.open(filePath.c_str(), std::ios::ate |  std::ios::binary | std::ios::in );

 //check file is open
  if(!file.is_open()){
     std::cout << "Failed to open file at: " << cwd << "\n";
    }
  else{
     std::cout <<"Successfully opened file " << cwd << "\n";
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

}//namespace shb