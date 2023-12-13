// // Write a program to calculate and display the black height of every node.
// ● First line is N - number of nodes to input
// ● Second line is values of nodes



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