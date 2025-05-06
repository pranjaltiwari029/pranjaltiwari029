#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* hashTable[MAX];
int table_size;

// Hash function
int hash(int key) {
    return key % table_size;
}

// Insert key
void insert(int key) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Search key
void search(int key) {
    int index = hash(key);
    Node* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->key == key) {
            printf("Found\n");
            return;
        }
        temp = temp->next;
    }
    printf("Not Found\n");
}

// Delete key
void deleteKey(int key) {
    int index = hash(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;
    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL) {
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Deleted\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Key not found\n");
}

// Display hash table
void display() {
    for (int i = 0; i < table_size; i++) {
        printf("[%d]: ", i);
        Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    printf("Enter size of hash table: ");
    scanf("%d", &table_size);

    // Initialize table
    for (int i = 0; i < table_size; i++) {
        hashTable[i] = NULL;
    }

    char command[20];
    int key;

    printf("Enter commands (insert <key>, search <key>, delete <key>, display, exit):\n");
    while (1) {
        scanf("%s", command);
        if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insert(key);
        } else if (strcmp(command, "search") == 0) {
            scanf("%d", &key);
            search(key);
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            deleteKey(key);
        } else if (strcmp(command, "display") == 0) {
            display();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}
