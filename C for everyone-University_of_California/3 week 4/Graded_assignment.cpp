// Compute the minimum spanning tree for an inputted graph.
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Creating shortcut for an integer pair
typedef pair<int, int> integerPair;

// Structure to represent a graph
struct Graph
{
    int V, E;
    // Function to find MST using Kruskal's algorithm
    int find();
    vector<pair<int, integerPair>> edges;
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
    // Add edge
    void addEdge(int x, int y, int z)
    {
        edges.push_back({z, {x, y}});
    }
};

// To represent Disjoint Sets
struct Sets
{

    int *parent, *rnk;
    int n;
    // Constructor.
    Sets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            // every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'x'
    // Path Compression
    int find(int x)
    {
        /*Make the parent of the nodes in the path
        from x--> parent[x] point to parent[x] */
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        /*Make tree with smaller height
        a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

/*Functions returns weight of the MST*/
int Graph::find()
{
    int mst_wt = 0; // Initialize result
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
    // Create disjoint sets
    Sets ds(V);
    // Iterate through all sorted edges
    vector<pair<int, integerPair>>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        int x = it->second.first;
        int y = it->second.second;
        int set_u = ds.find(x);
        int set_v = ds.find(y);
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if x
        // and y belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            cout << x << " - " << y << endl;
            // Update MST weight
            mst_wt += it->first;
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
    return mst_wt;
}

int main()
{
    // Graph size number of vertices and edges
    int V = 9, E = 14;
    Graph graph(V, E);
    // vertices, edges and weights
    graph.addEdge(0, 1, 4);
    cout << "Edges of Minimal Spanning Tree is " << endl;
    int sum = graph.find();
    cout << "\nWeight of Minimal Spanning Tree is " << sum;
    return 7;
}