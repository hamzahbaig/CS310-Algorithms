#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <list>

using namespace std;
// I HAVE DONE 2a and 2b in one code file. Press a to run 2a and b to run 2b

// QUESTION 2a:

// first of all, i read the whole file and store the leaders as nodes and their one sided grudges as 
// directed edge of that respective node.
// To find that the Leaders could be in line I used the topological sort algorithm.
// First I run DFS algorithm to check wheter there are cycles or not if there is any cycle
// then the leaders could not be arranged in a line according to given condiiton.
// So if there are cycles i return False (That they could not be arranged) 
// and if there is no cycle then i run topological algorithm and return the filled stack and output the content
// of stack

// ORDER OF COMPLEXITY TO CHECK CYCLES: O(V + E)
// ORDER OF COMPLEXITY FOR TOPOLOGICAL ALGORITHM: O(V + E)
// ORDER OF COMPLEXITY FOR STACK: O(V)
// Hence,
// TOTAL ORDER OF COMPLEXITY IS O(V + E) (Linearly)

// QUESTION 2b:

// If user enters b then it outputs whether the leaders with grudges could be seated in rows
// under given condiition.
// To solve this problem i used the old methods just modified few of them
// To solve this problem i made a 2D array aswell and fill the entires if there is a directed edge.
// First i check if there is any cyclee If yes then i return False that they could not be seated in rows.
// If there is no cycle. I run topological algorithm used in previous part.
// Order of Complexity : O(V+E)
// Then i fill a vector by popping the stack and that is done in linear time as well.
// Then i start pushing them in row and then i push the next element next to it if 
// there is no edge between the leader already present in row.
// to check wheter there is an edge or not. I use 2D array hence accessing is constant time O(1)
// And to iterate throgh all the vertices present in vector is also done in linear time: O(V)

// HENCE,  
// TOTAL ORDER OF COMPLEXITY is: 0(V + E) + O(V) + O(1)
// = O(V+E)
// SPACE COMPLEXITY is : O(V^2)

class Graph {

private:
	int total_nodes;
	vector<int>*edges ;
	char **edges_array;

public:
	Graph(int n);
	void adding_edge(int node, int edge);
	void topologicalSort(string task_code);
	void topologicalSortRecursion(int node,bool visited[],stack<int> &resulting_order);
	bool checkCycles(string task_code);
	bool checkCyclesHelper(int node, bool visited[], bool cycle[]);

};

Graph::Graph(int n) {
	this->total_nodes = n;
	edges = new vector<int>[n];
	edges_array = new char*[n];

	for(int i=0; i < n; i++) {
		edges_array[i] = new char[n];
	}
}

void Graph::adding_edge(int node, int edge) {
	edges[node].push_back(edge);
	edges_array[node][edge] = 'Y';
}

void Graph::topologicalSortRecursion(int node,bool visited[], stack<int> &resulting_order) {

	//Change the flag to visited
	visited[node] = true;

	vector<int>::iterator edge;
	for(edge = edges[node].begin() ; edge != edges[node].end(); edge++) { 
		if (!visited[*edge]) {
			topologicalSortRecursion(*edge,visited,resulting_order);
		}
	}


	resulting_order.push(node);
}

void Graph::topologicalSort(string task_code) {

	stack<int> resulting_order;
	//Mark all the vertices are not visited
	bool *visited = new bool[total_nodes];
	for (int i =0 ; i < total_nodes ; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < total_nodes ; i++) {
		if(visited[i] == false) {
			topologicalSortRecursion(i,visited,resulting_order);
		}
	}

	if (task_code =="a") {

		cout << endl <<  "-------- LEADERS IN A LINE ---------" << endl;
		cout << endl <<  "Yes" << endl;
		while(resulting_order.empty() == false) {
			cout << "L" << resulting_order.top() << ", ";
			resulting_order.pop();
		}

		cout << endl; 
	}
	
	else if (task_code == "b") {

		cout << endl << "-------- LEADERS IN ROWS ---------" << endl;	
		int counter=1;
		cout << endl<<  "Yes" << endl << endl ;
		vector<int> row_line;

		while(resulting_order.empty() == false) {
			row_line.push_back(resulting_order.top());
			resulting_order.pop();
		}

		for(int i = 0 ; i< row_line.size(); i++) {
			int edge = row_line[i];
			cout << "L" << edge;
			if(i+1 < row_line.size() && edges_array[edge][row_line[i+1]] == 'Y') {
				cout << endl;
				counter ++;
			} 
			else {

				cout << " " ;
			}
		}

		cout << endl << endl << "Total Number of rows: " << counter ;
	}
	
	
	
}

