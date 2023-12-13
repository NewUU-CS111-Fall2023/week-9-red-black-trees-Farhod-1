// Write a C++ class that describes the binarySearchTree class, add all necessary
// methods(add, delete, print, height, depth, etc.).
// ● Create a binarySearchTree object.
// ● Insert values 34, 62, 1, 46, 11, 0, 32, 3, 1, 2
// ● Print it using recursive method in a in-order traversal
// ● Consider turning it into an AVL tree
// ● Print the result
// ● First input line is N - size of a tree

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    int numChildren;
    vector<Node*> children;
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
    cin >> N;
    
    vector<Node> nodes(N);
    
    for (int i = 0; i < N; i++) {
        cin >> nodes[i].value;
    }
    
    for (int i = 1; i < N; i++) {
        int parentIndex;
        cin >> parentIndex;
        
        nodes[parentIndex].children.push_back(&nodes[i]);
    }
    
    countChildren(&nodes[0]);
    
    for (const Node& node : nodes) {
        cout << "Node " << node.value << " has " << node.numChildren << " children" << endl;
    }
    
    return 0;
}

