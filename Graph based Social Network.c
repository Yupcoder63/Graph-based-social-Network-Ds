#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure to represent a node in the graph
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent an adjacency list
struct Graph {
    int numVertices;
    struct Node** adjLists;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (struct Node*)malloc(numVertices * sizeof(struct Node));
    
    // Initialize adjacency lists as empty
    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
    }
    
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, add edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to print the adjacency list representation of the graph
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("Adjacency list of vertex %d:\n", v);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Function to perform Breadth-First Search (BFS) and find the shortest path from source to destination
void shortestPath(struct Graph* graph, int src, int dest) {
    // Check if src and dest are valid vertices
    if (src < 0 || src >= graph->numVertices || dest < 0 || dest >= graph->numVertices) {
        printf("Invalid source or destination vertex.\n");
        return;
    }
    
    // Array to track visited vertices
    bool visited[graph->numVertices];
    // Array to store distances from src to each vertex
    int distance[graph->numVertices];
    // Array to store the parent of each vertex in the shortest path tree
    int parent[graph->numVertices];
    
    // Initialize arrays
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
        distance[i] = INT_MAX; // Infinite distance initially
        parent[i] = -1;
    }
    
    // Queue for BFS
    int queue[graph->numVertices];
    int front = 0, rear = 0;
    
    // Start BFS from src
    visited[src] = true;
    distance[src] = 0;
    queue[rear++] = src;
    
    while (front < rear) {
        int u = queue[front++];
        
        // Traverse adjacency list of vertex u
        struct Node* temp = graph->adjLists[u];
        while (temp) {
            int v = temp->data;
            if (!visited[v]) {
                visited[v] = true;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }
    
    // Print shortest path from src to dest
    printf("Shortest path from %d to %d: ", src, dest);
    if (distance[dest] == INT_MAX) {
        printf("No path exists.\n");
    } else {
        int path[graph->numVertices];
        int pathLength = 0;
        for (int v = dest; v != -1; v = parent[v]) {
            path[pathLength++] = v;
        }
        for (int i = pathLength - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}

int main() {
    int numVertices, numEdges;
    
    printf("Enter the number of users (vertices): ");
    scanf("%d", &numVertices);
    
    struct Graph* graph = createGraph(numVertices);
    
    printf("Enter the number of friendships (edges): ");
    scanf("%d", &numEdges);
    
    printf("Enter the friendships (e.g., '1 2' for friendship between user 1 and user 2):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    
    // Print the adjacency list representation of the graph
    printGraph(graph);
    
    // Find shortest path between two users
    int src, dest;
    printf("\nEnter source and destination users to find shortest path: ");
    scanf("%d %d", &src, &dest);
    shortestPath(graph, src, dest);
    
    return 0;
}