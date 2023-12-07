#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "Wrong amount of arguments.\n";
    return -1;
  }

  std::ifstream input;
  input.open(argv[1]);
  if(!input.is_open()) {
    std::cerr << "File not opened.\n";
    return -1;
  }
  
  int result(0);
  std::string line;

  while(std::getline(input, line)) {
    // do it
  }




  return result;
}
