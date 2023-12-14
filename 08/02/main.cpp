#include <iostream>
#include <fstream>
#include <vector> 

// r - 1
// l - 0

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

bool isStartNode(Node node) {  return node.label[2] == 'A'; }
bool isEndNode(Node node) { return node.label[2] == 'Z'; }


std::vector<int> getAllStartNodes(const std::vector<Node>& nodes) {
  std::vector<int> result;
  for(int i = 0; i < nodes.size(); i ++) if(isStartNode(nodes[i])) result.push_back(i);
  return result;
}


bool areAllEndNodes(const std::vector<Node>& nodes, const std::vector<int>& currNodes) {
  for(const auto& i : currNodes) if(!isEndNode(nodes[i])) return false;
  return true;
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
  
  std::string line, moveset;
  std::getline(input, moveset);
  std::vector<Node> nodes; 
  std::getline(input, line); // empty line
  
  while(std::getline(input, line)) nodes.push_back(Node(line));   
  for(auto& n: nodes) n.Connect(nodes);
  std::vector<int> currNodes = getAllStartNodes(nodes); 

for( auto& n : currNodes) {
  int steps = 0, size = moveset.size();
  while(nodes[n].label[2] != 'Z') {
    n = nodes[n].turn(moveset[steps%size]);
    steps++;
  }
  std::cout << "result = " << steps << "\n";
}
  return 1;
}

