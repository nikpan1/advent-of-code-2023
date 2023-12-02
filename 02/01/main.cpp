#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::map<std::string, int> keymap = {
  {"red", 0},
  {"green", 1},
  {"blue", 2},
};

std::vector<int> conditions = { 12, 13, 14 };  // r  g  b


std::vector<std::string> split(std::string str, std::string separator) {
  std::vector<std::string> result;

  int start = 0, end = 1;
  while(end != str.size()) {
    if(str[end] == separator[0]) {
      result.push_back(str.substr(start, end - start));
      start = end + separator.size();
    }
    end ++;
  }

  result.push_back(str.substr(start, end - start));
  return result;
}


bool isRoundValid(std::string game) {
  std::vector<std::string> values = split(game, ", ");
  std::vector<int> counters = {0,0,0};
  std::cout << values[0] << '\n';  
  
  for(auto val = values.begin(); val != values.end(); val ++) {
    std::vector<std::string> v = split(*val, " ");

    auto it = keymap.find(v[1]);
    if(it != keymap.end()) {
      counters[it->second] += std::stoi(v[0]);
    }
  }
  
  return (counters[0] <= conditions[0]) && 
    (counters[1] <= conditions[1]) &&
    (counters[2] <= conditions[2]);
}


bool isGameValid(std::string line) {
  std::vector<std::string> game = split(line, ":");
  std::vector<std::string> rounds = split(game[1],";");
  
  for(std::string round : rounds) {
    if(!isRoundValid(round)) return false;
  }
  
  return true;
}


int getGameID(std::string line) {
  auto game = split(line, ":");
  auto title = split(game[0], " ");
  return std::stoi(title[1]);
}


int main() {
  std::ifstream input;
  input.open("input.txt");
  if(!input.is_open()) {
    std::cerr << "File not loaded.";
    return -1;
  }

  int result = 0;
  std::string line;
  
  while(std::getline(input, line)) {
    if(isGameValid(line)) result += getGameID(line);
  }
  
  std::cout << "result = " << result << '\n';
  return 1;
}

