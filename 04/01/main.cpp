#include <fstream>
#include <iostream>

bool isNumber(char c) { return (c >= '0') && (c <= '9'); }


int getCardPoints(const std::string& line, int gameLI, int winningLI) {
  int result(1), last(line.size() - 1);
  
  std::string number = "aa";
  int id(0);

  std::string winning = line.substr(gameLI + 1, winningLI - gameLI - 1);
  while(last > winningLI) {
    number = line.substr(last - 2, 3);

    if(winning.find(number + " ") != std::string::npos) result = result << 1; 
    last -= 3;
  }
  return result >> 1;
}


int main(int argc, char **argv) {
  int result(0);

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



  std::string line;
  while(std::getline(input, line)) {
    // LI - last index
    int gameLI = line.find(':');
    int winningLI = line.find('|');
    
    result += getCardPoints(line, gameLI, winningLI);
    
  }
  
  std::cout << "result = " << result;
  return 1;
}
