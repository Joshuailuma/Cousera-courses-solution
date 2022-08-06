// Implement Dijkstra's Algorithm

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <ctime>
#include <cstdlib>
using namespace std;

//Define no_ of edge path between nodes
const int num_edge_path = 999999;



// An inline function that change numbers to alphabetic characcters
inline char change_int_to_character(int n)
{
    if (n < 26)
        return static_cast<char>('A' + n);
    else
        return static_cast<char>('a' + n - 26);
}

// An overload operator to print some variables
ostream &operator<<(ostream &result, list<char> character)
{
    list<char>::iterator i;
    for (i = character.begin(); i != character.end(); ++i)
        result << *i << " ";
    return result;
}


typedef struct node_struct Node;
struct node_struct
{
    int number;
    int weight;
    list<Node> edges;
};


class Class_Graph
{
public:
    Class_Graph(); 
    Class_Graph(int vertices_number, int initialValue);
    char get_node_value(int x);
    void set_node_value(char x, char name);
    int get_edge_value(char x, char y);
    void set_edge_value(char x, char y, int value);
    bool adjacent(char x, char y);
    list<char> neighbors(char x);
    int V();
    int E();
    list<char> vertices();
    void show();

private:
    int numNodeV;                   // Number of nodes of the Class_Graph
    int numEdgeE;                   // Number of edges of the Class_Graph
    vector<char> nodeNames;    
    map<char, int> nodeNumbers; 
    list<Node> adjacent_list;         // Adjacency list representing the Class_Graph
};

// Default constructor of Class_Grap
// Create an empty graph by first setting to 0
Class_Graph::Class_Graph()
{
    numNodeV = 0;
    numEdgeE = 0;
    adjacent_list.clear();
}

// Constructor of Class_Graph
// Initialize number of nodes 
Class_Graph::Class_Graph(int vertices_number, int initialValue = num_edge_path)
{
    numNodeV = vertices_number;
    numEdgeE = 0;
    nodeNames.resize(vertices_number);
    for (int x = 0; x < numNodeV; ++x)
    {
        nodeNames[x] = change_int_to_character(x);
        nodeNumbers[change_int_to_character(x)] = x;
    }

    adjacent_list.clear();
    for (int i = 0; i < vertices_number; ++i)
    {
        Node newNode;
        newNode.number = i;
        newNode.weight = 0;
        newNode.edges.clear();
        adjacent_list.push_back(newNode);
    }
}

// Pass in name and return the node name from nodeNames
char Class_Graph::get_node_value(int nme)
{
    return nodeNames[nme];
}

// link node name to value and vice versa
void Class_Graph::set_node_value(char x, char name)
{
    int numX = nodeNumbers[x]; 
    nodeNames[numX] = name;  
    nodeNumbers[name] = numX;  
}

// Return the result of edge value between 'x' and 'y' or return num_edge_path if edge does not exist
int Class_Graph::get_edge_value(char x, char y)
{
    for (list<Node>::iterator i = adjacent_list.begin(); i != adjacent_list.end(); ++i)
    {
        if ((*i).number == nodeNumbers[x])
            for (list<Node>::iterator j = (*i).edges.begin(); j != (*i).edges.end(); ++j)
            {
                if ((*j).number == nodeNumbers[y])
                    return (*j).weight;
            }
    }
    return num_edge_path;
}

// Set edge value
void Class_Graph::set_edge_value(char x, char y, int value)
{
    bool found;
    for (list<Node>::iterator i = adjacent_list.begin(); i != adjacent_list.end(); ++i)
    {
        if ((*i).number == nodeNumbers[x])
        {
            found = false;
            for (list<Node>::iterator j = (*i).edges.begin(); j != (*i).edges.end(); ++j)
            {
                if ((*j).number == nodeNumbers[y])
                {
                    (*j).weight = value;
                    found = true;
                }
            }
            if (!found)
            {
                Node newNodeY;
                newNodeY.number = nodeNumbers[y];
                newNodeY.weight = value;
                newNodeY.edges.clear();
                (*i).edges.push_back(newNodeY);
            }
        }
    }

    // Add x in adjacent list of y
    for (list<Node>::iterator i = adjacent_list.begin(); i != adjacent_list.end(); ++i)
    {
        if ((*i).number == nodeNumbers[y])
        {
            found = false;
            for (list<Node>::iterator j = (*i).edges.begin(); j != (*i).edges.end(); ++j)
            {
                if ((*j).number == nodeNumbers[x])
                {
                    (*j).weight = value;
                    found = true;
                }
            }
            if (!found)
            {
                Node newNodeX;
                newNodeX.number = nodeNumbers[x];
                newNodeX.weight = value;
                newNodeX.edges.clear();
                (*i).edges.push_back(newNodeX);
                ++numEdgeE;
            }
        }
    }
}

