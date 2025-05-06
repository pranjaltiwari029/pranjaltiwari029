#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 99999

int adj[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top = -1;

// Push to stack
void push(int v) {
    stack[++top] = v;
}

// Pop from stack
int pop() {
    return stack[top--];
}

// Topological Sort (DFS based)
void dfs(int v, int V) {
    visited[v] = 1;
    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visited[i]) {
            dfs(i, V);
        }
    }
    push(v);
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    // Initialize adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1; // Weight is 1
    }

    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    // Print adjacency matrix
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    // Initialize visited array
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    // Perform Topological Sort
    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i, V);
    }

    printf("\nTopological Order: ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");

    // Initialize distances
    int dist[MAX];
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[source] = 0;

    // Shortest Path using Topological Order
    while (top != -1) {
        int u = pop();
        if (dist[u] != INF) {
            for (int v = 0; v < V; v++) {
                if (adj[u][v]) {
                    if (dist[u] + 1 < dist[v]) {
                        dist[v] = dist[u] + 1;
                    }
                }
            }
        }
    }

    printf("\nShortest distances from source %d:\n", source);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("%d -> INF\n", i);
        else
            printf("%d -> %d\n", i, dist[i]);
    }

    return 0;
}
