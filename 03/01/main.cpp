#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define BUFFER_SIZE 3
#define EMPTY_CHAR '.'
bool isNumber(char c) { return (c <= 57) && (c >= 48); }
bool isPart(char c) { return !isNumber(c) && c != EMPTY_CHAR; }


int getWholeNumber(std::string& line, int start) {
  int end = start;
  while(end < line.size() && isNumber(line[end])) end ++;
  while(start >= 0 && isNumber(line[start])) start --;
  
  int result = std::stoi(line.substr(start + 1, end - start));
  for(int i = start + 1; i <= end - 1; i ++) line[i] = EMPTY_CHAR;
  
  return result;
}


int findPartNumber(std::vector<std::string>& buffer, int cx, int cy) {
  int result(0);

  for(int x = cx - 1 ; x <= cx + 1; x ++) 
    for(int y = cy - 1; y <= cy + 1 ; y ++) 
      if((x >= 0 && x < buffer.size()) && (y >= 0 && y < buffer[x].size()) && (isNumber(buffer[x][y])))
        result += getWholeNumber(buffer[x], y);

  return result;
}


int validateEngine(std::vector<std::string>& buffer) {
  int result(0);
  for(int x = 0; x < buffer.size(); x ++) 
    for(int y = 0; y < buffer[x].size(); y ++) 
      if(isPart(buffer[x][y])) result += findPartNumber(buffer, x, y);
  
  return result;
}


int main(int argc, char** argv) {
  if(argc < 2) {
    std::cerr << "Dej mi tu wincyj inputu.\n";
    return -1;
  }

  std::ifstream input;
  input.open(argv[1]);
  if(!input.is_open()) {
    std::cerr << "File failed to open.\n";
    return -1;
  }


  int result(0);
  std::vector<std::string> buffer; 
  std::string line;

  while(input) { 
    while(BUFFER_SIZE > buffer.size()) {
     std::getline(input, line);
     buffer.push_back(line);
    }
    
    result += validateEngine(buffer);
    for(int i = 1; i < BUFFER_SIZE; i ++) buffer.erase(buffer.begin());
  }

  std::cout << "result = " << result;
  return 1;
}

