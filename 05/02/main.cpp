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
    result.push_back({*val, *(val+1), 0});

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


int dist(range r1, range r2) { return abs(r2.first - r1.first); }
bool isLeftSited(range val) { return val.length > 0; }
bool isSeedValue(range r1) { return r1.destination == 0; }


void annihilateLValues(std::vector<range>::iterator main, std::vector<range>& rest) {
  for(auto it = main; it < rest.end(); it ++) {
    if(dist(*main, *it) > abs(main->length)) break;
    
    if(isSeedValue(*it)) {
      it->destination = main->destination + (it->first - main->first); 
      it->length = dist(*it, *main);
    }
  }

  rest.erase(main);
}


void annihilateRValues(std::vector<range>::iterator main, std::vector<range>& rest) {
  for(auto it = main; it != rest.begin(); it --) {
    if(dist(*main, *it) > abs(main->length)) break;
    
    if(isSeedValue(*it)) {
      it->destination = main->destination + (it->first - main->first); 
      it->length = dist(*it, *main);
    }
  }

  rest.erase(main);
}


std::vector<range> compareRanges(std::vector<range>& seeds, std::vector<range>& rg) {
  std::vector<range> values;
  auto addValues = [&values](std::vector<range> v) { for(auto r : v) {
      values.push_back(r);
      values.push_back(range{r.first + r.length - 1, -1 * r.length, r.destination});
    }};

  addValues(seeds); addValues(rg);
  std::sort(values.begin(), values.end(), [](const auto& a, const auto& b) { return a.first < b.first; } );
  

  // _____________
  std::cout << "seeds:";
  for(auto s : seeds) std::cout<<"("<<s.first<<","<<s.length<<","<<s.destination<<"|";
  std::cout << "\n";
  std::cout << "ranges:";
  for(auto s: rg) std::cout<<"("<<s.first<<","<<s.length<<","<<s.destination<<"|";  std::cout <<endl;
  std::cout<<"sorted corners:\n";
  for(auto s : values) std::cout << s.first <<"|" << s.length << "|" << s.destination <<"\n";
  // _____________


  auto start = values.begin(), end = values.end();      // get the first and last occurance of 's' --> it will be the range we want
  while(start->destination != 0) start ++;
  while(end->destination != 0) end --;

  for(auto val = start; val != end - 1; val ++) {
    int destLength = dist(*val, *(val+1)); 
    int newVal;
        
    if(!isSeedValue(*val)) {
      if(isLeftSited(*val)) annihilateLValues(val, values);
      else annihilateRValues(val, values);
    }
  } 
 
  std::cout << "\nNew seeds:\n";
  for(auto s: values) std::cout <<"("<<s.first << ", "<<s.length<< "," << s.destination <<  ")";

  return seeds;

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
    seeds = compareRanges(seeds, rangeMap);   
  }

  std::sort(seeds.begin(), seeds.end(), 
    [](const auto& a, const auto& b) { return a.first < b.first; } );
  

  std::cout << "result = " << seeds[0].first << "\n";
  return 1;
}
