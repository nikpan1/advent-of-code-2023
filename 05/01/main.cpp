#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm>

 /*
   * val[0] - start of the destination range
   * val[1] - start of source range
   * val[2] - the range
 */

#define endl '\n'
bool isNumber(char c) { return (c >= '0') && (c <= '9'); }
bool isInRange(long int seed, const std::vector<long int>& range) { return seed >= range[1] && seed < range[1] + range[2]; }   


std::vector<long int> split(std::string str, char separator) {
  std::vector<long int> result;
  int start(0), end(0);

  while(end ++ < str.size()) { 
    if(str[end] == separator) {
      result.push_back(std::stoll(str.substr(start, end - start)));
      start = end;
    }
  } 
  
  result.push_back(std::stoll(str.substr(start, str.size() - 1)));
  return result;
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
  
  // ------
  std::string line;
  std::getline(input, line);
  auto seeds = split(line.substr(7, line.size()-1), ' ');
  
  while(input.is_open() && std::getline(input, line)) {
    
    std::vector<std::vector<long int>> ranges;
    if(isNumber(line[0])) do {
      ranges.push_back(split(line, ' '));  
    } while(std::getline(input, line) && isNumber(line[0]));  
    

    for(auto& seed : seeds) {
      for(auto range : ranges) {
        if(isInRange(seed, range)) {
          seed = range[0] + (seed - range[1]);
          break;
        }
      }
    }

  }

  std:: cout << "result = " << *std::min_element(seeds.begin(), seeds.end()); 
  return 1;
}
