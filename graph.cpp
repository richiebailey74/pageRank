#include "graph.h"
#include <iostream>

//creates a graph (adjacency list data structure for underlying data structure) for implementation for page ranking in the main

graph::graph(adjList& AList) {
	double graphSize = 0;

	for (auto it = AList.AL.begin(); it != AList.AL.end(); it++) {
		graphSize++;
	}

	double initialRank = (1.0 / graphSize);
	
	auto iterator = AList.AL.begin();
	vector<string> webpageNames;

	for (iterator; iterator != AList.AL.end(); iterator++) {
		webpageNames.push_back(iterator->first);
	}

	for (unsigned int i = 0; i < webpageNames.size(); i++) { //if throwing error, use verticeNum as the bound in the middle portion of the for loop
		ranks.push_back(make_pair(webpageNames[i], initialRank));
	}

	graphAL = AList;

	//add in actual outgoing values

	auto it = graphAL.AL.begin();
	for (it; it != graphAL.AL.end(); it++) {

		double linkedSize = (double)(it->second.size());
		double outdegree = (1 / linkedSize);
		
		for (int i = 0; i < linkedSize; i++) {
			it->second[i].second = outdegree;
		}
	}
}


void graph::applyPowerIt(int itNum) {
	for (int i = 1; i < itNum; i++) {
		//each iteration is essentially multiplying the graphAL data structure by the ranks data structure and putting the result in ranks

		vector<pair<string, double>> tempRanks;

		for (unsigned int k = 0; k < ranks.size(); k++) {

			double rankAtK = 0;
			for (auto it = graphAL.AL.begin(); it != graphAL.AL.end(); it++) {

				for (unsigned int j = 0; j < it->second.size(); j++) {

					if (ranks[k].first == it->second[j].first) {
						string identifier = it->first;
						bool run = true;
						int index = 0;
						while (run) {
							if (ranks[index].first == identifier) {
								run = false;
							}
							else {
								index++;
							}
						}
						rankAtK += ranks[index].second * it->second[j].second;

					}
				}
			}
			tempRanks.push_back(make_pair(ranks[k].first, rankAtK));
		}

		ranks = tempRanks;
	}

	//prints out final ranks after n power iterations (itNum power iterations)
	for (unsigned int i = 0; i < ranks.size(); i++) {
		cout << ranks[i].first << " ";
		printf("%.2f", ranks[i].second);
	}

}

