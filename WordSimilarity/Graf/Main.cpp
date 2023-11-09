#include <iostream>
#include "Graph.h"

int main()
{
    Graph g;
	int choice;
	while (true) {
		cout << "What operations do you wish to be done to the graph?" << endl
			<< "0.End Program" << endl
			<< "1.Load File" << endl
			<< "2.Add Vertex" << endl
			<< "3.Add Edge" << endl
			<< "4.Remove Vertex" << endl
			<< "5.Remove Edge" << endl
			<< "6.Print" << endl
			<< "7.Most Similar" << endl
			<< "8.Shortest Path" << endl
			<< "9.Connected" << endl << endl << "Choice = ";
		cin >> choice;
		switch (choice)
		{
		case 0:exit(0);
		case 1: // LoadFile
		{
			string fileName;
			cout << endl << "What file do you wish to read?" << endl << endl << "File Name = ";
			cin >> fileName;
			g.LoadFile(fileName);
			break;
		}
		case 2: // AddVertex
		{
			string vertexName;
			cout << endl << "What name should the vertex have?" << endl << endl << "Vertex Name = ";
			cin >> vertexName;
			g.AddVertice(vertexName);
			break;
		}
		case 3: // AddEdge
		{
			string source, destination;
			double similarity;
			cout << endl << "From what vertex, to what vertex and with which similarity should the edge be?"
				<< endl << endl << "Source Vertex = ";
			cin >> source;
			cout << endl << "Destination Vertex = ";
			cin >> destination;
			cout << endl << "Similarity between then = ";
			cin >> similarity;
			g.AddEdge(source, destination, similarity);
			break;
		}
		case 4: // RemoveVertex
		{
			string vertexName;
			cout << endl << "What name does the vertex have?" << endl << endl << "Vertex Name = ";
			cin >> vertexName;
			g.RemoveVertice(vertexName);
			break;
		}
		case 5: // RemoveEdge
		{
			string source, destination;
			cout << endl << "What 2 vertex does this edge connects?"
				<< endl << endl << "Source Vertex = ";
			cin >> source;
			cout << endl << "Destination Vertex = ";
			cin >> destination;
			g.RemoveEdge(source, destination);
			break;
		}
		case 6: // Print
		{
			g.Print();
			break;
		}
		case 7: // MostSimilar
		{
			string vertexName;
			int k;
			cout << endl << "For what vertex should we find k most similar vertex?"
				<< endl << endl << "Vertex Name = ";
			cin >> vertexName;
			cout << endl << "K = ";
			cin >> k;
			g.MostSimilar(vertexName, k);
			break;
		}
		case 8: // ShortestPath
		{
			string source, destination;
			cout << endl << "Path between what 2 vertices should we find?"
				<< endl << endl << "Source Vertex = ";
			cin >> source;
			cout << endl << "Destination Vertex = ";
			cin >> destination;
			g.ShortestPath(source, destination);
			break;
		}
		case 9: // Connected
		{
			string vertexName;
			cout << endl << "For what vertex should we find strongly connected verteces?"
				<< endl << endl << "Vertex Name = ";
			cin >> vertexName;
			g.Connected(vertexName);
			break;
		}
		default:
			break;
		}
	}
}