#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>

using namespace std;

// Description of code
// First i am reading the nodes and its neighbours and making a graph
// then i find the MST tree using the kruskal algorithm whose coplexity is O(ElogV)
// then i remove one edge from the MST
// then i use DFS whose order of coplexity is O(V+E)
// and mark the two graphs as different component and then i use the greedy approach that is pick the edge
// whose weight is smallest and that connects the two Minimum Spanning Tree (Which is not the edge that just deleted)

// Order of Complexity: O(ElogV + V^2)

// Data Structures:
// I implemented the class of Graph and using two structs that is node struct and one is arc struct


struct node {

	int dest;
	int weight;
	int graphNumber;
};

struct arc{
	int origin;
	int dest;
	int weight;
	int graphNumber;
};

class Graph {

private:
	int total_nodes;
	int no_of_arcs;
	int **weight_array;
	int *nodeComponent;
	vector<node> *Nodes; 
	vector<arc> allArcs;
	

public:
	Graph(int n);
	void printingGraph(Graph a);
	void adding_edge(int origin,int neighbour, int weight);
	void printFunction(string value);
	void sortingArcs();
	void removeArc(int o,int d, int w);
	void DFSUtil(int v,bool *&visited,int componenet);
	void DFS(int v,int componenet);
	void findingNew(Graph graph2,int r_o,int r_d,int w);
	bool merging(arc tempArc,vector<vector<int>>&set);
	int* findIndex(int tobeFound,vector<vector<int>>&set);
	int bringLowestArc(int o, int d,int r_o, int r_d);
	vector<arc> MST();
	vector<arc> min_spanning_tree;

};

Graph::Graph(int n)
{
	this->total_nodes = n;
	this->no_of_arcs = 0;
	nodeComponent = new int[n];
	Nodes = new vector<node>[n];
	weight_array = new int *[n];

	for (int i=0 ; i<n; i++) {
		weight_array[i] = new int[n];
		for (int j =0 ; j <n; j++) {
			weight_array[i][j] = 0;
		}
	}
}

int Graph::bringLowestArc(int o, int d,int r_o, int r_d)
{
	for(int i=0 ; i < allArcs.size();i++)
	{
		if(allArcs[i].origin != r_o || allArcs[i].dest != r_d)
		{
			if(allArcs[i].origin == o && allArcs[i].dest == d)
			{
				
				return i;
			}
		}
	}
	return -1;
}
void Graph::findingNew(Graph graph2,int r_o,int r_d,int w)
{
	vector<arc> temp;
	int index;
	cout << endl;
	for(int i=0; i < graph2.total_nodes; i++)
	{
		for(int j = i+1; j < graph2.total_nodes; j++)
		{

			if(graph2.nodeComponent[i] != graph2.nodeComponent[j])
			{
				index = (bringLowestArc(j,i,r_o,r_d));
				if(index != -1)
				{
					temp.push_back(allArcs[index]);
				}
				
			}
		}

	}

	arc min = temp[0];
	for(int i =0 ; i < temp.size(); i++)
	{
		if(temp[i].origin !=0 && temp[i].dest != 0)
		{
			if(temp[i].weight < min.weight)
			{
				min = temp[i];
			}
		}
	}

	min_spanning_tree.push_back(min);

}


void Graph::DFSUtil(int node,bool *&visited, int componenet)
{
	visited[node] = true;
	
	nodeComponent[node] = componenet;
	for (int i =0; i < Nodes[node].size();i++)
	{
		if(!visited[Nodes[node][i].dest])
		{

			DFSUtil(Nodes[node][i].dest,visited,componenet);
		}
	}
}

void Graph::DFS(int v, int componenet)
{
	bool *visited = new bool[total_nodes];
	for(int i =0; i < total_nodes; i++)
	{
		visited[i] = false;
	}

	DFSUtil(v,visited,componenet);
}

