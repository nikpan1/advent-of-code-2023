#include <iostream>
#include <fstream>

bool isDigit(char c) {
  return ( c >= 48 ) && ( c <= 57 );
}

int toInt(char c) {
  return int(c) - 48;
}

int findCode(std::string line) {
  int result = 0;
  size_t size = line.size();
  
  for(int i = 0; i < size; i ++) 
    if(isDigit(line[i])) {
      result += toInt(line[i]) * 10;
      break;
    }

  for(int i = size; i >= 0; i --) 
    if(isDigit(line[i])) {
      result += toInt(line[i]);
      break;
    }

  return result;
}

int main() {
  std::ifstream input;
  input.open("input.txt");
  
  if (!input.is_open()) {
    std::cerr << "File was not opened";
    return -1;
  }
  int sum = 0;
  std::string line;
  while ( getline(input, line) ) {
    sum += findCode(line);
  }

  std::cout << sum;
  return 1;
}

