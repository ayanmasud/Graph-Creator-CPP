/* Graph Creator. Add vertices with labels, edges with weights, and use dijkstras algorithm to find the shortest path
   Author: Ayan Masud
   Date: 5/26/25
 */

#include <iostream>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

void print(int graph[20][20], char vertices[20]);
bool dijkstra(int graph[20][20], char vertices[20], char start, char end, int& totalDistance, char path[]);
int findMinDistance(int dist[], bool visited[], int size);

using namespace std;

int main() {

  int graph[20][20];
  char vertices[20];

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      graph[i][j] = -1;
    }
  }

  for (int k = 0; k < 20; k++) {
    vertices[k] = ' ';
  }

  // information
  cout << "'ADDV' to add a vertex" << endl;
  cout << "'ADDE' to add an edge" << endl;
  cout << "'DELV' to delete a vertex" << endl;
  cout << "'DELE' to delete an edge" << endl;
  cout << "'PRINT' to print the graph" << endl;
  cout << "'FSP' to find shortest path" << endl;
  cout << "'QUIT' to leave" << endl;

  while (true) {
    char cmd[8];
    cin.getline(cmd, 8);

    if (strcmp(cmd, "ADDV") == 0) { // add vertex command
      char vlabel;
      cout << "Enter a label for a vertex: ";
      cin >> vlabel;
      int index = 0;
      while (vertices[index] != ' ') {
	      index++;
      }
      vertices[index] = vlabel;
    }
    else if (strcmp(cmd, "ADDE") == 0) { // add edge command
      cout << "Starting vertex: ";
      char vstart;
      cin >> vstart;
      cout << "Ending vertex: ";
      char vend;
      cin >> vend;
      cout << "Enter the weight: ";
      int weight;
      cin >> weight;

      int sindex = 0;
      while (vertices[sindex] != vstart) {
	      sindex++;
      }

      int eindex = 0;
      while (vertices[eindex] != vend) {
        eindex++;
      }

      graph[sindex][eindex] = weight;
    }
    else if (strcmp(cmd, "DELV") == 0) { // delete vertex command
      char vlabel;
      cout << "What vertex label? ";
      cin >> vlabel;
      int index = 0;
      while (vertices[index] != vlabel) {
        index++;
      }

      for (int i = 0; i < 20; i++) { // clear any edge connected to this vertex
        if (vertices[i] != ' ') {
          for (int j = 0; j < 20; j++) {
            if (graph[i][j] != -1) {
              if (i == index || j == index) {
                graph[i][j] = -1;
              }
            }
          }
        }
      }
      vertices[index] = ' '; // remove the vertex
    }
    else if (strcmp(cmd, "DELE") == 0) { // delete edge command
      cout << "Starting vertex: ";
      char vstart;
      cin >> vstart;
      cout << "Ending vertex: ";
      char vend;
      cin >> vend;

      int sindex = 0;
      while (vertices[sindex] != vstart) {
        sindex++;
      }

      int eindex = 0;
      while (vertices[eindex] != vend) {
        eindex++;
      }

      graph[sindex][eindex] = -1; // remove that edge
    }
    else if (strcmp(cmd, "PRINT") == 0) { // print command
      print(graph, vertices);
    }
    else if (strcmp(cmd, "FSP") == 0) { // find shortest path command
      char vstart;
      char vend;
      cout << "Starting vertex: ";
      cin >> vstart;
      cout << "Ending vertex: ";
      cin >> vend;
      
      char path[20];  // array to store the path
      int totalDistance = 0;

      bool pathExists = dijkstra(graph, vertices, vstart, vend, totalDistance, path);
      
      if (pathExists) {
	      cout << "Shortest distance: " << totalDistance << endl;
      } 
      else {
	      cout << "There's no path between " << vstart << " and " << vend << endl;
      }
    }
    else if (strcmp(cmd, "QUIT") == 0) { // quit command
      break;
    }
  }

  return 0;
}

void print(int graph[20][20], char vertices[20]) {
  cout << "  ";
  for (int k = 0; k < 20; k++) { // prints top part
    if (vertices[k] != ' ') {
      cout << vertices[k] << " ";
    }
  }
  cout << endl;
  for (int i = 0; i < 20; i++) {
    if (vertices[i] != ' ') {
      cout << vertices[i] << " "; // prints left part
      for (int j = 0; j < 20; j++) { // prints values
        if (graph[i][j] == -1) {
          cout << "  ";
        }
        else {
          cout << graph[i][j] << " ";
        }
      }
      cout << endl;
    }
  }
}

bool dijkstra(int graph[20][20], char vertices[20], char start, char end, int& totalDistance, char path[]) {
  // find number of vertices
  int numVertices = 0;
  for (int i = 0; i < 20; i++) {
    if (vertices[i] != ' ') {
      numVertices++;
    }
  }
  
  // find start and end index
  int startIndex = -1;
  int endIndex = -1;
  
  for (int i = 0; i < 20; i++) {
    if (vertices[i] == start) {
      startIndex = i;
    }
  }
  
  for (int i = 0; i < 20; i++) {
    if (vertices[i] == end) {
      endIndex = i;
    }
  }
  
  if (startIndex == -1 || endIndex == -1) { // they werent found
    return false;
  }
  
  // distance, visted, previous arrays
  int dist[20];
  bool visited[20];
  int prev[20];
  
  // initialize arrays
  for (int i = 0; i < 20; i++) {
    dist[i] = INT_MAX; // infinite
    visited[i] = false; // none visited yet
    prev[i] = -1; // empty
  }
  dist[startIndex] = 0; // starting distance is 0
  
  // dijkstras algorithm loop
  for (int count = 0; count < numVertices; count++) {
    int vsmallDist = findMinDistance(dist, visited, 20);
    if (vsmallDist == -1) { 
      break;
    }
    
    visited[vsmallDist] = true;
    
    // update distances for adjacent vertices
    for (int j = 0; j < 20; j++) {
      if (!visited[j] && vertices[j] != ' ' && graph[vsmallDist][j] != -1 && dist[vsmallDist] != INT_MAX && dist[vsmallDist] + graph[vsmallDist][j] < dist[j]) {
	dist[j] = dist[vsmallDist] + graph[vsmallDist][j];
	prev[j] = vsmallDist;
      }
    }
  }
  
  // check if path exists
  if (dist[endIndex] == INT_MAX) {
    return false;
  }
  
  totalDistance = dist[endIndex];
  return true;
}

int findMinDistance(int dist[], bool visited[], int size) {
  int minDist = INT_MAX;
  int minIndex = -1;
  
  for (int i = 0; i < size; i++) {
    if (!visited[i] && dist[i] <= minDist) { // vertex is unvisited and has a smaller distance than current minimum
      minDist = dist[i];
      minIndex = i;
    }
  }
  
  return minIndex;
}
