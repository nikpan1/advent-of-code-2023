#include <iostream>
#include <fstream>
#include <vector> 
#include <math.h> 


std::vector<long int> split(std::string str, char separator=' ') {
  std::vector<long int> result;
  long int start(0), end(0);
  while(str[start] != ':') start ++;
  start += 2; end = start;
  
  while(end ++ < str.size()) { 
    if(str[end] == separator) {
      result.push_back(std::stoll(str.substr(start, end - start)));
      start = end;
    }
  } 
  
  result.push_back(std::stoll(str.substr(start, str.size() - 1)));
  return result;
}


class quadraticSolution {
public:
  long int a = -1; long int b;  /* max_time */ int c;  /* time to beat */
  quadraticSolution(long int _b, long int _c) { b = _b; c = _c; }
  bool hasSolution() { return delta() >= 0; }

  std::vector<double> solution() {
    sol.clear();
    
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
  
  long int result(1);
  std::string line;
  
  std::getline(input, line);
  std::vector<long int> time = split(line);
 
  std::getline(input, line);
  std::vector<long int> distance = split(line);
  std::cout << "d" << distance[0];
  for(long int i = 0; i < distance.size(); i ++) { 
    quadraticSolution sol = quadraticSolution(time[i], (-1) * distance[i]); 
    if(!sol.hasSolution()) continue;
    auto ans = sol.solution();
    std::cout << "\n-->" << countPossibilites(ans);
    result *= countPossibilites(ans);

  }

  std::cout << "result = " << result;
  return result;
}
