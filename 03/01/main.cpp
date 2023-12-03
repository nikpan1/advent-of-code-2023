#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

class number {
public:
  number(int _value, int _x, int _y, int _len) : value(_value), digitLength(_len) {
    pos = {_x, _y};
  }
  int value;
  std::pair<int,int> pos; // don't ask why, ask why not :D
  int digitLength; // not used, but ye
};


bool isNumber(char c) {
  return (c <= 57) && (c >= 48);
}


bool isPart(char c) {
  return !isNumber(c) && c != '.';
}


int getNumberLength(number n) {
   int count = 0;
   while(n.value != 0) {
      n.value = n.value / 10;
      count++;
   }
   return count;
}


int getNumberValue(std::string line, int& start) {
  int end = start;
  while(isNumber(line[end])) end ++;
  
  int result = std::stoi(line.substr(start, end));
  start = end - 1;
  return result; 
}


void search(int lineIndex, std::string line, std::vector<std::pair<int, int>>& parts, std::vector<number>& numbers) {
  int old_i = 0;
  for(int i = 0; i < line.size(); i ++) {
    if(line[i] != '.') { // it's a part or number 
      if(isNumber(line[i])) {
        old_i = i;
        number n(getNumberValue(line, i), i, lineIndex, 1 + i - old_i);
        std::cout<< i << "-"<<lineIndex<<"\n";
        numbers.push_back(n);
      }
      else {
        std::pair<int,int> pos{lineIndex, i};
        parts.push_back(pos);
      }
    }
  }
}


int isAdjacent(std::vector<std::pair<int, int>>& parts, number n) {
  std::pair<int,int> npos{0,0};
  int counter = 0;
  for(int i = - 1; i < getNumberLength(n) + 1; i ++) {
    npos = {n.pos.first - i, n.pos.second + 1};  
    if(n.pos.first -i >= 0 && std::find(parts.begin(), parts.end(), npos) != parts.end()) return true;
    npos = {n.pos.first - i, n.pos.second - 1};  
    if(n.pos.first - i >= 0 && n.pos.first - i && std::find(parts.begin(), parts.end(), npos) != parts.end()) return true;
  }

  npos = {n.pos.first + 1, n.pos.second};  
  if(std::find(parts.begin(), parts.end(), npos) != parts.end()) return true; // right
 
  npos = {n.pos.first - getNumberLength(n), n.pos.second};  
  if(std::find(parts.begin(), parts.end(), npos) != parts.end()) return true; // left

  return false;
}


int countSeperate(std::vector<std::pair<int, int>>& parts, std::vector<number>& numbers) {
  int result = 0;
  
  for(auto number : numbers) {
    if(!isAdjacent(parts, number)) {result ++;  
      std::cout << number.value<<" :)\n";  
    }
  }

  return result;
}

int main() {
  std::ifstream input;
  input.open("input.txt");
  if(!input.is_open()) {
    std::cerr << "File not loaded.";
    return -1;
  }

  std::vector<std::pair<int,int>> parts;
  std::vector<number> numbers;
 
  std::string line;
  int lineIndex = 0;
  
  while(std::getline(input, line)) {
    search(lineIndex ++ , line, parts, numbers);
  }
  
  std::cout << countSeperate(parts, numbers);
  
  return 1;
}

