#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 99999

int adj[MAX][MAX];
int visited[MAX];

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    // Initialize adjacency matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j)
                adj[i][j] = 0;
            else
                adj[i][j] = INF;
        }
    }

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u][v] = w;
        adj[v][u] = w; // Undirected graph
    }

    int start;
    printf("Enter starting vertex: ");
    scanf("%d", &start);

    // Print adjacency matrix
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adj[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    // Initialize visited array
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    visited[start] = 1;
    int edges_accepted = 0;
    int total_weight = 0;

    printf("\nEdges in MST:\n");

    while (edges_accepted < V - 1) {
        int min = INF;
        int u = -1, v = -1;

        for (int i = 0; i < V; i++) {
            if (visited[i]) {
                for (int j = 0; j < V; j++) {
                    if (!visited[j] && adj[i][j] < min) {
                        min = adj[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u != -1 && v != -1) {
            printf("%d - %d : %d\n", u, v, adj[u][v]);
            total_weight += adj[u][v];
            visited[v] = 1;
            edges_accepted++;
        }
    }

    printf("\nTotal weight of MST: %d\n", total_weight);

    return 0;
}
