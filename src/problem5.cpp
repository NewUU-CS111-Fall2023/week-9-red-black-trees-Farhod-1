#include <iostream>
#include <vector>

struct Node {
    int value;
    int numChildren;
    std::vector<Node*> children;
};

void countChildren(Node* node) {
    if (node == nullptr) {
        return;
    }
    
    node->numChildren = node->children.size();
    
    for (Node* child : node->children) {
        countChildren(child);
    }
}

int main() {
    int N;
    std::cin >> N;
    
    std::vector<Node> nodes(N);
    
    for (int i = 0; i < N; i++) {
        std::cin >> nodes[i].value;
    }
    
    for (int i = 1; i < N; i++) {
        int parentIndex;
        std::cin >> parentIndex;
        
        nodes[parentIndex].children.push_back(&nodes[i]);
    }
    
    countChildren(&nodes[0]);
    
    for (const Node& node : nodes) {
        std::cout << "Node " << node.value << " has " << node.numChildren << " children" << std::endl;
    }
    
    return 0;
}
