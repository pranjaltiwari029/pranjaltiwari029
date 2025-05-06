#include <stdio.h>
#include <stdlib.h>

// Define the structure for tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Define queue structure for level order operations
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

// Function to create a new tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ----------------- Queue Functions -----------------
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node* dequeue(Queue* q) {
    if (q->front == NULL)
        return NULL;
    QueueNode* temp = q->front;
    Node* node = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return node;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

// ----------------- Build Tree using Level Order -----------------
Node* buildTree(int arr[], int n) {
    if (n == 0)
        return NULL;

    Node* root = createNode(arr[0]);
    Queue* q = createQueue();
    enqueue(q, root);

    int i = 1;
    while (i < n) {
        Node* temp = dequeue(q);

        if (i < n) {
            temp->left = createNode(arr[i++]);
            enqueue(q, temp->left);
        }
        if (i < n) {
            temp->right = createNode(arr[i++]);
            enqueue(q, temp->right);
        }
    }
    return root;
}

// ----------------- Recursive Traversals -----------------
void preorderRecursive(Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

void inorderRecursive(Node* root) {
    if (root == NULL)
        return;
    inorderRecursive(root->left);
    printf("%d ", root->data);
    inorderRecursive(root->right);
}

void postorderRecursive(Node* root) {
    if (root == NULL)
        return;
    postorderRecursive(root->left);
    postorderRecursive(root->right);
    printf("%d ", root->data);
}

// ----------------- Level-order Traversal -----------------
void levelOrderTraversal(Node* root) {
    if (root == NULL)
        return;
    Queue* q = createQueue();
    enqueue(q, root);
    while (!isQueueEmpty(q)) {
        Node* temp = dequeue(q);
        printf("%d ", temp->data);
        if (temp->left)
            enqueue(q, temp->left);
        if (temp->right)
            enqueue(q, temp->right);
    }
}

// ----------------- Main Function -----------------
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6}; // Sample input
    int n = sizeof(arr) / sizeof(arr[0]);

    Node* root = buildTree(arr, n);

    printf("\nRecursive Preorder Traversal: ");
    preorderRecursive(root);

    printf("\nRecursive Inorder Traversal: ");
    inorderRecursive(root);

    printf("\nRecursive Postorder Traversal: ");
    postorderRecursive(root);

    printf("\n\nLevel-order Traversal: ");
    levelOrderTraversal(root);

    printf("\n");

    return 0;
}
