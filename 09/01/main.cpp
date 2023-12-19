#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include <sstream>


std::vector<int> split(const std::string &str, char separator = ' ') {
  std::vector<int> result;
  std::istringstream iss(str);
  std::string value;

  while(std::getline(iss, value, separator)) result.push_back(std::stoi(value));
  return result;
}


int getLastDistance(std::vector<int>& his) {
  std::vector<int> result;
  for(int i = 0; i < his.size() - 1; i ++) result.push_back(his[i + 1] - his[i]);
  his = result;
  return result.back();
}


bool areDistancesEqual(const std::vector<int>& dists) {
  if(dists.size() == 1) return true;
  for(auto dist : dists) if(dist != 0) return false;
  return true;
}


int getNextValue(std::vector<int> history) {
  int result = history.back();
  while(!areDistancesEqual(history)) result += getLastDistance(history);
  return result + history.back();
}


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

  while(std::getline(input, line)) {
    result += getNextValue(split(line));
  }

  std::cout << "result =" << result;
  return result;
}
