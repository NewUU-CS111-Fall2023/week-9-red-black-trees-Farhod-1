#include <iostream>
#include <stack>

class RedBlackTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        bool isRed;

        Node(int val) : data(val), left(nullptr), right(nullptr), isRed(true) {}
    };

    Node* root;

public:
    RedBlackTree() : root(nullptr) {}

    void Insert(int x) {
        root = InsertNode(root, x);
        root->isRed = false;
    }

    void printTree() {
        std::stack<Node*> nodes;
        Node* current = root;

        while (current != nullptr || !nodes.empty()) {
            while (current != nullptr) {
                nodes.push(current);
                current = current->right;
            }

            current = nodes.top();
            nodes.pop();

            std::cout << current->data << " ";

            current = current->left;
        }

        std::cout << std::endl;
    }

private:
    Node* InsertNode(Node* node, int x) {
        if (node == nullptr) {
            return new Node(x);
        }

        if (x < node->data) {
            node->left = InsertNode(node->left, x);
        } else if (x > node->data) {
            node->right = InsertNode(node->right, x);
        }

        return node;
    }
};

int main() {
    int N;
    std::cin >> N;

    RedBlackTree tree;

    for (int i = 0; i < N; i++) {
        int value;
        std::cin >> value;
        tree.Insert(value);
    }

    tree.printTree();

    return 0;
}
