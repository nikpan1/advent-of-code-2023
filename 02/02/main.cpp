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

std::vector<int> validateRound(std::string game) {
  std::vector<std::string> values = split(game, ", ");
  std::vector<int> counters = {0,0,0};
  
  for(auto val = values.begin(); val != values.end(); val ++) {
    std::vector<std::string> v = split(*val, " ");

    auto it = keymap.find(v[1]);
    counters[it->second] += std::stoi(v[0]);
  }
  
  return counters;
}

std::vector<int> getMaxValues(std::vector<int> v1, std::vector<int> v2) {
  std::vector<int> result; 
  for(int i = 0; i < 3; i ++) {
    result.push_back((v1[i] > v2[i]) ? v1[i] : v2[i]);
  }

  return result;
}

int powerOfGame(std::vector<int> vals) {
  int result = 1;
  for(auto value : vals) result *= value;
  
  return result;
}


int validateGame(std::string line) {
  std::vector<std::string> game = split(line, ":");
  std::vector<std::string> rounds = split(game[1],";");
  
  std::vector<int> minValues = {0,0,0};
  
  for(std::string round : rounds) {
    minValues = getMaxValues(minValues, validateRound(round));
    std::cout << "-" << minValues[0] << " " << minValues[1] << " " << minValues[2] << "\n";
  }
  
  return powerOfGame(minValues);
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
    std::cout << validateGame(line) << "\n";
    result += validateGame(line);
  }
  
  std::cout << "result = " << result << '\n';
  return 1;
}

