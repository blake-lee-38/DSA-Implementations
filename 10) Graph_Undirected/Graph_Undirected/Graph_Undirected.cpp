//
// This file implements an undirected graph
// with both tree traverse algorithms, as well
// as Dijkstra's shortest path algorithm
//  
// Graph is based on matrix-based implementation
// 
// For simplicity, assumes no satellite data, focuses on 
// dealing with integers (node numbers) only 
// 
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <climits>
using namespace std;


//
// Used to test Dijkstra's Algorithm: a Result object is returned with
// the length of the shortest path, the weight of the shortest path,
// and the node sequence of the shortest path
//
class Result {
public:
    int length;
    int weight;
    int* path;
};

// 
// Graph class: undirected graph with matrix implementation:
// Has "size" nodes labeled from 0 to size - 1
//
class Graph {

private:

    // Holds the graph matrix 
    int** m;

    // Holds the number of nodes in graph 
    int size;

    // Helper method for Breadth-First traverse and
    // isPath() method
    vector<int> BFTHelper(int i);

    // Helper method for Dijkstra's algorithm: takes in
    // pointers to an integer array for distances from
    // the sources node and a boolean array to represent
    // a visited node or not: Returns the index of the 
    // node with the least distance that is also unvisited
    int findMin(int* distances, bool* visited);

public:

    // Returns the degree of node i 
    int Degree(int i);


    // Adds an edge between node i and 
    // node j, and assigns a weight "w" to the edge 
    // [For unweighted graph, w will always be 1]
    void Add(int i, int j, int w);


    // Returns 1 if node i and node j are connected,
    // returns 0 otherwise
    int IsEdge(int i, int j);


    // Returns 1 if there is a path from node i to
    // node j and returns 0 otherwise
    int IsPath(int i, int j);


    // Performs depth-first search starting at node i
    // [breaks tie based on node number (smaller node goes first)]
    // Returns array holding the traverse sequence of the nodes
    int* DFT(int i);


    // Performs breadth-first search starting at node i
    // [breaks tie based on node number (smaller node goes first)
    // Returns array holding the traverse sequence of the nodes
    int* BFT(int i);

    // Performs Dijkstra's algorithm to find the shorest path 
    // from node i to node j
    //
    // Returns address of an object of the
    // Result class, which contains three
    // public variables (see definition at top):
    // (i) int length: length of the shorest path
    // (ii) int weight: total weight of the shortest path
    // (iii) int *path: array of nodes on the path
    Result* Dijkstra(int i, int j);

    // Constructor: Creates graph with n nodes and
    // initializes all entries in "m" to 0
    Graph(int n);
};

//
// Returns degree of node i by stepping through "ith" row of
// matrix and incrementing count when node i has an edge with
// another node [Cell is not equal to 0]
//
int Graph::Degree(int i) {
    int count = 0;

    for (int col = 0; col < size; col++) {
        if (m[i][col] > 0) count++;
    }

    return count;
}

//
// Checks bound of i and j, then returns the weight of the
// edge between i and j if there is one, otherwise returns 0
//
int Graph::IsEdge(int i, int j) {
    if (i >= size || j >= size) return -1;

    if (m[i][j] > 0) return m[i][j];

    return 0;
}

//
// Uses BFTHelper() method to perform Breadth-First
// Traverse from node i -> If node j is in the resulting
// array/vector, then return 1 [there is a path], otherwise
// return 0 [no path]
//
int Graph::IsPath(int i, int j) {
    vector<int> connectedNodes = BFTHelper(i);

    for (int i = 0; i < connectedNodes.size(); i++) {
        if (connectedNodes[i] == j) {
            return 1;
        }
    }
    
    return 0;
}

