#include <stdio.h>
#include <stdlib.h>

// Define a BST node
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Insert into BST
Node* insert(Node* root, int key) {
    if (root == NULL)
        return newNode(key);
    
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    
    return root;
}

// Inorder Traversal (prints sorted elements)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

int main() {
    int elements[] = {5, 3, 7, 2, 8, 4};
    int n = sizeof(elements) / sizeof(elements[0]);
    
    Node* root = NULL;
    
    // Insert elements into BST
    for (int i = 0; i < n; i++) {
        root = insert(root, elements[i]);
    }
   

    printf("Sorted: ");
    inorderTraversal(root);
    printf("\n");
    
    return 0;
}
