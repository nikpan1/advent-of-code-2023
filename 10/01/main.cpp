#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

std::vector<int> split(const std::string &str, char separator = ' ');
std::vector<std::string> loadFile(int argc, char** argv);


struct pos { 
  int x, y; 
  pos operator+(const pos& other) const   { return pos{this->x + other.x, this->y + other.y}; }
  pos operator-(const pos& other) const   { return pos{this->x - other.x, this->y - other.y}; }
  bool operator==(const pos& other) const { return this->x == other.x && this->y == other.y;  }
  bool operator!=(const pos& other) const { return this->x != other.x || this->y != other.y;  }
};


struct loop { 
  pos start; 
  std::vector<pos> path;
  pos current() { return path.back(); }
  int size() { return path.size(); }
};


std::map<char, std::vector<pos>> tiles = {
  //pipe  x y       x y
  {'|', {{0, 1 }, {0, -1} }},
  {'-', {{1, 0 }, {-1, 0} }},
  {'L', {{0, -1}, {1, 0 } }},
  {'J', {{0, -1}, {-1, 0} }},
  {'7', {{0, 1 }, {-1, 0} }},
  {'F' ,{{0, 1 }, {1, 0 } }},
};

pos getStartPos(const std::vector<std::string>& grid) {
  for(int x = 0; x < grid[0].size(); x ++) 
    for(int y = 0; y < grid.size(); y ++)
      if(grid[y][x] == 'S') return pos{x, y};                // @todo check if good 
  
  return pos{0, 0};
}

pos getEndOfPipe(const std::vector<std::string>& grid, pos oldPos, pos newPos) {
  pos comeFrom = newPos - oldPos;
  
  auto it = tiles.find(grid[newPos.y][newPos.x]);
  auto entry = std::find(it->second.begin(), it->second.end(), comeFrom);
  int index = 1 - std::distance(it->second.begin(), entry); 
  
  return it->second[index];
} 

bool canMove(const std::vector<std::string>& grid, pos oldPos, pos newPos) {
  auto it = tiles.find(grid[newPos.y][newPos.x]);
  if(it == tiles.end()) return false;
  
  bool result = false;
  for(auto vec : it->second) result = result || (oldPos == newPos - vec);
  return result;
}

loop findLoop(const std::vector<std::string>& grid, pos start) {
  loop result{start, {start}};
  
  if(canMove(grid, start, )
  while(result.current() != start) move(grid, result);

  return result;
}


loop getBiggestLoop(const std::vector<std::string>& grid, pos start) {
  std::vector<loop> loops;

  for(auto x : tiles) {  // iterate through every possibility
    loop lp = findLoop(grid, start);
    loops.push_back(lp);
  }

  // sort loops by size and return the longest
  return loops[0];
}


int main(int argc, char** argv) {
  auto grid = loadFile(argc, argv);  
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


std::vector<std::string> loadFile(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "Wrong amount of arguments.\n";
  }

  std::ifstream input;
  input.open(argv[1]);
  if(!input.is_open()) {
    std::cerr << "File not opened.\n";
  }
  
  std::string line;
  std::vector<std::string> result;
  
  while(std::getline(input, line)) result.push_back(line); // check if need to add borders
  return result;
}

