#include <iostream>
#include <fstream>
#include <string>
#include <vector>


bool isNumber(char c) { return (c <= 57) && (c >= 48); }
bool isPart(char c) { return !isNumber(c) && c != '.'; }


int getWholeNumber(std::string line, int &start) {
  int end = start;

  while(end < line.size() && isNumber(line[end])) end ++;
  while(start >= 0 && isNumber(line[start])) start --;
  

  int result = std::stoi(line.substr(start + 1, end - start));
  start = end + 1;
  return result;
}


// @TODO niektóre rzeczy liczy podwójnie, a niektóre wcale :/
int findValue(std::vector<std::string> buffer, int cx, int cy) {
  int x(0), y(0);
  for(int i = -1 ; i < 1; i ++) {
    for(int j = -1; j < 1; j ++) {
      x = cx + j; y = cy + i;
      if(x < 0 || y < 0 || x > buffer[0].size() || y > buffer.size()) continue;
      else if(isNumber(buffer[y][x])) { int val = getWholeNumber(buffer[y],x); std::cout << "b"<<val<< "\n";return val;};
    }
  }

  return 0;
}


int validateEngine(std::vector<std::string> buffer) {
  int result(0);

  for(int x = 0; x < buffer[0].size(); x ++) {
    for(int y = 0; y < buffer.size(); y ++) {
      if(isPart(buffer[y][x])) result += findValue(buffer, x, y);
    }
   }
//  std::cout<<"r=" << result << "\n"; 
  return result;
}


int main() {
  int result(0);
  
  std::ifstream input;
  input.open("input.txt");
  if(!input.is_open()) return -1;
  

  std::vector<std::string> buffer; 
  std::string line;

  int counter(0);  
  do {  
    buffer.push_back(line);  
  } while(counter ++ < 2 && std::getline(input, line));   // assumption: at least 3 lines in the file 
  
  while(std::getline(input, line)) {
    result += validateEngine(buffer);
    
    buffer.push_back(line);
    buffer.erase(buffer.begin());
  }

  std::cout << "result = " << result;
  return 1;
}

