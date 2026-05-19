#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100
#define MAXE 5000

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double weight;
} Edge;

int parent[MAXN];

int find(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void unionSet(int a, int b) {
    parent[find(a)] = find(b);
}

double distance(Point a, Point b) {
    return sqrt((b.x - a.x) * (b.x - a.x) +
                (b.y - a.y) * (b.y - a.y));
}

int compare(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;

    if (e1->weight > e2->weight)
        return 1;
    if (e1->weight < e2->weight)
        return -1;
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        Point points[MAXN];
        Edge edges[MAXE];
        int edgeCount = 0;

        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }

        // Create all edges
        for (int u = 0; u < n; u++) {
            for (int v = u + 1; v < n; v++) {
                edges[edgeCount].u = u;
                edges[edgeCount].v = v;
                edges[edgeCount].weight = distance(points[u], points[v]);
                edgeCount++;
            }
        }

        // Sort edges
        qsort(edges, edgeCount, sizeof(Edge), compare);

        // Initialize DSU
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        double total_ink = 0.0;
        int edges_added = 0;

        // Kruskal
        for (int i = 0; i < edgeCount; i++) {
            int set_u = find(edges[i].u);
            int set_v = find(edges[i].v);

            if (set_u != set_v) {
                unionSet(set_u, set_v);
                total_ink += edges[i].weight;
                edges_added++;

                if (edges_added == n - 1)
                    break;
            }
        }

        printf("%.2lf\n", total_ink);

        if (T)
            printf("\n");
    }

    return 0;
}