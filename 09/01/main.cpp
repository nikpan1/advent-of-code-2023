#include <iostream>
#include <fstream>
#include <vector> 
#include <string>


std::vector<int> split(std::string str, char separator=' ') {
  std::vector<int> result;

  int start = 0, end = 1;
  while(end != str.size()) {
    if(str[end] == separator) {
      result.push_back(std::stoi(str.substr(start, end - start)));
      start = end + 1;
    }
    end ++;
  }

  result.push_back(std::stoi(str.substr(start, end - start)));
  return result;
}


std::vector<int> getDistances(const std::vector<int>& his) {
  std::vector<int> result;
  for(int i = 0; i < his.size() - 1; i ++) result.push_back(abs(his[i + 1] - his[i]));
  std::cout << "H - ";
  for(auto i : result) std::cout << i << " ";
  std::cout << "\n";
  return result;
}


bool areDistancesEqual(const std::vector<int>& dists) {
  return dists[dists.size() - 1] == 0 && dists[dists.size() - 1] == 0;
}


int sum(const std::vector<int>& arr) {
  int result = 0;
  for(auto el : arr) result += el;
  return result;
}


int getNextValue(const std::vector<int>& history) {
  auto dists = getDistances(history);
  std::vector<int> lastValues;

  lastValues.push_back(history[history.size() - 1]);
  lastValues.push_back(dists[dists.size()-1]);
  
  while(!areDistancesEqual(dists)) {
    dists = getDistances(dists);
    lastValues.push_back(dists[dists.size() - 1]);
  }
  
  for(auto d : lastValues) std::cout << d << " "; std::cout << "\n";
  return sum(lastValues);
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
    auto history = split(line);
    std::cout << "\nVal: ";
    for(auto a : history) std::cout << a << " ";
    std::cout << "\n";
    result += getNextValue(history);
  }

  std::cout << "result =" << result;
  return result;
}
