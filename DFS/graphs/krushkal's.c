#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent an edge
typedef struct {
    int u, v, w;
} Edge;

int adj[MAX][MAX];
int parent[MAX];

// Find function for Union-Find
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]); // Path compression
}

// Union function for Union-Find
void union_set(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu != pv)
        parent[pu] = pv;
}

// Compare function for qsort
int compare(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->w - e2->w;
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    // Initialize adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = 0;

    Edge edges[E];

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u][v] = w;
        adj[v][u] = w; // Since undirected
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }

    // Print adjacency matrix
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    // Sort edges by weight
    qsort(edges, E, sizeof(Edge), compare);

    // Initialize Union-Find structure
    for (int i = 0; i < V; i++)
        parent[i] = i;

    printf("\nEdges in MST:\n");
    int total_weight = 0;
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            printf("%d - %d : %d\n", u, v, w);
            total_weight += w;
            union_set(u, v);
        }
    }

    printf("\nTotal weight of MST: %d\n", total_weight);

    return 0;
}
