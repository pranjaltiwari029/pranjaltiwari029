#include <stdio.h>

#define MAX 100
#define INF 99999

int dist[MAX][MAX];
int next[MAX][MAX]; // For path reconstruction

void printPath(int u, int v) {
    if (next[u][v] == -1) {
        printf("No path");
        return;
    }
    printf("%d", u);
    while (u != v) {
        u = next[u][v];
        printf(" -> %d", u);
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    // Initialize distance and next matrices
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
            next[i][j] = -1;
        }
    }

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        dist[u][v] = w;
        next[u][v] = v;
    }

    // Print initial adjacency matrix
    printf("\nInitial Adjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Print final distance matrix
    printf("\nFinal Distance Matrix (Shortest Paths):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    // Sample path reconstruction
    int u, v;
    printf("\nEnter two vertices to reconstruct path (u v): ");
    scanf("%d %d", &u, &v);
    printf("Path from %d to %d: ", u, v);
    printPath(u, v);
    printf("\n");

    return 0;
}
