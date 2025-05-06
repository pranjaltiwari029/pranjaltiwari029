#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// insertion
Node* insert(Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Inorder Traversal
void inorderTraversal(Node* root) {
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Searching
int search(Node* root, int key) {
    if (root == NULL)
        return 0;
    if (root->data == key)
        return 1;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Find minimum value node
Node* findMin(Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Deletion

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return NULL;
    
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node found
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Main function
int main() {
    Node* root = NULL;

    // Insert elements
    int elements[] = {56, 33, 71, 20, 49, 63, 88};
    int n = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, elements[i]);
    }

    printf("Inorder Traversal after insertions: ");
    inorderTraversal(root);
    printf("\n");
 
    // Delete nodes: 
    int toDelete[] = {20, 33, 49};
    for (int i = 0; i < 3; i++) {
        root = deleteNode(root, toDelete[i]);
    }

    printf("\nInorder Traversal after deletions: ");
    inorderTraversal(root);
    printf("\n");

    
    int toSearch[] = {71, 88};
    for (int i = 0; i < 2; i++) {
        if (search(root, toSearch[i]))
            printf("\nSearch %d: Found", toSearch[i]);
        else
            printf("\nSearch %d: Not Found", toSearch[i]);
    }

    printf("\n");
    return 0;
}