// This function returns true if x and y are adjacent to each other
bool Class_Graph::adjacent(char x, char y)
{
    for (list<Node>::iterator i = adjacent_list.begin(); i != adjacent_list.end(); ++i)
    {
        if ((*i).number == nodeNumbers[x])
        {
            for (list<Node>::iterator j = (*i).edges.begin(); j != (*i).edges.end(); ++j)
            {
                if ((*j).number == nodeNumbers[y])
                {
                    return true;
                }
            }
        }
    }
    return false;
}



list<char> Class_Graph::neighbors(char x)
{
    list<char> adjNodes;
    for (list<Node>::iterator i = adjacent_list.begin(); i != adjacent_list.end(); ++i)
    {
        if ((*i).number == nodeNumbers[x])
        {
            for (list<Node>::iterator j = (*i).edges.begin(); j != (*i).edges.end(); ++j)
            {
                adjNodes.push_back(nodeNames[(*j).number]);
            }
        }
    }
    return adjNodes;
}

// Return the number of nodes in our Class_Graph
int Class_Graph::V()
{
    return numNodeV;
}

// Return the number of edges in our Class_Graph
int Class_Graph::E()
{
    return numEdgeE;
}

// Return a list having all nodes in our Class_Graph
list<char> Class_Graph::vertices()
{
    list<char> nodes;
    for (list<Node>::iterator i = adjacent_list.begin(); i != adjacent_list.end(); ++i)
    {
        nodes.push_back(nodeNames[(*i).number]);
    }
    return nodes;
}



// Print out adjacency list representing the Class_Graph
void Class_Graph::show()
{
    cout << "  ";
    for (list<Node>::iterator i = adjacent_list.begin(); i != adjacent_list.end(); ++i)
        cout << " " << nodeNames[(*i).number];
    cout << endl;
    for (list<Node>::iterator i = adjacent_list.begin(); i != adjacent_list.end(); ++i)
    {
        cout << " " << nodeNames[(*i).number];
        int shift = 0;
        for (list<Node>::iterator j = (*i).edges.begin(); j != (*i).edges.end(); ++j)
        {
            int walk = (*j).number - shift;
            for (int k = 0; k < walk; ++k)
            {
                cout << " -";
                shift++;
            }
            cout << " " << (*j).weight;
            shift++;
        }
        while (shift < numNodeV)
        {
            cout << " -";
            shift++;
        }
        cout << endl;
    }
}



struct node_structInfo
{
    char nodeName; // Node name
    int shortestDistance;   // Shortest distance to nodeName
    char before;  // Node that precede nodeName in the shortest path
};
typedef struct node_structInfo NodeInfo;

// Compare Nodes return boolean value accordingly
bool compareNodeName(NodeInfo &node1, NodeInfo &node2)
{
    if (node1.nodeName < node2.nodeName)
        return true;
    return false;
}



// Compare Node by shortestDistance
bool compareShortestDistance(NodeInfo &node1, NodeInfo &node2)
{
    if (node1.shortestDistance < node2.shortestDistance)
        return true;
    return false;
}


// Return true if two NodeInfo have the same nodeName
bool operator==(NodeInfo &node1, NodeInfo &node2)
{
    if (node1.nodeName == node2.nodeName)
        return true;
    return false;
}


class InfoStore
{
public:
    InfoStore();
    void changePr(NodeInfo n);
    void minimumPr();
    bool contains(NodeInfo n);
    bool isBetter(NodeInfo n);
    void insert(NodeInfo n);
    NodeInfo top();
    int size();

private:
    list<NodeInfo> pq; // List of nodes
};

