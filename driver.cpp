// Raul Martinez
// raul.martinez01@utrgv.edu

#include <iostream>
#include <string>
#include "directedGraph.h"
#include <queue>
#include <string>

using namespace std;

int main()
{
	directedGraph graph;

	//part 1:  implement "addVertex", "addDirectedEdge", and "addEdge"
	graph.addVertex("a");
	graph.addVertex("b");
	graph.addVertex("c");
	graph.addVertex("d");
	graph.addVertex("e");
	graph.addVertex("f");

	graph.addEdge("a","b");
	graph.addEdge("a","c");
	graph.addEdge("b","d");
	graph.addEdge("c","d");
	graph.addEdge("c","e");
	graph.addEdge("e","d");
	graph.addEdge("e","f");
	graph.addDirectedEdge("f", "a");

	//test that your add methods correctly build the graph:
	//should display:
	//a: b c
	//b: a d
	//c: a d e
	//d: b c e
	//e: c d f
	//f: e a
	
	graph.testDisplay();

	//Part 2: Implement breadth first search.

	//Implement a test method that:
	//1: runs breadth first search with respect to given vertex
	//2: displays each vertex and its predecessor

	//list each vertex in the graph and display which vertex is its predecessor
	//on a shortest path starting from vertex "c".
	graph.testBreadthFirstSearch("c");

	//list each vertex in the graph and display which vertex is its predecessor
	//on a shortest path starting from vertex "a".
	graph.testBreadthFirstSearch("a"); 

	//etc.
	graph.testBreadthFirstSearch("f"); 
	graph.testBreadthFirstSearch("d"); 

	//part 2: Use breadth first search to compute shortest paths
	cout << "Shortest path from a to f: " << graph.shortestPath("a","f") << endl;


	//part 3:Read in a text file describing a “maze”.  The maze consists of ‘x’ and ‘o’, 
	//characters, as well as a single ‘s’ and a single ‘d’ character.  You may assume 
	//the characters form a rectangle.  Here is an example input file: maze.txt

	//Your goal is to compute a shortest route from ‘s’ (source or start) to ‘d’ 
	//(destination).  You may move up, down, left or right one position but may only 
	//pass through ‘o’ positions.  The ‘x’ character represents unpassable walls in the 
	//maze.  Your program should write your solution to an output file showing the 
	//shortest path by replacing ‘o’ characters with ‘*’ characters whenever the ‘o’ lies 
	//on the shortest path.  Here is an example solution file for the above input file: 
	//mazeSolution.txt

	//If there is no route from ‘s’ to ‘d’, then your program should simply output the 
	//original maze with no modification.

	directedGraph graphM;

	graphM.maze("maze.txt");



	return 0;
}