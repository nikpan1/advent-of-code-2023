#include <iostream>
#include <fstream>
#include <vector> 
#include <unordered_map>

std::unordered_map<char, int> map = {{'L', 0}, {'R', 1}};


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
    std::cout <<"";
  }
  
  void Connect(std::vector<Node>& nodes) {
    for(auto& node : nodes) {
      if(node.label == this->R_label) connection[1] = &node;
      else if(node.label == this->L_label) connection[0] = &node;
    }
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
    os << obj.label << " = (" << obj.L_label << ", " << obj.R_label << ")[" << (obj.connection[0] != nullptr && obj.connection[1] != nullptr) <<"]\n"; 
    return os;
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

  while(std::getline(input, line)) {
    nodes.push_back(Node(line));   
  }
  
  for(auto n: nodes) n.Connect(nodes);
  for(auto n: nodes) std::cout << n;

  


  return 1;
}