// Constructor of InfoStore Class
InfoStore::InfoStore()
{
    pq.clear();
}

void InfoStore::changePr(NodeInfo j)
{
    for (list<NodeInfo>::iterator i = pq.begin(); i != pq.end(); ++i)
        if ((*i) == j)
        {
            (*i).shortestDistance = j.shortestDistance;
            (*i).before = j.before;
        }
    pq.sort(compareShortestDistance);
}

// Remove the node with lower shortestDistance
void InfoStore::minimumPr()
{
    if (!pq.empty())
    {
        pq.pop_front();
    }
}

// Returne true if there is a node named j
bool InfoStore::contains(NodeInfo j)
{
    for (list<NodeInfo>::iterator i = pq.begin(); i != pq.end(); ++i)
        if ((*i).nodeName == j.nodeName)
            return true;
    return false;
}

// Return true if node j has a lower shortestDistance
bool InfoStore::isBetter(NodeInfo j)
{
    for (list<NodeInfo>::iterator i = pq.begin(); i != pq.end(); ++i)
        if ((*i).nodeName == j.nodeName)
            if ((*i).shortestDistance > j.shortestDistance)
                return true;
    return false;
}

// Insert node j
void InfoStore::insert(NodeInfo j)
{
    pq.push_back(j);
    pq.sort(compareShortestDistance);
}

// Return the node with lower shortestDistance
NodeInfo InfoStore::top()
{
    NodeInfo n = {' ', 0};
    if (!pq.empty())
    {
        list<NodeInfo>::iterator i = pq.begin();
        n.nodeName = (*i).nodeName;
        n.shortestDistance = (*i).shortestDistance;
        n.before = (*i).before;
    }
    return n;
}

// Return the number of elements in InfoStore
int InfoStore::size()
{
    return pq.size();
}

//To find the shortest path between 2 nodes
class DShortestPath
{
public:
    DShortestPath();
    DShortestPath(Class_Graph g);
    list<char> path(char u, char v);
    int path_size(char u, char v);

private:
    Class_Graph graph; 
};

// A Constructor 
DShortestPath::DShortestPath()
{
}

// t stores Class_Graph
DShortestPath::DShortestPath(Class_Graph g)
{
    graph = g;
}

// Return a list containing the list of nodes in the shortest path between 'u' and 'v'
list<char> DShortestPath::path(char u, char v)
{
    // Initialize candidates list with all nodes
    list<char> candidates = graph.vertices(), desiredPath;
    list<NodeInfo> minPaths;
    InfoStore p;
    NodeInfo lastSelected, n;

    // Calculate shortest path from 'u' to 'v' (Dijkstra's Algorithm)
    candidates.remove(u);      // Remove 'u' from candidates list
    lastSelected.nodeName = u; // Set 'u' as lastSelected
    lastSelected.shortestDistance = 0;
    lastSelected.before = u;
    minPaths.push_back(lastSelected); // Add 'u' to minPath list
    while ((!candidates.empty()) && (lastSelected.nodeName != v))
    {
        // For each node in candidate list calculate the cost to reach that candidate before lastSelected
        for (list<char>::iterator i = candidates.begin(); i != candidates.end(); ++i)
        {
            n.nodeName = *i;
            n.shortestDistance = lastSelected.shortestDistance + graph.get_edge_value(lastSelected.nodeName, *i);
            n.before = lastSelected.nodeName;
            if (!p.contains(n)) 
                p.insert(n);
            else if (p.isBetter(n)) 
                p.changePr(n);
        }
        lastSelected = p.top();                  
        p.minimumPr();                          
        minPaths.push_back(lastSelected);
        candidates.remove(lastSelected.nodeName); 
    }

    // Go backward from 'v' to 'u' adding nodes in that path to desiredPath list
    lastSelected = minPaths.back();
    desiredPath.push_front(lastSelected.nodeName);
    while (lastSelected.nodeName != u)
    {
        for (list<NodeInfo>::iterator i = minPaths.begin(); i != minPaths.end(); ++i)
            if ((*i).nodeName == lastSelected.before)
            {
                lastSelected = (*i);
                desiredPath.push_front(lastSelected.nodeName);
            }
    }
    return desiredPath;
}