void making_the_graph(Graph &graph, char leaders,string grudges_list) {

	if(grudges_list != "") {

		int Li = (leaders-48);
		int Lj;
		string grudges;
		grudges = grudges_list.substr(2,1);
		Lj = (grudges[0]-48);

		graph.adding_edge(Li, Lj);
		while(grudges_list.substr(3,1) != "" ) {

			grudges_list = grudges_list.substr(4);
			grudges = grudges_list.substr(2,1);
			Lj = (grudges[0] - 48);

			graph.adding_edge(Li, Lj);
		}

	}


}

void reading_file(string filename,string task_code) {

	ifstream fout;
	int total_leaders;
	string leader;
	string grudges;
	fout.open(filename + ".txt");
	int counter = 0;
	while(fout) {

		Graph graph(total_leaders);
		if (counter == 0) {

			char temp ;
			fout >> temp;
			counter ++;
		}
		else if (counter == 1) {

			fout >> total_leaders;
			counter++;
			break;
		}
	}

	Graph graph(total_leaders);
	while(fout) {

		fout >> leader;
		getline(fout,grudges);
		making_the_graph(graph,leader[1],grudges);
	}

	// IF THERE ARE NO CYCLES IN GRAPH THEN GIVE THE TOPOLOGICAL ORDERING

	if(task_code == "a") {
		if(!graph.checkCycles(task_code)) {
			graph.topologicalSort(task_code);
		}
	}
	else if(task_code == "b") {
		if(!graph.checkCycles(task_code)) {
			graph.topologicalSort(task_code);
		}
		else {
			cout << "NO";
		}
	}

}

bool Graph::checkCyclesHelper(int node, bool visited[], bool cycle[]) {

	if(visited[node] == false) {

		visited[node] = true;
		cycle[node] = true;

		vector<int>::iterator edge;
		for(edge = edges[node].begin(); edge != edges[node].end(); edge++) {

			if(!visited[*edge] && checkCyclesHelper(*edge,visited,cycle)) {
				return true;
			}
			else if(cycle[*edge]) {
				return true;
			}

		}
	}
	cycle[node] = false;
	return false;
}

bool Graph::checkCycles(string task_code) {

	bool *visited = new bool[total_nodes];
	bool *cycle = new bool[total_nodes];

	for(int i =0; i <total_nodes; i++) {
		visited[i] = false;
		cycle[i] = false;
	}

	for(int i=0; i < total_nodes; i++) {

		if(checkCyclesHelper(i,visited,cycle)) {
			if(task_code == "a") {

				cout << "NO" << endl;
				cout << endl << "BECAUSE THERE IS A CYCLE" << endl << endl;
				int ancestor;

				for(int i=0 ; i < total_nodes ;i++) {
					if (i == 0 && cycle[i] == true) {
						ancestor = i;
					}
					if (cycle[i] == true) {
						cout << "L" << i << "->";
					}
				}
				cout << "L" << ancestor;
			}


			

			return true;
		}
	}

	return false;


}

int main() {

	string filename,task_code;
	cout << "Enter the part code for Task 2: ";
	cin >> task_code;
	cout << "Enter filename: " ;
	cin >> filename;

	if(task_code == "a") {
		reading_file(filename,task_code);
	}
	else if (task_code == "b") {
		reading_file(filename,task_code);
	}
	

}