#include <iostream>
#include <fstream>
#include <vector> 

std::vector<std::string> split(std::string str, char separator) {
  std::vector<std::string> result;

  int start = 0, end = 1;
  while(end != str.size()) {
    if(str[end] == separator) {
      result.push_back(str.substr(start, end - start));
      start = end + 1;
    }
    end ++;
  }

  result.push_back(str.substr(start, end - start));
  return result;
}



bool isNumber(char c) { return (c >= '0') && (c <= '9'); }

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
  
  std::getline(input, line);
  auto seeds = split(line, ' ');
  seeds.erase(seeds.begin()); // removes the first "seeds:"
  
  while(std::getline(input, line)) {
    // if finds than replace
    //
    // do it
  }




  return result;
}
