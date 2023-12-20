#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include <sstream>

std::vector<int> split(const std::string &str, char separator = ' ');
std::ifstream loadFile(int argc, char** argv);


int main(int argc, char** argv) {
  std::ifstream input = loadFile(argc, argv);  
  std::string line;

  while(std::getline(input, line)) {

  }

  return 0;
}


std::vector<int> split(const std::string &str, char separator) {
  std::vector<int> result;
  std::istringstream iss(str);
  std::string value;

  while(std::getline(iss, value, separator)) result.push_back(std::stoi(value));
  return result;
}


std::ifstream loadFile(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "Wrong amount of arguments.\n";
  }

  std::ifstream input;
  input.open(argv[1]);
  if(!input.is_open()) {
    std::cerr << "File not opened.\n";
  }

  return input;
}



