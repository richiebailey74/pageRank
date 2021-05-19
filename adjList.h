#pragma once
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <iostream>
#include <cstring>

class adjList {
public:
	map<string, vector<pair<string, double>>> AL;

	adjList();
	void operator=(const adjList& al);
	void addEdge(string from, string to);
};

