#include <stdio.h>
#include <stdlib.h>

// AVL Tree Node
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Utility to get max
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Get height of node
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Create a new node
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially at height 1
    return node;
}

// Right rotate
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

// Left rotate
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

// Get balance factor
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert into AVL Tree
Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);
    
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Equal keys not allowed
    
    // Update height
    node->height = 1 + max(height(node->left), height(node->right));
    
    int balance = getBalance(node);

    // If unbalanced, there are 4 cases:

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

// Find minimum node
Node* minValueNode(Node* node) {
    Node* current = node;
    
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete from AVL Tree
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;
    
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            
            free(temp);
        }
        else {
            Node* temp = minValueNode(root->right);
            
            root->key = temp->key;
            
            root->right = deleteNode(root->right, temp->key);
        }
    }
    
    if (root == NULL)
        return root;
    
    root->height = 1 + max(height(root->left), height(root->right));
    
    int balance = getBalance(root);
    
    // 4 cases:

    // Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

// Print Level Order Traversal
void printLevelOrder(Node* root) {
    if (root == NULL)
        return;
    
    Node* queue[100];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        Node* current = queue[front++];
        printf("%d ", current->key);
        
        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

int main() {
    Node* root = NULL;
    
    int insert_elements[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(insert_elements) / sizeof(insert_elements[0]);
    
    printf("Level-order after insertions:\n");
    for (int i = 0; i < n; i++) {
        root = insert(root, insert_elements[i]);
        printLevelOrder(root);
        printf("\n");
    }
    
    printf("\nDeleting 40...\n");
    root = deleteNode(root, 40);
    
    printf("Level-order after deletion:\n");
    printLevelOrder(root);
    printf("\n");
    
    return 0;
}
