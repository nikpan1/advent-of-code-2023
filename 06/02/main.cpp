#include <iostream>
#include <fstream>
#include <vector> 
#include <math.h> 


long int split(std::string str, char separator=' ') {
  int end = 3; 
  while(end ++ < str.size()) { 
    if(str[end] == separator) return std::stoll(str.substr(end, str.size() - end));
  } 
  return 0;
}


class quadraticSolution {
public:
  long int a = -1; long int b;  /* max_time */ long int c;  /* time to beat */
  quadraticSolution(long int _b, long int _c) { b = _b; c = _c; }
  bool hasSolution() { return delta() >= 0; }

  std::vector<double> solution() {
    sol.push_back((-1 * b - sqrt(delta()))/(2*a));
    sol.push_back((-1 * b + sqrt(delta()))/(2*a));
    return sol;
  }
private:
  std::vector<double> sol;
  long int delta() { return b*b - 4*a*c; }
};


long int countPossibilites(std::vector<double> range) {
  long int start = std::ceil(range[0]); 
  long int end = std::floor(range[1]);

  return abs(start - end) - 1;
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
  
  std::string line; 
  std::getline(input, line);
  long int time = split(line);
  std::getline(input, line);
  long int distance = split(line);
  

  quadraticSolution sol = quadraticSolution(time, (-1) * distance); 
  auto ans = sol.solution();
  std::cout << "result = " << countPossibilites(ans);
  
  return 1;
}
