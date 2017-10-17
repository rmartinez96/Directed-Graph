//Raul Martinez
//raul.martinez01@utrgv.edu

#include <iostream>
#include <string>
#include <list> //the stl's doubly linked list
#include <stack>
#include <queue>
#include <fstream>

using namespace std;

class directedGraph
{
private:
	class vertex
	{
	public:
		string data;
		list<vertex*> adjList;
		bool visited;
		vertex * pred;
		// for maze only
		int row;
		int column;

		vertex(string x)
		{
			data=x;
			visited = false;
			//sanity check
			row = 0;
			column = 0;
		}

		// for maze only
		vertex(string x, int i, int j)
		{
			data=x;
			visited = false;
			row = i;
			column = j;
		}
	};

	list<vertex*> vertexList; //should really use.. hash table, or AVL-tree

public:

	~directedGraph()
	{
		//free all the (dynamically allocated) vertices.
		for(list<vertex*>::iterator itr = vertexList.begin(); itr!= vertexList.end(); itr++)
		{
			vertex * v = (*itr);
			delete v;
		}
	}	

	//add a new vertex with data value x to the graph
	void addVertex(string x)
	{
		vertex * v = new vertex(x);
		vertexList.push_back(v);
	}

	//add a directed edge going from x to y
	void addDirectedEdge(string x, string y)
	{
		//first, find the vertices holding x and y
		vertex* a = findVertex(x);
		vertex* b = findVertex(y);
		//Second, add an edge going from x's vertex to y's vertex
		a->adjList.push_back(b);
	}

	vertex* findVertex(string x)
	{
		for(list<vertex*>::iterator itr = vertexList.begin(); itr!= vertexList.end(); itr++)
		{
			vertex * v = (*itr);
			if (v->data == x)
				return v;
		}
		return NULL;
	}

	//add a basic edge (going both directions) connect x and y
	void addEdge(string x, string y)
	{
		addDirectedEdge(x,y);
		addDirectedEdge(y,x);
	}

	void BFS(string x)
	{
		vertex * a = findVertex(x);
		queue<vertex *> q;
		vertex * u;
		vertex * tPred;

		q.push(a);
		a->visited = true;

		while (!q.empty())
		{
			a = q.front();
			tPred = a;
			q.pop();

			for (list<vertex*>::iterator itr = a->adjList.begin(); itr != a->adjList.end(); itr++)
			{
				u = (*itr);
				if (u->visited == false)
				{
					u->visited = true;
					q.push(u);
					u->pred = tPred;
				}
			}
		}

		for (list<vertex*>::iterator itr = vertexList.begin(); itr != vertexList.end(); itr++)
		{
			vertex * u = (*itr);
			u->visited = false;
		}		
	}

	void testBreadthFirstSearch(string x)
	{
		//BFS(x);
		vertex * a = findVertex(x);
		queue<vertex *> q;
		vertex * u;
		vertex * tPred;

		q.push(a);
		a->visited = true;

		cout << a->data << "- ";

		while (!q.empty())
		{
			a = q.front();
			tPred = a;
			q.pop();

			for (list<vertex*>::iterator itr = a->adjList.begin(); itr != a->adjList.end(); itr++)
			{
				u = (*itr);
				if (u->visited == false)
				{
					u->visited = true;
					q.push(u);
					u->pred = tPred;
					cout << u->data << " " << u->pred->data << ", ";
				}
			}
		}
		cout << endl;

		for (list<vertex*>::iterator itr = vertexList.begin(); itr != vertexList.end(); itr++)
		{
			vertex * u = (*itr);
			u->visited = false;
		}

	}

	string shortestPath(string x, string y)
	{
		BFS(x);

		return dispB(x, y);
	}

	string dispB(string a, string b){
		string z = "";
		int c = 0;

		stack<vertex *> s;
		vertex * x = findVertex(a);
		vertex * y = findVertex(b);

		while (x->data != y->data)
		{
			s.push(y);
			y = y->pred;
		}

		s.push(x);

		while(!s.empty())
		{
			x = s.top();
			s.pop();
			c++;
			z = z + x->data + " ";
		}

		return z;
	}

	//after implementing your "addVertex", "addDirectedEdge", and "addEdge" methods,
	//test that each added vertex is present, and it has the correct neighbors:
	void testDisplay()
	{
		for(list<vertex*>::iterator itr = vertexList.begin(); itr!= vertexList.end(); itr++)
		{
			vertex * v = (*itr);
			cout << v->data << ": ";
			for(list<vertex*>::iterator jtr=v->adjList.begin(); jtr!=v->adjList.end(); jtr++)
			{
				vertex * u = (*jtr);
				cout << u->data << " ";
			}
			cout << endl;
		}
	}

	// these are only for the maze //////////////////////////////////////////////////////////////

	void addVertex(string x, int i, int j)
	{
		vertex * v = new vertex(x,i,j);
		vertexList.push_back(v);
	}

