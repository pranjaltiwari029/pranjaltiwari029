#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define EMPTY -1
#define DELETED -2

int table[MAX];
int table_size;

// Hash function
int hash(int key) {
    return key % table_size;
}

// Insert key
void insert(int key) {
    int index = hash(key);
    int original_index = index;
    int i = 0;

    while (table[index] != EMPTY && table[index] != DELETED) {
        i++;
        index = (original_index + i) % table_size;
        if (i == table_size) {
            printf("Hash Table is full! Cannot insert.\n");
            return;
        }
    }
    table[index] = key;
}

// Search key
void search(int key) {
    int index = hash(key);
    int original_index = index;
    int i = 0;

    while (table[index] != EMPTY) {
        if (table[index] == key) {
            printf("Found at index %d\n", index);
            return;
        }
        i++;
        index = (original_index + i) % table_size;
        if (i == table_size) {
            break;
        }
    }
    printf("Not Found\n");
}

// Delete key
void deleteKey(int key) {
    int index = hash(key);
    int original_index = index;
    int i = 0;

    while (table[index] != EMPTY) {
        if (table[index] == key) {
            table[index] = DELETED;
            printf("Deleted\n");
            return;
        }
        i++;
        index = (original_index + i) % table_size;
        if (i == table_size) {
            break;
        }
    }
    printf("Key not found\n");
}

// Display hash table
void display() {
    for (int i = 0; i < table_size; i++) {
        if (table[i] == EMPTY) {
            printf("[%d]: EMPTY\n", i);
        } else if (table[i] == DELETED) {
            printf("[%d]: DELETED\n", i);
        } else {
            printf("[%d]: %d\n", i, table[i]);
        }
    }
}

int main() {
    printf("Enter size of hash table: ");
    scanf("%d", &table_size);

    // Initialize table
    for (int i = 0; i < table_size; i++) {
        table[i] = EMPTY;
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