// Return the size of the shortest path between 'u' and 'v'
int DShortestPath::path_size(char u, char v)
{
    int pathCost = 0;
    list<char> sp;
    char current, next;

    // Calculate the shortest path from 'u' to 'v' and then sum up edge weights in this path
    sp = path(u, v);
    current = sp.front();
    sp.pop_front();
    for (list<char>::iterator i = sp.begin(); i != sp.end(); ++i)
    {
        next = (*i);
        pathCost += graph.get_edge_value(current, next);
        current = next;
    }
    return pathCost;
}


// Generate random graphs and run simulations
class GraphGenerator
{
public:
    GraphGenerator();
    Class_Graph randomClass_Graph(int vert, double density, int shortestDistanceEdge, int maximumDistanceEdge);
    void run(Class_Graph result);

private:
};


// Constructor of GraphGenerator Class
GraphGenerator::GraphGenerator()
{
    srand(time(NULL));
}

// Return a random Class_Graph generated with number of nodes, density and edge weight range informed
Class_Graph GraphGenerator::randomClass_Graph(int numNodeVert, double density, int shortestDistanceEdge, int maximumDistanceEdge)
{
    int randDistEdge;
    char vertix_source, vertix_distance;

    Class_Graph result(numNodeVert);

    for (int i = 0; i < result.V(); ++i)
        for (int j = i + 1; j < result.V(); ++j)
        {
            double p = ((static_cast<double>(rand())) / RAND_MAX); // Generate random probability
            if (p < density)                                       // If random probability is less than density, edge (i,j) will be set
            {
                randDistEdge = rand() % (maximumDistanceEdge - shortestDistanceEdge) + shortestDistanceEdge; // Generate random edge weight
                vertix_source = change_int_to_character(i);
                vertix_distance = change_int_to_character(j);
                result.set_edge_value(vertix_source, vertix_distance, randDistEdge);
            }
        }

    return result;
}

// Run a simulation finding the shortest paths in a given graph
void GraphGenerator::run(Class_Graph result)
{
    static int turn = 0;

    cout << endl
         << "Simulation number " << ++turn << "." << endl;

    // Print graph info
    double d = static_cast<double>(result.E()) / ((static_cast<double>(result.V()) * static_cast<double>(result.V()) - 1) / 2) * 100;
    cout << "Vertices: " << result.V() << endl;
    cout << "Edges: " << result.E() << ". density: " << d << "%" << endl;

    // Print shortest path info
    list<char> path = result.vertices();
    cout << endl
         << "Vertices: " << path << endl;
    int vertix_reacheded = 0, path_size_sum = 0, averagePathSize = 0;
    DShortestPath shortestp(result);
    for (list<char>::iterator i = ++path.begin(); i != path.end(); ++i)
    {
        char src = path.front();
        char distance = (*i);
        list<char> p = shortestp.path(src, distance);
        int ps = shortestp.path_size(src, distance);
        if (ps != num_edge_path)
            cout << "The shortestPath from" << src << " to " << distance << ": " << ps << " is " << p << endl;
        else
            cout << "ShortestPath (" << src << " to " << distance << "): " << endl;
        if (ps != num_edge_path)
        {
            vertix_reacheded++;
            path_size_sum += ps; 
        }
    }


    // Calculate average shortest path
    if (vertix_reacheded != 0)
        averagePathSize = path_size_sum / vertix_reacheded;
    else
        averagePathSize = 0;
    cout << endl
         << "Average shortest Path Size (vertices reached: " << vertix_reacheded << " sum of path size: " << path_size_sum << "): " << averagePathSize << endl;
}



int main()
{
    GraphGenerator simulation;
    Class_Graph graph;

    // A graph of 50 nodes with a distance range of 1.0 to 10.0 with ddensity 20%
    graph = simulation.randomClass_Graph(50, 0.2, 1, 10);
    simulation.run(graph);

    // Creates a graph with 50 nodes / density 40% and then run simulation
    graph = simulation.randomClass_Graph(50, 0.4, 1, 10);
    simulation.run(graph);

    return 0;
}