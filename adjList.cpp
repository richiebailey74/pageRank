#include "adjList.h"

//this file creates the structure for an adjacency list for the graph file to utilize with greater ease

adjList::adjList() {
	
}

void adjList::addEdge(string from, string to) {
	
	AL[from].push_back(make_pair(to, 0));
	AL[to];
	
}
void adjList::operator=(const adjList& al) {
	AL = al.AL;
}
