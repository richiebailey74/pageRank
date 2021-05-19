# pageRank
This repository includes a basic implementation of the pagerank algorithm of which Google built their initial search engine. Does not include anything regarding to NLP (natural language processing) but does have the capacity to rank pages based off of their relative importance (number of times referenced) to other pages. This was the initial underlying data structure of Google's initial search engine and has been built off of and developed since their founding.


At the deepest level, this implementation of the algorithm utilizies an adjacency list implementation since it is far superior for space complexity and nearly as efficient for time complexity. The space complexity gains of an adjacency list versus an adjacency matrix far outweigh the time complexity losses (hardly noticable).

The graph object is static with regards to how many references (directed edges) a certain page (node) has with other pages, meaning that once the object is created, that number cannot change and thus effect the power iterations' calculations. The power iterations will converge on a set of values as the iterations approach larger numbers to yield the definitive ranks of the pages relative to each other (the math employs linear algebra concepts).

To interact with the program, follow the prompts the command promt gives, where the initial number of lines input will yield how many edges the user can input into the graph. The power iteration function will print out all of the rankings of the pages/nodes once all the power iterations are complete for the user to see.
