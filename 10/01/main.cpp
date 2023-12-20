#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include <sstream>
#include <map>

std::vector<int> split(const std::string &str, char separator = ' ');
std::ifstream loadFile(int argc, char** argv);

struct pos { int x, y; };
struct loop { pos start; std::vector<pos> path; };

pos getStartPos(const std::vector<std::string>& grid) {
  for(int x = 0; x < grid[0].size(); x ++) 
    for(int y = 0; y < grid.size(); y ++)
      if(grid[y][x] == 'S') return pos{y, x};
  
  return pos{0, 0};
}


/*
 | is a vertical pipe connecting north and south.
- is a horizontal pipe connecting east and west.
L is a 90-degree bend connecting north and east.
J is a 90-degree bend connecting north and west.
7 is a 90-degree bend connecting south and west.
F is a 90-degree bend connecting south and east.
. is ground; there is no pipe in this tile.
*/

std::map<char, std::vector<pos>> tiles = {
  //pipe  x y       x y
  {'|', {{1, 0},  {-1, 0} }},
  {'-', {{0, 1},  {0, -1} }},
  {'L', {{-1, 0}, {0, 1}  }},
  {'J', {{-1, 0}, {0, -1} }},
  {'7', {{0, -1}, {0, 0}  }},
  {'F' ,{{1, 0},  {0, 1}  }},
};


loop getBiggestLoop(const std::vector<std::string>& grid, pos start) {
  loop result;
  result.start = start;
}


int main(int argc, char** argv) {
  std::ifstream input = loadFile(argc, argv);  
  std::string line;
  
  std::vector<std::string> grid;
  while(std::getline(input, line)) grid.push_back(line);
  
  pos startPos = getStartPos(grid);
  loop biggestLoop = getBiggestLoop(grid, startPos); 
  

  return 0;
}


std::vector<int> split(const std::string &str, char separator) {
  std::vector<int> result;
  std::istringstream iss(str);
  std::string value;

  while(std::getline(iss, value, separator)) result.push_back(std::stoi(value));
  return result;
}


std::ifstream loadFile(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "Wrong amount of arguments.\n";
  }

  std::ifstream input;
  input.open(argv[1]);
  if(!input.is_open()) {
    std::cerr << "File not opened.\n";
  }

  return input;
}