void Graph::removeArc(int o,int d, int w)
{
	for(int i = 0 ; i < min_spanning_tree.size(); i++)
	{
		if(min_spanning_tree[i].origin == o &&
			min_spanning_tree[i].dest == d &&
			min_spanning_tree[i].weight == w)
		{
			min_spanning_tree.erase(min_spanning_tree.begin() + i);
		}
	}

	// for(int i =0 ;i <min_spanning_tree.size(); i++)
	// {
	// 	if(min_spanning_tree[i])
	// }
} 
int* Graph::findIndex(int tobeFound,vector<vector<int>>&set)
{
	int *index = new int[2];
	for(int i=0; i < set.size() ; i++ )
	{
		for(int j=0;j<set[i].size();j++)
		{
			if(tobeFound == set[i][j])
			{
				index[0] = i;
				index[1] = j;
				break;
			}
		}
	}

	return index;
}

bool Graph::merging(arc tempArc,vector<vector<int>>&set)
{
	int toBeFound1 = tempArc.origin;
	int toBeFound2 = tempArc.dest;
	int* index1 = findIndex(toBeFound1,set);
	int* index2 = findIndex(toBeFound2,set);
	
	if(index1[0] == index2[0])
	{
		return false;
	}

	vector<int> temp;
	for(int i=0 ; i < set[index1[0]].size() ;i++)
	{
		temp.push_back(set[index1[0]][i]);
	}
	for(int i=0 ; i < set[index2[0]].size() ;i++)
	{
		temp.push_back(set[index2[0]][i]);
	}
	
	set.erase(set.begin()+findIndex(toBeFound1,set)[0]);
	set.erase(set.begin()+findIndex(toBeFound2,set)[0]);
	set.push_back(temp);
	
	

	return true;
	
}

vector<arc> Graph::MST()
{
	vector<arc> min_span_tree;
	vector<vector<int> > set;

	for(int i =0; i <total_nodes; i++)
	{
		vector<int> tempNode;
		tempNode.push_back(i);
		set.push_back(tempNode);
	}

	sortingArcs();

	int i =0;
	while(set.size() != 1)
	{
		if(merging(allArcs[i],set))
		{
			min_span_tree.push_back(allArcs[i]);
			min_spanning_tree.push_back(allArcs[i]);
		}
		i++;
	}
	
	return min_span_tree;
}

void Graph::sortingArcs()
{
	for(int i =0; i < allArcs.size()-1;i++)
	{
		for(int j =0; j < allArcs.size()-i-1; j++)
		{
			if(allArcs[j].weight > allArcs[j+1].weight)
			{
				arc temp = allArcs[j];
				allArcs[j] = allArcs[j+1];
				allArcs[j+1] = temp;
			}
		}
	}
}


void Graph::printFunction(string value)
{
	if(value == "graph")
	{
		cout << endl<< "------ GRAPH ------" << endl;
		for(int i=0; i <total_nodes; i++)
		{
			cout << "NODE NUMBER: " << i;
			for(int j=0; j < Nodes[i].size(); j++)
			{
				cout << " (" << Nodes[i][j].dest << ","
				<< Nodes[i][j].weight << ")" << " ";
			}
			cout << endl;
		}
	}

	else if(value == "grapharray")
	{
		cout << endl << "----- GRAPH ARRAY -----" << endl;
		for(int i =0 ; i< total_nodes; i++)
		{
			for(int j =0; j < total_nodes; j++)
			{
				cout << weight_array[i][j] << " ";
			}
			cout << endl;
		}
	}

	else if(value == "arcs")
	{
		cout << endl << "-------ARCS-----" << endl;
		for(int i =0 ; i < no_of_arcs; i++)
		{
			cout << "Origin: " << allArcs[i].origin
			<< " Dest: " << allArcs[i].dest << 
			" Weight: " << allArcs[i].weight << endl;
		}

	}

	else if(value == "MST")
	{
		for(int i =0 ; i < min_spanning_tree.size(); i++)
		{
			cout << "Origin: " << min_spanning_tree[i].origin
			<< " Dest: " << min_spanning_tree[i].dest << 
			" Weight: " << min_spanning_tree[i].weight << endl;
		}
	}
}

