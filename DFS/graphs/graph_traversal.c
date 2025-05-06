#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];     // Adjacency matrix
int visited[MAX];      // Visited array
int queue[MAX];        // Queue for BFS
int front = -1, rear = -1;

// Function to insert into queue
void enqueue(int v) {
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    queue[++rear] = v;
}

// Function to delete from queue
int dequeue() {
    if (front == -1 || front > rear)
        return -1;
    return queue[front++];
}

// BFS Traversal
void bfs(int start, int V) {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    printf("BFS Traversal: ");

    while (front <= rear) {
        int current = dequeue();
        printf("%d ", current);

        for (int i = 0; i < V; i++) {
            if (adj[current][i] && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

// DFS Traversal (Recursive)
void dfs_util(int v, int V) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visited[i])
            dfs_util(i, V);
    }
}

void dfs(int start, int V) {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    printf("DFS Traversal: ");
    dfs_util(start, V);
    printf("\n");
}

// Function to find connected components
void find_connected_components(int V) {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    int count = 0;
    printf("Connected Components:\n");

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            count++;
            printf("Component %d: ", count);
            dfs_util(i, V);
            printf("\n");
        }
    }
    printf("Total Connected Components: %d\n", count);
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    // Initialize adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = 0;

    printf("Enter edges (pairs of vertices):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1; // Since undirected
    }

    printf("Enter starting vertex for traversal: ");
    int start;
    scanf("%d", &start);

    // Print adjacency matrix
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    bfs(start, V);
    dfs(start, V);
    printf("\n");
    find_connected_components(V);

    return 0;
}