	void addDirectedEdge(int r1,int b1,int r2,int b2)
	{
		vertex* a = findVertex(r1,b1);
		vertex* b = findVertex(r2,b2);

		a->adjList.push_back(b);
	}

	void addEdge(int r1, int b1, int r2, int b2)
	{
		addDirectedEdge(r1,b1,r2,b2);
		addDirectedEdge(r2,b2,r1,b1);
	}

	vertex* findVertex(int r, int c)
	{
		for(list<vertex*>::iterator itr = vertexList.begin(); itr!= vertexList.end(); itr++)
		{
			vertex * v = (*itr);
			if (v->row == r && v->column == c)
				return v;
		}
		return NULL;
	}

	void BFS()
	{
		vertex * start = findVertex("s");

		queue<vertex *> q;
		vertex * u;
		vertex * tPred;

		q.push(start);
		start->visited = true;

		//cout << start->data << " -(" << start->column << "," << start->row << "): ";

		while (!q.empty())
		{
			start = q.front();
			tPred = start;
			q.pop();

			for (list<vertex*>::iterator itr = start->adjList.begin(); itr != start->adjList.end(); itr++)
			{
				u = (*itr);

				if (u->visited == false)
				{
					u->visited = true;
					q.push(u);
					u->pred = tPred;
					//cout << "(" << u->column << "," << u->row << "), ";
				}
			}
		}
		cout << endl << endl;
		for (list<vertex*>::iterator itr = vertexList.begin(); itr != vertexList.end(); itr++)
		{
			vertex * u = (*itr);
			u->visited = false;
		}		
	}

	void shortestPath(string s)
	{
		BFS();

		cout << dispB();
	}

	string dispB(){
		string z = "";
		int c = 0;

		stack<vertex *> s;
		vertex * x = findVertex("s");
		vertex * y = findVertex("d");

		while (x->pred != y->pred)
		{
			if (y->data != "d")
			{
				y->data	= "*";
			}
			s.push(y);
			y = y->pred;
		}

		s.push(x);

		while(!s.empty())
		{
			x = s.top();
			s.pop();
			c++;
			//z = z + x->data + ": (" + to_string(x->column) + "," + to_string(x->row) + "), ";
		}

		return z;
	}

	void maze(string x)
	{
		ifstream inFile;
		ofstream outFile("solution.txt");
		inFile.open(x);

		int n = 0, i = 0, j = 0, size = 0;
		string * s = new string[100];

		vertex * start;
		vertex * end;

		while (!inFile.eof())
		{
			getline(inFile,s[i]);
			size = s[i].length();

			//add each vertex with the chars in the string
			for (j = 0; j < size - 1; j++)
			{
				string h(1,s[i][j]);
				if (h != "x")
				{
					addVertex(h,i,j);
				}
				//cout << s[i] << endl;
			}

			//connect the coloumn vertices to their neighbors
			for (j = 0; j < size; j++)
			{
				if (j + 1 != size && ((s[i][j] == 'o' && s[i][j+1] == 'o') || (s[i][j] == 's' && s[i][j+1] == 'o') 
					|| (s[i][j] == 'o' && s[i][j+1] == 's') || (s[i][j] == 'o' && s[i][j+1] == 'd') 
					|| (s[i][j] == 'd' && s[i][j+1] == 'o')))
				{
					addEdge(i,j,i,j+1);
				}
			}

			i++;
		}

		inFile.close();

		//connect the row vertcies to their neighbors
		for (j = 0; j < size; j++)
		{
			for (n = 0; n < i; n++)
			{
				if (n + 1 != i && ((s[n][j] == 'o' && s[n+1][j] == 'o') || (s[n][j] == 's' && s[n+1][j] == 'o') 
					|| (s[n][j] == 'o' && s[n+1][j] == 's') || (s[n][j] == 'o' && s[n+1][j] == 'd') 
					|| (s[n][j] == 'd' && s[n+1][j] == 'o')))
				{
					addEdge(n,j,n+1,j);
				}
			}
		}

		//testDisplayG();

		shortestPath("s");

		//cout << endl;

		vertex * change;

		outFile << "Maze: Solution" << endl;

		for (j = 0; j < i; j++)
		{
			for (n = 0; n < size - 1; n++)
			{
				change = findVertex(j,n);
				if (change != NULL && change->data != "d")
				{
					s[j][n] = change->data[0];
				}
			}
			outFile << s[j] << endl;
		}

		outFile.close();

		delete [] s;
	}

	void testDisplayG()
	{
		for(list<vertex*>::iterator itr = vertexList.begin(); itr!= vertexList.end(); itr++)
		{
			vertex * v = (*itr);
			cout << v->data << " -(" << v->column << "," << v->row << "): ";
			for(list<vertex*>::iterator jtr=v->adjList.begin(); jtr!=v->adjList.end(); jtr++)
			{
				vertex * u = (*jtr);
				cout << "(" << u->column << "," << u->row << "), ";
			}
			cout << endl;
		}
	}
};