void Graph::adding_edge(int origin,int neighbour, int weight)
{
	weight_array[origin][neighbour] = weight;
	node tempNode;
	tempNode.dest = neighbour;
	tempNode.weight = weight;
	tempNode.graphNumber = 1;

	nodeComponent[origin] = 1;
	Nodes[origin].push_back(tempNode);

	if(weight_array[neighbour][origin] != 0)
	{
		arc tempArc;
		tempArc.origin = origin;
		tempArc.dest = neighbour;
		tempArc.weight = weight;
		tempArc.graphNumber = 1;
		allArcs.push_back(tempArc);

		no_of_arcs++;

	}

}

int extractingNumber(string a)
{
	int n;
	n = stoi(a.substr(1,a.length()-2));
	return n;
}


void extractConnectedCityAndWeight(Graph &graph, int node, string neighbours)
{
	int w,c;
	int counter=0;
	int semicolon = 0;
	int temp1 =0;
	string b;
	b =  neighbours + '\n';
	for(int i = 0; i < b.length() ; i++) {

		switch(b[i]) {

			case 'C':
				counter = i+1;
				break;

			case ';':
				semicolon = i;
				break;

			case ',':
				c= stoi(b.substr(counter,semicolon-1));
				w = stoi(b.substr(semicolon+1,i-semicolon-1));
				graph.adding_edge(node,c,w);
				break;

			case '\n':
				c= stoi(b.substr(counter,semicolon-2));
				w = stoi(b.substr(semicolon+1,i-semicolon-1));
				graph.adding_edge(node,c,w);
				break;

			default:
				temp1 = 1;
			}
		}
}


void making_the_graph(Graph &graph, string node, string neighbours)
{
	if(neighbours != "")
	{
		extractConnectedCityAndWeight(graph, extractingNumber(node), neighbours);
	}
}


Graph readingFile(string filename)
{
	ifstream fout;
	int total_nodes;
	string node;
	string neighbours;
	fout.open((filename + ".txt").c_str());
	int counter = 0;

	while(fout) {

		if (counter == 0) {
			char temp;
			fout >> temp;
			counter ++;
		}
		else if (counter == 1) {

			fout >> total_nodes;
			counter++;
			break;
		}
	}

	Graph graph(total_nodes);

	for(int i =0; i<total_nodes; i++)
	{
		fout >> node;
		getline(fout,neighbours);
		making_the_graph(graph,node,neighbours);

	}

	return graph;

}

int main()
{
	string filename;
	int r_origin,r_dest,r_w;

	cout << "Enter filename: ";
	cin >> filename;

	Graph graph = readingFile(filename);
	graph.MST();
	cout << endl <<"----------- ORIGINAL MST ----------" << endl << endl;
	graph.printFunction("MST");

	cout << endl <<"Input Arc info you want to remove" << endl;
	cout << "Enter the origin: ";
	cin >> r_origin;
	cout << "Enter the dest: ";
	cin >> r_dest;
	cout << "Enter the weight: ";
	cin >> r_w;

	cout << endl << "------------- REMOVED EDGE ------------" << endl;
	cout << "Origin: " << r_origin << " Dest: " << r_dest << " Weight: " << r_w ;
 	graph.removeArc(r_origin,r_dest,r_w);

	Graph graph2(5);
	for(int i=0; i< graph.min_spanning_tree.size(); i++)
	{
		graph2.adding_edge(graph.min_spanning_tree[i].dest,
						graph.min_spanning_tree[i].origin,
						graph.min_spanning_tree[i].weight);
		graph2.adding_edge(graph.min_spanning_tree[i].origin,
						graph.min_spanning_tree[i].dest,
						graph.min_spanning_tree[i].weight);
		
		
	}


	graph2.DFS(r_origin,1);
	graph2.DFS(r_dest,2);

	graph.findingNew(graph2,r_origin,r_dest,r_w);
	cout << endl <<"----------- NEW MST ----------" << endl << endl ;

	graph.printFunction("MST");
	

}