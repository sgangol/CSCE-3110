/*********************************************************************
     NAME:        Srizan Gangol         USERID:sg0440               **
     ASSIGNMENT:  CSCE3110                                          **
     DESCRIPTION: Program 4                                         **
                  Program reads the input file provide by the user
				  through the argument and reads the vertices and 
				  edges using which this program derives BFS, DFS
				  & Topological Sorting along with further analyzing 
				  for Cyclic & Connected
 ********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <utility>

#define underline "\33[4m" // GUI to underline

using namespace std;

static int currentIteration = 1;

// Declaring the Class Graph
class Graph {
	// Private Class
	map<int, vector<int> > adjList;

	void clearMap(map<int, bool> &inputMap);
	void BFSUtil(int v, ofstream &outputFile, map<int, bool> &visited, bool writeToFile);	// BFS Utilization- Does all the work
	void callDFS(int v, map<int, bool> &visited, ofstream &outputFile);						// Calls DFS
	void topologicalSortUtil(int v, map<int, bool> &visited, stack<int> &Stack);			// Topological Sort Utilization
	bool isCyclicUtil(int v, map<int, bool> &recursionStack, map<int, bool> &visited);		// Checks for Cyclic

	public : 
		void insertVertex(int v);															// Inserts Vertex
		void addEdge(int source, int destination);											// Add Edge
		void DFSUtil(int v, map<int, bool> &visited, map<int, pair<int, int> > &info);		// DFS Utilization 
		void DFS();																			// Function Call for DFS
		void BFS();																			// Function Call for BFS
		void topologicalSort();																// Function Call for Topological Sorting
		bool isCyclic();																	// Returns True or False for Cyclic
		bool isConnected();																	// Returns True or False for Connected
		Graph reverseGraph();
};

void Graph::clearMap(map<int, bool> &inputMap) {
	for(map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
		inputMap[it->first] = false;
	}
}

// Inserts vertex to the adjacency list
void Graph::insertVertex(int v) {
	adjList[v] = vector<int>();
}

// Inserts Edges to the adjacency List
void Graph::addEdge(int source, int destination) {
	adjList[source].push_back(destination);
}

// Function to carry out main function for the BFS
void Graph::BFSUtil(int v, ofstream &outputFile, map<int, bool> &visited, bool writeToFile) {
	list<pair<int, int> > queue;
	pair<int, int> vertex, temp;
	int weight = 0;
	vertex = make_pair(v, weight);
	visited[v] = true;
	queue.push_back(vertex);
	while(!queue.empty()) {
		vertex = queue.front();
		if(writeToFile) {
			cout << vertex.first << "\t" << vertex.second << "\n";
			outputFile << vertex.first << " " << vertex.second << "\n";
		}
		queue.pop_front();
		weight = vertex.second + 1;	// Calculates the Weight
		for(vector<int>::iterator it = adjList[vertex.first].begin(); it != adjList[vertex.first].end(); ++it) {
			if(!visited[*it]) {
				visited[*it] = true;
				temp = make_pair(*it, weight);
				queue.push_back(temp);
			}
		}
	} 
	if(writeToFile) {
		for(map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
			if(!visited[it->first]) {
				cout << it->first << "\tinf\n";
				outputFile << it->first << " inf\n";
			}
		}
	}
}

// Prints out the BFS, Main call for the BFS output
void Graph::BFS() {
	ofstream outputFile ("BFS.out");
	map<int, bool> visited;
	clearMap(visited);
	cout << "\n\33[4m>BFS\33[0m :\n";
	cout << "\n\33[4mNodes\33[0m\t\33[4mDistance\33[0m \n";
	BFSUtil(1, outputFile, visited, true);
	cout << "\n Result exported to BFS.out\n";
}

// Function to carry out DFS, main function for DFS
void Graph::DFSUtil(int v, map<int, bool> &visited, map<int, pair<int, int> > &info) {
	visited[v] = true;
    info[v].first = currentIteration;
    for(vector<int>::iterator it=adjList[v].begin(); it != adjList[v].end(); ++it) {
    	if(!visited[*it]) {
    		currentIteration++;
    		DFSUtil(*it, visited, info);
    	}
    }
    currentIteration++;
    info[v].second = currentIteration;
}

// Prints out the DFS, Main call for the DFS output
void Graph::callDFS(int v, map<int, bool> &visited, ofstream &outputFile) {
	map<int, pair<int, int> > info;
	currentIteration++;
	DFSUtil(v, visited, info);
	cout << v << "\t" << info[v].first << "\t" << info[v].second << "\n";
	outputFile << v << " " << info[v].first << " " << info[v].second << "\n";
	for(vector<int>::iterator it = adjList[v].begin(); it != adjList[v].end(); ++it) {
		if(info[*it].first > 0) {
			cout << *it << "\t" << info[*it].first << "\t" << info[*it].second << "\n";
			outputFile << *it << " " << info[*it].first << " " << info[*it].second << "\n";
		}
	}
}
// Prints out the DFS, Main call for the DFS output
void Graph::DFS() {
	ofstream outputFile ("DFS.out");
	map<int, bool> visited;
	map<int, pair<int, int> > info;
	clearMap(visited);
	cout << "\n\33[4m>DFS\33[0m  :\n";
	cout << "\n\33[4mNodes\33[0m\t\33[4mStart\33[0m\t\33[4mFinished\33[0m \n"; 					// Looks funky because of the underlining
	DFSUtil(1, visited, info);
	for(map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
		if(info[it->first].first > 0) {
			cout << it->first << "\t" << info[it->first].first << "\t" << info[it->first].second << "\n";
			outputFile << it->first << " " << info[it->first].first << " " << info[it->first].second << "\n";
		}
	}
	for(map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
		if(!visited[it->first]){
			callDFS(it->first, visited, outputFile);
		}
	}
	outputFile.close();
	cout << "\n Result exported to DFS.out\n";
}

// Function to perform Topological Sort
void Graph::topologicalSortUtil(int v, map<int, bool> &visited, stack<int> &Stack) {
	visited[v] = true;
	for(vector<int>::iterator it = adjList[v].begin(); it != adjList[v].end(); ++it) {
		if(!visited[*it]) {
			topologicalSortUtil(*it, visited, Stack);
		}
	}
	Stack.push(v);
}

// Prints out the Topological Sort, Main call for the Topological Sort output
void Graph::topologicalSort() {
	ofstream outputFile ("ts.out");
	stack<int> Stack;
	map<int, bool> visited;
	clearMap(visited);
	for (map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
		if(!visited[it->first]) {
			topologicalSortUtil(it->first, visited, Stack);
		}
	}
	cout << "\n\33[4m>Topological Sort\33[0m :\n";
	cout << "\n\33[4mNodes\33[0m \n";
	while(!Stack.empty()) {
		cout << Stack.top() << "\n";
		outputFile << Stack.top() << "\n";
		Stack.pop();
	}
	cout << "\n Result exported to ts.out\n";
}

// Checks if the Graph is Cyclic
bool Graph::isCyclicUtil(int v, map<int, bool> &recursionStack, map<int, bool> &visited) {
	if(!visited[v]) {
		visited[v] = true;
		recursionStack[v] = true;
		for(vector<int>::iterator it = adjList[v].begin(); it != adjList[v].end(); ++it) {
			if(!visited[*it] && isCyclicUtil(*it, recursionStack, visited)) {
				return true;
			} else if(recursionStack[*it]) {
				return true;
			}
		}
	}
	recursionStack[v] = false;
	return false;
}
// Returns True if the Graph is Cyclic
bool Graph::isCyclic() {
	map<int, bool> recursionStack, visited;
	clearMap(recursionStack);
	clearMap(visited);
	for(map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
		if(isCyclicUtil(it->first, recursionStack, visited)) {
			return true;
		}
	}
	return false;
}

// Reverse Graph
Graph Graph::reverseGraph() {
	Graph newGraph;
	for(map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
		int destination = it->first;
		vector<int> adjVertices = it->second;
		newGraph.insertVertex(destination);
		for(vector<int>::iterator i = adjVertices.begin(); i != adjVertices.end(); ++i) {
			newGraph.addEdge(*i, destination);
		}
	}
	return newGraph;
}
// Returns True if the Graph is connected
bool Graph::isConnected() {
	ofstream outputStream;
	map<int, bool> visited;
	clearMap(visited);
	map<int, pair<int, int> > info;
	BFSUtil(1, outputStream, visited, false);
	for(map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
		if(!visited[it->first]) {
			return false;
		}
	}
	Graph newGraph = reverseGraph();
	clearMap(visited);
	newGraph.BFSUtil(1, outputStream, visited, false);
	for(map<int, vector<int> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {
		if(!visited[it->first]) {
			return false;
		}
	}
	return true;
}

// Get Source Vertex - Used while reading the file
int getSourceVertex(string line) {
	int v;
	bool foundSourceVertex = false;
	istringstream iss (line);
	while(iss >> v) {
		if(!foundSourceVertex) {
			return v;
		}
		foundSourceVertex = true;
	}
	return v;
}

// Main Function
int main(int argc, char * argv[]) {
	// Checks for the USUAGE, if in correct shows the usuage
	if(argc != 3) {
		cout << "\n Invalid Command!!! \n";
		cout << " Usage : " << argv[0] << " [algorithm] " << " [filename]\n";
	} else { 
		ifstream graphInput (argv[2]);											// Inputs from the file
		if(!graphInput.is_open()) {												// If Input fails
			cout << " Sorry! Unable to open the file\n";						// ERROR message
		} else {
			string algorithm = argv[1];											// Which Algorithm to accept
			if(algorithm.compare("bfs") != 0 && algorithm.compare("dfs") != 0 && algorithm.compare("ts") != 0) {
				cout << "\n Invalid algorithm entered. Please choose between : \tbfs\tdfs\tts \n";
				cout << "\n Please Try Again \n\n\n\n";
				return 0;
			}
			cout << "\n>Reading input from the file: \n\n";
			Graph g;
			string line;
			int v, currentVertex = 1;
			// Read from the file line by line
			while(getline(graphInput, line)) {
				cout << line << "\n";
				istringstream iss (line);
				int sourceVertex = getSourceVertex(line);
				if(sourceVertex == currentVertex) {
					g.insertVertex(currentVertex);
					while(iss >> v) {
						if(v != currentVertex) {
							g.addEdge(currentVertex, v);
						}
					}
					currentVertex++;
				}
			}
			// Call BFS 
			if(algorithm.compare("bfs") == 0) {
				g.BFS();
			// Call DFS
			} else if(algorithm.compare("dfs") == 0) {
				g.DFS();
			// Call Topological Sort
			} else if(algorithm.compare("ts") == 0) {
				g.topologicalSort();
			}
			// Checks if it's connected or not
			if(g.isConnected()) {
				cout << "\n>Is the graph connected? \t::YES::\n";
			} else {
				cout << "\n>Is the graph connected? \t::NO:: \n";
			}
			// Checks if it's Cyclic
			if(g.isCyclic()) {
				cout << "\n>Is the graph Cyclic? \t\t::YES::\n";
			} else {
				cout << "\n>Is the graph Cyclic? \t\t::NO:: \n";
			}
		}
	}
	cout << "\nThank you for using the program !\n";
	return 0;
}