//
// Performs Breadth-First Traverse from Node i and returns
// a vector with the traverse sequence
//
vector<int> Graph::BFTHelper(int i) {
    
// Step 1: Initialize 3 data structures:
    // (1) A vector indicating whether a given node has already been visited or not
    // (2) A vector to hold the order in which nodes have been visited [To return]
    // (3) A queue to hold the next nodes to visit in the traverse sequence
    vector<bool> visited;
    visited.resize(size, false);

    vector<int> resultOrder;
    
    queue<int> nodeToVisit;

//Step 2: Initialize queue with first Node (i) and set visited[i] to true
    nodeToVisit.push(i);
    visited[i] = true;

//Step 3: Visit the node at the front of the queue ["nextNode"] and add it to the
//resultOrder, then push all of its unvisited neighbors into the queue and mark
//them as "visited"
    while (!nodeToVisit.empty()) {
        int nextNode = nodeToVisit.front();
        nodeToVisit.pop();
        resultOrder.push_back(nextNode);
        
        for (int i = 0; i < size; i++) {
            if (m[nextNode][i] != 0 && !visited[i]) {
                nodeToVisit.push(i);
                visited[i] = true;
            }
        }
    }

    return resultOrder;
}

//
// Use BFTHelper method to get the BFT traverse sequence as a vector, then
// convert it to a dynamically allocated array and return the array
//
int* Graph::BFT(int i) {
    vector<int> traverse = BFTHelper(i);
    
    int* resultArr = new int[traverse.size()];
    copy(traverse.begin(), traverse.end(), resultArr);

    return resultArr;
}

//
//Complete Depth-First Traverse from Node "i"
//
int* Graph::DFT(int i) {

// Step 1: Initialize result array to return traverse sequence and nextIdx to hold
// next open space in array
    int* result = new int[size];
    int nextIdx = 0;

// Step 2: Initialize a vector to mark if each node in the graph has been visited or not
    vector<bool> visited;
    visited.resize(size, false);

// Step 3: Initialize stack to perform DFT, holding each node in reverse order of how they
// have been visited
    stack<int> visitedNodes;

// Initialize stack with first node [Node i], mark it as visited, and add it to reult array
    int nextNode = 0;
    visitedNodes.push(i);
    visited[i] = true;
    result[nextIdx++] = i;
    
// Main Logic: Loop continues until the visitedNodes stack is empty, meaning that all Nodes
// have been visited
    while (!visitedNodes.empty()) {

    // Get the next node from the top of the stack of visited nodes, then pop it
        nextNode = visitedNodes.top();
        visitedNodes.pop();

    // Find nextNode's lowest index unvisited neighbor: Once found, push the current nextNode
    // back into the stack, then push the new node into the stack, mark it as visited, and add
    // it to the result array
        for (int node = 0; node < size; node++) {
            if (m[nextNode][node] != 0 && !visited[node]) {
                visitedNodes.push(nextNode);
                nextNode = node;
                visited[nextNode] = true;
                visitedNodes.push(nextNode);
                if(nextIdx < size) result[nextIdx++] = nextNode;
            }
        }
    }

    // Return result array
    return result;
}

// 
// Add edge to Graph: First check for bounds, then update matrix entries to add edge
//
void Graph::Add(int i, int j, int w) {
    if (i >= size || j >= size) return;

    m[i][j] = w;
    m[j][i] = w;
}

//
// Helper method for Dijkstra's algorithm: Finds the lowest distance for an 
// unvisited node and returns the index of that node
//
int Graph::findMin(int* distances, bool* visited) {

    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < size; v++) {
        if (!visited[v] && distances[v] <= min) {
            min = distances[v];
            min_index = v;
        }
    }

    return min_index;
}

