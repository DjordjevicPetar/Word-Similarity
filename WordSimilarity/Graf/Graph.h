#ifndef _Graph_h_
#define _Graph_h_
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Graph
{
	struct Edge {
		double value;
		string directedAt;
		Edge* nextEdge;

		Edge(double value, string directedAt, Edge* nextEdge = nullptr)
			: value(value), directedAt(directedAt), nextEdge(nextEdge) {}
	};

	struct Vertice {
		string name;
		Vertice* nextVer;
		Edge* edges;

		Vertice(string name, Vertice* next):name(name),nextVer(next), edges(nullptr) {}
	};

	Vertice* graph;
	int num_of_ver = 0;

public:

	Graph() { graph = nullptr; }

	Vertice* Find(string name) {
		for (Vertice* i = graph; i != nullptr; i = i->nextVer)if (i->name == name)return i;
		return nullptr;
	}

	int Search(string name) {
		int pos = 0;
		for (Vertice* i = graph; i != nullptr; i = i->nextVer, pos++)if (i->name == name)return pos;
		return -1;
	}
	
	Vertice* At(int pos) {
		Vertice* i;
		for (i = graph; i != nullptr && pos != 0; i = i->nextVer, pos--);
		if (i == nullptr)return nullptr;
		return i;
	}

	void AddEdge(string source, string destination, double similarity){
		if (Find(destination) != nullptr)AddEdge(Find(source), destination, similarity);
		else cout << "Destined vertice doesn't exist" << endl;
	}

	void AddEdge(Vertice* source, string destination, double similarity) {
		if (source == nullptr) {
			cout << "Source vertice doesn't exist" << endl;
			return;
		}
		Edge* temp = new Edge(similarity, destination, source->edges);
		source->edges = temp;
	}

	void RemoveEdge(string source, string destination) {
		if (Find(destination) != nullptr)RemoveEdge(Find(source), destination);
		else cout << "Destined vertice doesn't exist" << endl;
	}

	void RemoveEdge(Vertice* source, string destination) {
		if (source == nullptr) {
			cout << "Source vertice doesn't exist" << endl;
			return;
		}
		for (Edge* i = source->edges, *j = nullptr; i != nullptr; i = (j = i)->nextEdge) {
			if (i->directedAt == destination) {
				if (j == nullptr)source->edges = i->nextEdge;
				else j->nextEdge = i->nextEdge;
				delete i;
				return;
			}
		}
	}

	void AddVertice(string name) {
		graph = new Vertice(name, graph);
		num_of_ver++;
	}

	void RemoveVertice(string name) {
		if (Find(name) == nullptr) {
			cout << "This vertice already doesn't exist" << endl;
			return;
		}
		for (Vertice* i = graph, *last = nullptr; i != nullptr; i = (last) ? last->nextVer : graph)
		{
			if (i->name != name) {
				RemoveEdge(i, name);
				last = i;
			}
			else {
				for (Edge* j = i->edges, *temp; j != nullptr;)
				{
					temp = j->nextEdge;
					delete j;
					j = temp;
				}
				if (last == nullptr) {
					graph = i->nextVer;
					delete i;
					last = nullptr;
				}
				else {
					last->nextVer = i->nextVer;
					delete i;
				}
			}
		}
		num_of_ver--;
	}

	~Graph()
	{
		for (Vertice* i = graph, *j = nullptr; i != nullptr;)
		{
			j = i;
			i = i->nextVer;
			RemoveVertice(j->name);
		}
	}

	void LoadFile(string fileName) {
		delete graph;
		graph = nullptr;
		ifstream file(fileName);
		if (!file.good()) {
			cout << "This file doesn't exist" << endl;
			return;
		}
		try
		{
			int numVer, numEdges;
			string source, destination, name;
			double similarity;
			file >> numVer >> numEdges;
			while (numVer--) {
				file >> name;
				AddVertice(name);
			}
			while (numEdges--)
			{
				file >> source >> destination >> similarity;
				AddEdge(source, destination, similarity);
			}
		}
		catch (const std::exception&)
		{
			delete graph;
			graph = nullptr;
			cout << "Incorrect format of a file" << endl;
		}
	}

	void Print() {
		for (Vertice* i = graph; i != nullptr; i = i->nextVer)
		{
			cout << i->name;
			for (Edge* j = i->edges; j != nullptr; j = j->nextEdge)cout << " -> " << j->directedAt << " : " << j->value;
			cout << endl;
		}
	}

	void Dijkstra(int index, int* path, double* value) {
		Vertice* max = nullptr;
		int j, maxPos;
		bool* visited = new bool[num_of_ver];
		for (int i = 0; i < num_of_ver; i++) {
			path[i] = -1;
			value[i] = 0;
			visited[i] = false;
		}
		value[index] = 1;
		while (true)
		{
			j = 0;
			maxPos = -1;
			for (Vertice* i = graph; i != nullptr; i = i->nextVer, j++)
				if ((maxPos == -1 || value[maxPos] < value[j]) && !visited[j] && value[j]) {
					maxPos = j;
					max = i;
				}
			if (maxPos == -1)break;
			for (Edge* i = max->edges; i != nullptr; i = i->nextEdge)
			{
				j = Search(i->directedAt);
				if (value[maxPos] * i->value > value[j] && !visited[j]) {
					value[j] = value[maxPos] * i->value;
					path[j] = maxPos;
				}
			}
			visited[maxPos] = true;
		}
	}

	void MostSimilar(string name, int k) {
		int* path = new int[num_of_ver], maxPos;
		double* value = new double[num_of_ver], maxValue;
		bool* visited = new bool[num_of_ver];
		for (int i = 0; i < num_of_ver; i++)visited[i] = false;
		if (Search(name) == -1) {
			cout << "This vertix does not exist" << endl;
			return;
		}
		Dijkstra(Search(name), path, value);
		for (int i = 0; i < k + 1; i++)
		{
			maxPos = -1;
			maxValue = 0;
			for (int i = 0; i < num_of_ver; i++)
				if ((maxPos == -1 || maxValue < value[i]) && !visited[i] && value[i]) {
					maxPos = i;
					maxValue = value[i];
				}
			if (maxPos == -1)break;
			visited[maxPos] = true;
			if (maxValue == 1)continue;
			cout << At(maxPos)->name << " " << value[maxPos] << endl;
		}
		delete[] path;
		delete[] value;
		delete[] visited;
	}

	void ShortestPath(string from, string to) {
		int* path = new int[num_of_ver], first = Search(from);
		double* value = new double[num_of_ver];
		string output = "";
		if (Search(from) == -1) {
			cout << "Source vertix does not exist" << endl;
			return;
		}
		if (Search(to) == -1) {
			cout << "Destination vertix does not exist" << endl;
			return;
		}
		Dijkstra(Search(from), path, value);
		if (path[Search(to)] == -1) {
			cout << "There doesn't exist a path between those 2 vertices." << endl;
			return;
		}
		for (int i = Search(to); i != first; i = path[i])
			output = " - " + to_string(value[i] / value[path[i]]) + " -> " + At(i)->name + output;
		cout << from << output << endl;
		delete[] path;
		delete[] value;
	}

	void Connected(string from) {
		int* path = new int[num_of_ver], first = Search(from);
		double* value = new double[num_of_ver];
		if (Search(from) == -1) {
			cout << "This vertix does not exist" << endl;
			return;
		}
		Dijkstra(Search(from), path, value);
		int* pathTemp;
		double* valueTemp;
		for (int i = 0; i < num_of_ver; i++)
		{
			pathTemp = new int[num_of_ver];
			valueTemp = new double[num_of_ver];
			if (i == first)continue;
			Dijkstra(i, pathTemp, valueTemp);
			if (pathTemp[first] != -1 && path[i] != -1)cout << At(i)->name << endl;
			delete[] pathTemp;
			delete[] valueTemp;
		}
	}
};

#endif