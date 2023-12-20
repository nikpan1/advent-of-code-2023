#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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

bool isDigitChar(char c) {
  return (( c >= 48 ) && ( c <= 57 ));
}

bool isDigitSpelled(std::string chr, int index, int& value) {
  for(int i = 3; i < 6; i ++) {
    if(index + i >= chr.size()) return 0;
    std::string sub = chr.substr(index, i);
    
    auto result = std::find(numbers.begin(), numbers.end(), sub);
    if(result != numbers.end()) // sub was found
    {
      value = 1 + result - numbers.begin();
      return 1;
    }
  }

  return 0;
}

bool isReversedDigitSpelled(std::string chr, int index, int& value) {
  for(int i = 2; i < 6; i ++) {
    if(index - i < 0) return 0;
    std::string sub = chr.substr(index - i, i + 1);
    
    //std::cout << "sub - " << sub << "\n";
    auto result = std::find(numbers.begin(), numbers.end(), sub);
    if(result != numbers.end()) // sub was found
    {
      value = 1 + result - numbers.begin();
      return 1;
    }
  }

  return 0;
}

int charToInt(char c) {
  return int(c) - 48;
}

int findDecimal(std::string line) {
    int val = 0;
    for(int i = 0; i < line.size(); i ++) {
      if(isDigitChar(line[i])) return charToInt(line[i]);
      if(isDigitSpelled(line, i, val)) return val;
    }
    return val;  
}

int findSingular(std::string line) {
  int val = 0;
  for(int i = line.size() - 1; i >= 0; i --) {
    if(isDigitChar(line[i])) return charToInt(line[i]);
    if(isReversedDigitSpelled(line, i, val)) return val;
  }
  return val;
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
    sum += findDecimal(line) * 10 + findSingular(line);
    std::cout << findDecimal(line) * 10 + findSingular(line) << " | "; 
  }

  std::cout << sum;
  return 1;
}

