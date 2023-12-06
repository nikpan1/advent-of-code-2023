#include <fstream>
#include <iostream>
#include <map>

bool isNumber(char c) { return (c >= '0') && (c <= '9'); }


int getCardPoints(const std::string& line, int gameLI, int winningLI) {
  int result(0), last(line.size() - 1);
  
  std::string number = "aa";
  std::string winning = line.substr(gameLI + 1, winningLI - gameLI - 1);
  while(last > winningLI) {
    number = line.substr(last - 2, 3);
    if(winning.find(number + " ") != std::string::npos) result ++;
    last -= 3;
  }

  return result;
}


int main(int argc, char **argv) {
  if(argc != 2) {
    std::cerr << "Wrong input.\n";
    return -1;
  }

  std::ifstream input;
  input.open(argv[1]);
  if(!input.is_open()) {
    std::cerr << "File was not opened.\n";
    return -1;
  }

  int index = 1; // counting game
  std::string line;
  std::map<int, int> result; 
  while(std::getline(input, line)) {
    // LI - last index
    int gameLI = line.find(':'), winningLI = line.find('|');
    
    result[index] += 1;
    int val = getCardPoints(line, gameLI, winningLI); 
    index ++;  
    for(int i = index; i < index + val; i ++) result[i] += result[index - 1];
  }
  

  int sum = 0;
  for( auto value : result) sum += value.second; 
  std::cout << "result = " << sum << '\n';
  return 1;
}
