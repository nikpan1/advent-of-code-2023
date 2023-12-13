#include <iostream>
#include <fstream>
#include <vector> 

class Node {
private:
  std::string L_label, R_label;
public:
  Node* connection[2];
  std::string label;

  Node(std::string line) {
    label = line.substr(0, 3);
    L_label = line.substr(7, 3);
    R_label = line.substr(12, 3);
    connection[0] = nullptr;
    connection[1] = nullptr;
  }
  
  void Connect(std::vector<Node>& nodes) {
    for(auto& node : nodes) {
      if(node.label == R_label) connection[1] = &node;
      if(node.label == L_label) connection[0] = &node;
    }
  }

  Node* turn(char c) {
  if(c == 'R') return connection[1];
  if(c == 'L') return connection[0];
  return nullptr;
  }

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

  Node* currentNode = &nodes[0];   // we could also hold the index of the std::vector instead of
  int steps = 0, pivot = 0;
  while(currentNode->label != "ZZZ") {
    currentNode = currentNode->turn(moveset[pivot]);
    if(pivot == moveset.size() - 1) pivot = 0;
    else pivot ++;
    steps ++;
  }
  
  std::cout << "result = " << steps;
  return 1;
}

