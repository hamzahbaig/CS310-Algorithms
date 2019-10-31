#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

// Dijstra algorithm Space complexity : O(V^2)
// Space Complexity : O(V+E)
struct node{
 	
 	int city_number;
 	int weight;

};

class Graph {

	private:
		vector<node> *edges;
		int **weight_array ;
		int total_cities;


	public:
		Graph(int n);
		void adding_edge(int n, node struct_m);
		int dijkstra(int total_cities, string soure, string dest);
};

Graph::Graph(int n) {
	this->total_cities = n;
	edges = new vector<node>[n];
	weight_array = new int *[n];

	for (int i=0 ; i<n; i++) {
		weight_array[i] = new int[n];
		for (int j =0 ; j <n; j++) {
			weight_array[i][j] = 0;
		}
	}
}

int findMinVertex(int *distance, bool *visited, int total_cities) {

	int minV = -1 ;
	for (int i=0; i< total_cities; i++) {
		if(!visited[i] && (minV == -1 || distance[i] < distance[minV])) {
			minV = i;
		}
	}
	return minV;
}

int Graph::dijkstra(int total_cities, string source, string dest) {

	vector<int> *history = new vector<int>[total_cities];
	int s = stoi(source.substr(1));
	int d = stoi(dest.substr(1));
	int *distance = new int[total_cities];
	bool *visited = new bool[total_cities];
	vector<int>* path = new vector<int>[total_cities];

	for (int i =0; i < total_cities ; i++) {
		distance[i] = 99;
		visited[i] = false;
	}

	int flag = 0;
	distance[s] = 0;
	history[s].push_back(s);
	for(int i =0; i < total_cities ; i++ ) {
		int minV = findMinVertex(distance,visited,total_cities);
		visited[minV] = true;

		for (int j=0; j < total_cities; j++) {
			if(weight_array[minV][j] != 0 && !visited[j]) {
				int dist = distance[minV] + weight_array[minV][j];
				history[i].push_back(minV) ;
				if(dist < distance[j]) {
					distance[j]  = dist;
					
				}
			}
		}
	}


	// for (int i = 0; i < total_cities; ++i)
	// {
	// 	cout << i << " " << distance[i] << endl;
	// }


	for (int i =0; i < total_cities ; i++) {
		if(i ==d) {
			return distance[i];
		}
	}


}




void Graph::adding_edge(int n, node struct_m) {
	edges[n].push_back(struct_m);
	weight_array[n][struct_m.city_number] = struct_m.weight;
}


int extractingNumber(string a) {

	int n;
	n= stoi(a.substr(1,a.length()-2));
	return n;
}


void extractConnectedCityAndWeight(Graph &graph, int city_no, string connected_citis_list ) {

	node temp;
	int w,c;
	int counter=0;
	int semicolon = 0;
	int temp1 =0;
	string b;
	b =  connected_citis_list + '\n';
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
				temp.weight = w;
				temp.city_number = c;
				graph.adding_edge(city_no,temp);
				break;

			case '\n':
				c= stoi(b.substr(counter,semicolon-2));
				w = stoi(b.substr(semicolon+1,i-semicolon-1));
				temp.weight = w;
				temp.city_number = c;
				graph.adding_edge(city_no,temp);
				break;

			default:
				temp1 = 1;

		}
	}
}


void making_the_graph(Graph &graph, string city_no, string connected_citis_list) {
	
	
	if( connected_citis_list != "") { 
			extractConnectedCityAndWeight(graph, extractingNumber(city_no), connected_citis_list);
	}
	
	
}

// void printingGraph(Graph graph) {

// 	for (int i=0 ; i< graph.total_cities; i++) {

// 		cout << "CITY NO: " << i ;
// 		for(int j =0 ; j< graph.edges[i].size() ;j++) {


// 			cout << "(" << graph.edges[i][j].city_number << "," << graph.edges[i][j].weight << ")";
// 		}
// 		cout << endl;
// 	}

// }
void reading_file(string filename) {

	ifstream fout;
	int total_cities;
	string city;
	string connected_cities;
	fout.open(filename + ".txt");
	int counter = 0;

	while(fout) {

		if (counter == 0) {
			char temp;
			fout >> temp;
			counter ++;
		}
		else if (counter == 1) {

			fout >> total_cities;
			counter++;
			break;
		}
	}

	Graph graph(total_cities);
	while(fout) {

		fout >> city ;
		getline(fout,connected_cities);
		making_the_graph(graph,city,connected_cities);
	}


	// printingGraph(graph);

	// for (int i =0 ; i < total_cities ; i++) {
	// 	for (int j =0; j < total_cities; j++) {
	// 		cout << graph.weight_array[i][j] << " " ;
	// 	}
	// 	cout << endl;
	// }

	string condition;
	cout << "Do u want to find length via some city (Press 1 for Yes): ";
	cin >> condition;
	string source,dest;
	int dist1;
	cout << endl << endl;

	if (condition != "1") {
		cout << "Enter the Source: " ;
		cin >> source;
		cout << "Enter Destination: ";
		cin >> dest;
		cout << endl << "Calculating total Length.." ;
		dist1 = graph.dijkstra(total_cities,source,dest);
		cout <<  dist1;
	}

	else if (condition == "1") 
	{
		string via;
		cout << "Enter the Source: " ;
		cin >> source;
		cout << "Enter your via-city: ";
		cin >> via;
		cout << "Enter Destination: ";
		cin >> dest;
		dist1 = graph.dijkstra(total_cities,source,via);
		dist1 = graph.dijkstra(total_cities,via,dest) + dist1;
		cout << endl << "Calculating total Length.." << endl;
		cout << endl << dist1;

	}
	
	

}


int main() {

	string filename;
	cout << "Enter filename: " ;
	cin >> filename;
	reading_file(filename);
}