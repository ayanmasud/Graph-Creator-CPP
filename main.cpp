#include <iostream>
#include <cstring>

void print(int graph[20][20], char vertices[20]);

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
      cout << "Starting node: ";
      char vstart;
      cin >> vstart;
      cout << "Ending node: ";
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
      cout << "Starting node: ";
      char vstart;
      cin >> vstart;
      cout << "Ending node: ";
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
      
    }
    else if (strcmp(cmd, "QUIT") == 0) { // quit command
      break;
    }
  }

  return 0;
}

void print(int graph[20][20], char vertices[20]) {
  cout << "  ";
  for (int k = 0; k < 20; k++) {
    if (vertices[k] != ' ') {
      cout << vertices[k] << " ";
    }
  }
  cout << endl;
  for (int i = 0; i < 20; i++) {
    if (vertices[i] != ' ') {
      cout << vertices[i] << " ";
      for (int j = 0; j < 20; j++) {
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
