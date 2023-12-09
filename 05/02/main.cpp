#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm>
#include <utility>

#define endl '\n'
struct range{ int first; int length; int destination = 0;};
bool isNumber(char c) { return (c >= '0') && (c <= '9'); }
bool isInRange(int seed, const std::vector<int>& range) { return seed >= range[1] && seed < range[1] + range[2]; }   


std::vector<int> split(std::string str, char separator) {
  std::vector<int> result;
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


std::vector<range> getSeedRanges(std::string& line) {
  std::vector<range> result;
  auto values = split(line.substr(7, line.size() - 1), ' ');
  
  for(auto val = values.begin(); val < values.end(); val += 2) 
    result.push_back({*val, *val + *(val + 1) - 1});

  return result;
}


std::vector<range> getAlmanacRanges(std::ifstream& input, std::string& line) {
  std::vector<range> result;

  do {
    auto v = split(line, ' ');
    result.push_back({v[1], v[2], v[0]});  
  } while(std::getline(input, line) && isNumber(line[0]));  
  
  return result;
}

void compareRanges(std::vector<range>& seeds, std::vector<range>& rg) {
  std::vector<std::pair<char, range>> values;
  auto addValues = [&values](std::vector<range> v, char id) { for(auto r : v) {
      values.push_back(std::make_pair(id, r));
      values.push_back(std::make_pair(id, range{r.first + r.length - 1, -1 * r.length, r.destination}));
    }};

  addValues(seeds, 's');
  addValues(rg, 'r');

  std::sort(values.begin(), values.end(), 
    [](const auto& a, const auto& b) { return a.second.first < b.second.first; } );

  std::vector<range> newSeeds; // we could optimise it 
  
  // get the first and last occurance of 's' --> it will be the range we want
  auto start = values.begin(), end = values.end();
  for(auto val = values.begin(); val != values.end(); val ++) { 
    if(val->first == 's') {
      start = val;
      break;
    }
  }
  for(auto val = values.end(); val != values.begin(); val --) { 
    if(val->first == 's') {
      end = val;
      break;
    }
  }
 
  for(auto val = start; val != end; val ++) {
    int destinationVal = 0;
    
    if(val->second.destination != 0) {
      if(val->second.destination > 0) // it means it's the lvalue
        destinationVal = val->second.destination;
      else // it means it's a value we don't need 
        break;
    }
    else {  
      if((val+1)->second.destination == 0) destinationVal = 0;  // the next value is also 's'
      else if((val+1)->second.destination < 0) destinationVal = (val+1)->second.destination; // the next value is a rvalue
      else if((val+1)->second.destination > 0) destinationVal = 0;
    }
  //
  // //  HOW DO WE KNOW THE NEW VALUE 
  //
    int firstVal = (destinationVal == 0) ? val->second.first : val->second.first - ; 
    newSeeds.push_back({firstVal,  });
  } 

}


void translateRanges(std::vector<range>& seeds, std::vector<range> rangeMap) { 
  for(range rg : rangeMap) {

  };
}


int main(int argc, char** argv) {
  if(argc != 2) std::cerr << "Wrong amount of arguments.\n";
  
  std::ifstream input;
  input.open(argv[1]);
  if(!input.is_open()) std::cerr << "File not opened.\n";


  // get the seed line and read it 
  std::string line;
  std::getline(input, line);
  std::vector<range> seeds = getSeedRanges(line);
  
  std::vector<range> rangeMap;
  while(input.is_open() && std::getline(input, line)) {
    if(!isNumber(line[0])) continue;
    rangeMap = getAlmanacRanges(input, line);
    translateRanges(seeds, rangeMap);   
  }

  return 1;
}
