#include <iostream>
#include <fstream>

#include <algorithm>
#include <vector>
#include <utility> 
#include <array>
#include <unordered_map>


#define sep ' '
std::array<char, 13> keymap = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
std::pair<std::string, int> readCamelCard(std::string line) { return std::make_pair(line.substr(0, 5), std::stoi(line.substr(6, line.size() - 6))); }


int gv(char c) {  // get value from keymap 
  int result = 0;
  while(c != keymap[result]) result ++;
  return result;
}


int getHandType(std::pair<std::string, int> hand) {
  std::unordered_map<char, int> counter;   // does anyone like std::map? me? no.
  for(char c : hand.first) counter[c] ++ ;
  
  std::vector<int> values;
  for(auto ct : counter) values.push_back(ct.second);
  std::sort(values.begin(), values.end(), std::greater<int>());
  
  for(auto c = values.begin(); c != values.end(); c ++) {
    switch(*c) {
      case 5: return 6;                                 // 6 | five of a kind 
      case 4: return 5;                                 // 5 | four of a kind 
      case 3: return (*(c+1) == 2) ? 4 : 3;  // 4 | full house        3 | three of a kind 
      case 2: return (*(c+1) == 2) ? 2 : 1;  // 2 | two pair          1 | one pair 
    }
  }
  return 0;                                             // 0 | high card 
}


void sortHands(std::vector<std::vector<std::pair<std::string, int>>>& types) {
  for(auto& type : types) {
    std::sort(type.begin(), type.end(),
    [](const auto& a, const auto& b) {
      for(int i = 0; i < a.first.size(); i++) 
        if(a.first[i] != b.first[i]) 
          return gv(a.first[i]) < gv(b.first[i]);
      
      return gv(a.first.back()) < gv(b.first.back());
    });
  } 
}


int main(int argc, char** argv) {
  if(argc != 2) { std::cerr << "Wrong amount of arguments.\n"; return -1; }
  std::ifstream input; input.open(argv[1]);
  if(!input.is_open()) { std::cerr << "File not opened.\n"; return -1; }
 

  std::vector<std::vector<std::pair<std::string, int>>> types;
  types.resize(7);

  std::string line;
  while(std::getline(input, line)) {
    auto p = readCamelCard(line);
    types[getHandType(p)].push_back(p); 
  }

  sortHands(types);
  
  int ct = 0;
  long int sum = 0; int rankNum = 1;
  for(auto v : types) { 
    for(auto u : v){ 
      sum += rankNum * u.second;
      std::cout << ct << "|" << u.first <<"\n";
      rankNum ++;
    }
    ct ++ ;
  }
  
  std::cout << "sum = " << sum;
  return 1;
}
