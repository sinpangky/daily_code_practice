#include <stdio.h>
#include <stdlib.h>

// Binary Tree Node
typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} BinaryTree, *BiTree;

typedef struct MyQueue {
  BiTree* data;
  int front;
  int rear;
  int size;
}Queue;


BiTree createBinaryTree(int arr[], int size) {
  if (size == 0)
    return NULL;

  BiTree root = (BiTree)malloc(sizeof(BinaryTree));
  root->data = arr[0];
  root->left = NULL;
  root->right = NULL;

  Queue queue;
  queue.data = (BiTree*)malloc(size * sizeof(BiTree));
  queue.front = 0;
  queue.rear = 0;
  queue.size = size;

  queue.data[queue.rear++] = root;

  int i = 1;
  while (i < size) {
    BiTree node = queue.data[queue.front++];
    if (i < size) {
      BiTree leftChild = (BiTree)malloc(sizeof(BinaryTree));
      leftChild->data = arr[i++];
      leftChild->left = NULL;
      leftChild->right = NULL;
      node->left = leftChild;
      queue.data[queue.rear++] = leftChild;
    }
    if (i < size) {
      BiTree rightChild = (BiTree)malloc(sizeof(BinaryTree));
      rightChild->data = arr[i++];
      rightChild->left = NULL;
      rightChild->right = NULL;
      node->right = rightChild;
      queue.data[queue.rear++] = rightChild;
    }
  }

  free(queue.data);
  return root;
}


void preOrderTraversal(BiTree root) {
  if (root == NULL)
    return;

  printf("%d ", root->data);
  preOrderTraversal(root->left);
  preOrderTraversal(root->right);
}


void inOrderTraversal(BiTree root) {
  if (root == NULL)
    return;

  inOrderTraversal(root->left);
  printf("%d ", root->data);
  inOrderTraversal(root->right);
}


void postOrderTraversal(BiTree root) {
  if (root == NULL)
    return;

  postOrderTraversal(root->left);
  postOrderTraversal(root->right);
  printf("%d ", root->data);
}

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  int size = sizeof(arr) / sizeof(arr[0]);

  BiTree root = createBinaryTree(arr, size);

  printf("Pre-order traversal: ");
  preOrderTraversal(root);
  printf("\n");

  printf("In-order traversal: ");
  inOrderTraversal(root);
  printf("\n");

  printf("Post-order traversal: ");
  postOrderTraversal(root);
  printf("\n");

  return 0;
}

//完成冒泡，选择，插入排序