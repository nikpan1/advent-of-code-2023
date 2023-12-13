#include <iostream>
#include <fstream>
#include <vector> 

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
  
  void Connect(std::vector<Node>& nodes) {
    for(int i = 0; i < nodes.size(); i ++) {
      if(nodes[i].label == R_label) connection[1] = i;
      if(nodes[i].label == L_label) connection[0] = i;
    }
  }

  int turn(char c) { return connection[c == 'R']; }
};


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
  
  std::string line, moveset;
  std::getline(input, moveset);
  std::vector<Node> nodes; 
  std::getline(input, line); // empty line
  
  while(std::getline(input, line)) nodes.push_back(Node(line));   
  
  for(auto& n: nodes) n.Connect(nodes);
  std::cout << "|"<<moveset<<"|\n";
  int currNode = 0, steps = 0;
  while(nodes[currNode].label != "ZZZ") {
    currNode = nodes[currNode].turn(moveset[steps++%moveset.size()]);
  }
  
  std::cout << "result = " << steps;
  return 1;
}

