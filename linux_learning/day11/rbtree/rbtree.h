#include <iostream>

#define RED 0
#define BLACK 1

typedef int Type;
typedef struct RBTreeNode {
  unsigned char color;
  Type key;
  struct RBTreeNode* left;
  struct RBTreeNode* right;
  struct RBTreeNode* parent;
}Node, *RBTree;

typedef struct rb_root {
  Node* node;
}RBRoot;

void PrintRBTree(RBRoot* root);