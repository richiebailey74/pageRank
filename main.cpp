using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <iostream>
#include <cstring>
#include <limits>


class adjList {
public:
	map<string, vector<pair<string, double>>> AL; //graph implementation, outer data structure is a map that uses website names to map to other website names and their respective weights/out ranks

	adjList();
	void operator=(const adjList& al);
	void addEdge(string from, string to);
};


class graph {
public:
	vector<pair<string, double>> ranks; //ranks vector that tracks the current rank value for each website after a certain number of power iterations
	adjList graphAL; //the graph implementation for the graph object

	graph(adjList& AL);
	void applyPowerIt(int itNum);
};


int main() {

	int numOfLines;
	int powerIters;
	string to;
	string from;

	cin >> numOfLines;
	cin >> powerIters;

	adjList AL = adjList();

	//adds the edges into the graph implementation (adjList object)
	for (int i = 0; i < numOfLines; i++) {
		cin >> from;
		cin >> to;
		AL.addEdge(from, to);
	}

	//create graph object and pass in the adjList object with all of the added edges to it
	graph linkGraphList = graph(AL);

	//call power iterations function that passes in the number of power iterations to be done on the graph implementation
	linkGraphList.applyPowerIt(powerIters);

	return 0;
}


//empty constructor for explicit implementation 
adjList::adjList() {

}

//add edges to graph by pushing a pair value to the vector of the from key
//add empty to key that'll have empty vector if it isn't already a key
//outrank value is 0 because it is unknown what the value will be until the adjList is added to the graph object
void adjList::addEdge(string from, string to) {
	AL[from].push_back(make_pair(to, 0));
	AL[to];
}

//overload assignment operator so shallow copies aren't made any where in program
//only needs to assign the map
void adjList::operator=(const adjList& al) {
	AL = al.AL;
}


graph::graph(adjList& AList) {
	double graphSize = 0;

	//iterates through map to get the size of the map (number of unique vertices)
	for (auto it = AList.AL.begin(); it != AList.AL.end(); it++) {
		graphSize++;
	}

	//can get the initial ranks of all vertices by dividing 1 by the number of vertices
	double initialRank = (1.0 / graphSize);

	auto iterator = AList.AL.begin();
	vector<string> webpageNames;

	//get all webpage names in order in the map and add to a vector
	for (iterator; iterator != AList.AL.end(); iterator++) {
		webpageNames.push_back(iterator->first);
	}

	//push back the webpage names corresponding to the initial rank values into the r vector (rank vector)
	for (unsigned int i = 0; i < webpageNames.size(); i++) {
		ranks.push_back(make_pair(webpageNames[i], initialRank));
	}

	//copy over the adjList object from passed in to the graph object's member
	graphAL = AList;

	//iterate through map and every vector element of every key value pair and add the corresponding out rank value to each member depending on the size of the value's vector
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

		//temp ranks vector to take new values without reassigning the ranks vector until after calculations being done
		vector<pair<string, double>> tempRanks;

		//ranks through the output vector (since 4 overall values and calculations will be needed)
		for (unsigned int k = 0; k < ranks.size(); k++) {

			//get the temp sum for each output index
			double rankAtK = 0;

			//loop through map and key vectors
			for (auto it = graphAL.AL.begin(); it != graphAL.AL.end(); it++) {

				for (unsigned int j = 0; j < it->second.size(); j++) {

					//if the value of the rank vector's string at the outter index is the same as the maps value vector at the particular inner index's string-
					//-then find the index in the vector where the string from the map at the iterator's first value is equal, then multiply the rank vector at that index with-
					//-the map at the iterator's value at the vector at inner index's out rank value and add to the temp sum
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

						//adds value for each output's index
						rankAtK += ranks[index].second * it->second[j].second;
					}
				}
			}

			//puts the value of the output for an index and it's repsective string and puts in temp ranks vector
			tempRanks.push_back(make_pair(ranks[k].first, rankAtK));
		}

		//after all loops completed, equate the ranks to temp ranks before temp ranks falls out of scope and repeat for however many power iterations are needed
		ranks = tempRanks;
	}

	//prints out final ranks after n power iterations (itNum power iterations)
	for (unsigned int i = 0; i < ranks.size(); i++) {
		cout << ranks[i].first << " ";
		printf("%.2f", ranks[i].second); //prints the decimal values to two decimal places to keep outputs consistent
		cout << endl;
	}

}


