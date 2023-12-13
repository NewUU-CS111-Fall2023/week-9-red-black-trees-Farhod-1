#include <iostream>
#include <queue>
using namespace std;

enum Color { RED, BLACK };

class Node {
public:
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int data) {
        this->data = data;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }

        rightChild->parent = node->parent;

        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }

        leftChild->parent = node->parent;

        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->left) {
            node->parent->left = leftChild;
        } else {
            node->parent->right = leftChild;
        }

        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixViolation(Node* node) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while (node != root && node->color != BLACK && node->parent->color == RED) {
            parent = node->parent;
            grandparent = node->parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                Node* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = BLACK;
    }

    void printTreeUtil(Node* node, int space) {
        if (node == nullptr) {
            return;
        }

        space += 5;

        printTreeUtil(node->right, space);

        cout << endl;
        for (int i = 5; i < space; i++) {
            cout << " ";
        }
        cout << node->data << "(" << (node->color == RED ? "RED" : "BLACK") << ")" << endl;

        printTreeUtil(node->left, space);
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void Insert(int data) {
        Node* newNode = new Node(data);

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;

            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        newNode->parent = parent;

        if (parent == nullptr) {
            root = newNode;
        } else if (data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixViolation(newNode);
    }

    void printTree() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        printTreeUtil(root, 0);
    }
};

