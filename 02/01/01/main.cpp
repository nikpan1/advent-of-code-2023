#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


std::vector<std::string> shortNumbers = {
  "one",
  "two",  
  "thr",
  "fou", 
  "fiv", 
  "six",  
  "sev",
  "eig",
  "nin", 
};


std::vector<std::string> numbers = {
  "one",
  "two",  
  "three",
  "four", 
  "five", 
  "six",  
  "seven",
  "eight",
  "nine", 
};

bool foundSubstr(const std::string& line, int startIdx, int endIdx, const std::vector<std::string>& collection) {
  if(endIdx > line.size() - 1 || startIdx < 0) return false;
  std::string shortNum = line.substr(startIdx, endIdx);
  return std::find(collection.begin(), collection.end(), shortNum) != collection.end();
}

bool foundSubstr(const std::string& line, int startIdx, int endIdx, const std::vector<std::string>& collection, int& value) {
  if(endIdx > line.size() - 1 || startIdx < 0 || startIdx > endIdx) return false;
  std::string shortNum = line.substr(startIdx, endIdx);
  auto val = std::find(collection.begin(), collection.end(), shortNum);
  if(val == collection.end()) {value = 0; return false;}
  else { value = val - collection.begin(); return true;}
}

bool isSpelledDigit(const std::string& line, int index, int& value) {
  if(!foundSubstr(line, index, index + 3, shortNumbers)) return false;
  return foundSubstr(line, index, index + 5, numbers, value);
}

bool isReversedSpelledDigit(const std::string& line, int index, int& value ) {
  if(!foundSubstr(line, index - 3, index, shortNumbers)) return false;
  return foundSubstr(line, index - 5, index, numbers, value);
}


bool isDigitChar(char c) {
  return (( c >= 48 ) && ( c <= 57 ));
}

int charToInt(char c) {
  return int(c) - 48;
}

int findCode(const std::string& line) {
  int result = 0;
  int val = 0;
  for(int i = 0; i < line.size(); i ++) {
    if(isDigitChar(line[i])) {
      result += charToInt(line[i]) * 10;
      break;
    }
    if(isSpelledDigit(line, i, val)) {
      result += val * 10;
      break;
    }
  }

  for(int i = line.size() - 1; i >= 0; i --) {
    if(isDigitChar(line[i])) {
      result += charToInt(line[i]); 
      break;
    }
    if(isReversedSpelledDigit(line, i, val)) {
      result += val;
      break;
    }
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
    std::cout << findCode(line) << "\n"; 
  }

  std::cout << sum;
  return 1;
}

