#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector> 

// R - 1    |    L - 0

class Node {
private:
  std::string L_label, R_label;
  int connection[2];
  
public:
  std::string label;

  Node(std::string line) {
    label = line.substr(0, 3);
    L_label = line.substr(7, 3);
    R_label = line.substr(12, 3);
    
    connection[0] = 0; 
    connection[1] = 0;
  }
  
  void connect(std::vector<Node>& nodes) {
    for(int i = 0; i < nodes.size(); i ++) {
      if(nodes[i].label == R_label) connection[1] = i;
      if(nodes[i].label == L_label) connection[0] = i;
    }
  }

  int turn(char c) { return connection[c == 'R']; }
};

bool isStartNode(const Node& node) {  return node.label[2] == 'A'; }
bool isEndNode(const Node& node) { return node.label[2] == 'Z'; }


std::vector<int> getAllStartNodes(const std::vector<Node>& nodes) {
  std::vector<int> result;
  for(int i = 0; i < nodes.size(); i ++) if(isStartNode(nodes[i])) result.push_back(i);
  return result;
}


int64_t NWD(int64_t a, int64_t b) {
  int64_t p(0);
  while(b!=0) {
    p = b;
    b = a%b;
    a = p;
  }
  return a;
}


int64_t NWW(int64_t a, int64_t b) { return a*b/NWD(a,b); }

int64_t NWW(std::vector<int> values) {
  int64_t result = values[0];
  for(auto v : values) result = NWW(v, result);
  return result;
}


int main(int argc, char** argv) {
  if(argc != 2) std::cerr << "Wrong amount of arguments.\n"; 
  std::ifstream input(argv[1]);
  if(!input.is_open()) std::cerr << "File not opened.\n"; 
  
  std::string line, moveset;
  std::getline(input, moveset); 
  std::getline(input, line); // empty line


  std::vector<Node> nodes; 
  while(std::getline(input, line)) nodes.push_back(Node(line));   
  for(auto& n: nodes) n.connect(nodes);
  

  std::vector<int> results, currNodes = getAllStartNodes(nodes); 
  int size = moveset.size();
  for(auto& n : currNodes) {
    int steps = 0;
    while(!isEndNode(nodes[n])) n = nodes[n].turn(moveset[steps++%size]);
    results.push_back(steps);
  }

  std::cout << "NWW = " << NWW(results);
  return 1;
}

