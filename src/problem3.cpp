#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data) : data(data) {
        left = right = parent = nullptr;
        color = RED;
    }
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (node->right != nullptr)
            node->right->parent = node;

        rightChild->parent = node->parent;

        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (node->left != nullptr)
            node->left->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    void insertFix(Node* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

    void deleteFix(Node* node) {
        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                Node* sibling = node->parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    rotateLeft(node->parent);
                    node = root;
                }
            } else {
                Node* sibling = node->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }

        node->color = BLACK;
    }

    void deleteNode(Node* node, int data) {
        Node* z = nullptr;
        Node* x, * y;

        while (node != nullptr) {
            if (node->data == data) {
                z = node;
                break;
            }

            if (node->data <= data)
                node = node->right;
            else
                node = node->left;
        }

        if (z == nullptr)
            return;

        y = z;
        bool yOriginalColor = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        if (yOriginalColor == BLACK)
            deleteFix(x);

        delete z;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    Node* minimum(Node* node) {
        while (node->left != nullptr)
            node = node->left;

        return node;
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void insert(int data) {
        Node* newNode = new Node(data);
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;

            if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        newNode->parent = parent;

        if (parent == nullptr)
            root = newNode;
        else if (data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        insertFix(newNode);
    }

    void deleteNode(int data) {
        deleteNode(root, data);
    }
};

int main() {
    int N;
    cin >> N;

    RedBlackTree tree;

    for (int i = 0; i < N; i++) {
        int value;
        cin >> value;
        tree.insert(value);
    }

    // Perform operations on the tree

    return 0;
}
