#pragma once
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "adjList.h"
#include <utility>
#include <iostream>
#include <cstring>
#include <limits>

class graph {
public:
	vector<pair<string, double>> ranks;
	adjList graphAL;

	graph(adjList &AL);
	void applyPowerIt(int itNum);
};