//
// Implement Dijkstra's algorithm to find the shortest path from Node i to Node j
//
Result* Graph::Dijkstra(int i, int j) {

// Step 1: Create 3 arrays:
    // (1) "visited": track whether each Node has been visited or not
    // (2) "shortestTime": track the shortest time from node i to every node in the graph
    // (3) "prevNode": track the previous Node from which each Node's "shortestTime" was reached
    bool* visited = new bool[size];
    int* shortestTime = new int[size];
    int* prevNode = new int[size];

// Step 2: Initialize Arrays: prevNode to -1, shortestTime to Infinity, and visited to false, then set
// the shortest time for index i to 0 [Distance from node to itself is 0]
    for (int idx = 0; idx < size; idx++) {
        prevNode[idx] = -1;
        shortestTime[idx] = INT_MAX;
        visited[idx] = false;
    }

    shortestTime[i] = 0;

    int next = i;

// Step 3: Main Logic -> Run Loop until Node j, our endpoint, is selected as the next shortest possible Node
// to reach: At this point, we have found the shortest path to Node j
    while (next != j) {

    // Use findMin helper method to find next node to visit [Unvisited node with shortest distance from i] then
    // mark node as visited
        next = findMin(shortestTime, visited);
        visited[next] = true;

    // In the case where a Node is selected whose distance is still Infinity, the graph is disconnected and there
    // is no possible path from i to j -> Return NULL
        if (shortestTime[next] == INT_MAX) {
            return NULL;
        }

    // Analyze each edge connected to "next": If the node is unvisited, has an edge to "next", and can be reached from
    // "next" with a smaller weight than its previous "shortestTime", then update its shortestTime and prevNode
        for (int v = 0; v < size; v++) {
            if (!visited[v] 
                && m[next][v] != 0
                && shortestTime[next] + m[next][v] < shortestTime[v]) {

                shortestTime[v] = shortestTime[next] + m[next][v];
                prevNode[v] = next;
            }
        }
    }

// Step 4: After loop exits, arrays hold all information needed: Create result object to hold results
    Result* result = new Result;

// Use a stack to push Nodes backwards from j using the "prevNode" array until Node i is reached: allows
// for correct ordering of Result's path
    stack<int> path;
    int nextPath = j;
    while (nextPath != -1) {
        path.push(nextPath);
        nextPath = prevNode[nextPath];
    }

// Set length of shortestPath to the size of the path stack
    result->length = path.size();

// Set weight of shortestPath to the value at index j in the shortestTime array
    result->weight = shortestTime[j];

// Create dynamically allocated array for result's path, then fill it by popping the top element from the
// "path" stack
    result->path = new int[result->length];
    for (int idx = 0; idx < result->length; idx++) {
        result->path[idx] = path.top();
        path.pop();
    }

// Return the result object
    return result;
}


// 
// Constructor: Create graph of size "n" by creating 2D matrix and intializing all values to 0
//
Graph::Graph(int n) {
    size = n;
    m = new int*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = 0;
        }
    }
}


int main()
{
    
    int mode, size, i, j, w; 
    
    int a, b;

    // mode: Selects method to test
    // size: Size of Graph [number of Nodes]
    // a & b: Specific node numbers used for testing
    cin >> mode >> size >> a >> b;

    Graph x(size);


    // Create edges on graph from Node i to Node j with weight w:
    // Testing assumes inputs are within boundary
    // For unweighted graph: input 1 for all w
    while (cin >> i >> j >> w) {
        x.Add(i, j, w);
    }
    
    // Mode 0: test IsEdge()
    if (mode == 0) {
        cout << x.IsEdge(a, b);
    }
    // Mode 1: test IsPath()
    else if (mode == 1) {
        cout << x.IsPath(a,b);
    }
    // Mode 2: test Degree()
    else if (mode == 2) {
        cout << x.Degree(a);
    }
    // Mode 3: test DFT()
    else if (mode == 3) {
        int* s = new int[size];
        s = x.DFT(a);
        for (int i = 0; i < size; i++) {
            cout << s[i];
        }
    }
    // Mode 4: test BFT()
    else if (mode == 4) {
        int* s = new int[size];
        s = x.BFT(a);
        for (int i = 0; i < size; i++) {
            cout << s[i];
        }
    }
    // Mode 5: test Dijkstra()
    else if (mode == 5) {
        Result* z = x.Dijkstra(a, b);
        cout << z->length << endl;
        cout << z->weight << endl;
        for (int i = 0; i < z->length; i++) {
            cout << z->path[i];
        }
    }

    return 0;

}
