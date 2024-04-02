#include <iostream>
using namespace std;

int main()
{
	// n is the number of vertices
	// m is the number of edges
	int n, m;
	cin >> n >> m;
	int adjMat[n + 1][n + 1];
  // Initialize matrix
  for (int i = 0; i<=n; i++) {
    for (int j = 0; j<=n; j++) {
      adjMat[i][j] = 0;
    }
  }
  
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adjMat[u][v] = 1;
		adjMat[v][u] = 1;
		// for a directed graph with an edge pointing from u
		// to v,we just assign adjMat[u][v] as 1
	}
  //Display the graph
  cout << " "; 
  for (int i = 0; i < n; i++) { 
    cout << " " << i;
  }
  cout << endl;
  for (int i = 0; i < n; i++) { 
    cout << i << " ";
    for (int j = 0; j < n; j++) { 
      cout << adjMat[i][j] << " ";
    }
    cout << endl;
  }
	return 0;
}
