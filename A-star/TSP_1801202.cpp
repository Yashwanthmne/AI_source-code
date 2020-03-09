#include <bits/stdc++.h>
using namespace std;


// admissible heuristic function.

int heuristic(int xq, int **graph, int g[], vector<int> not_v,int node){
	
	std::vector<int> not_visited;
	for(int i = 0; i < not_v.size(); ++i){
		not_visited.push_back(not_v[i]);
	}
	int x = not_visited.size(), n = node;
	int h1 = 0, h2 = 0, min = INT_MAX;
	
	//**********************************************************
	// for the heuristic h1, closest unvisited city from present node
	
	
	for(int i = 0; i < not_visited.size(); ++i){
		if(graph[node][not_visited[i]] < min){
			min = graph[node][not_visited[i]];
		}
	}
	if(min < INT_MAX) h1 = min;
	min = INT_MAX;
	
	
	// *********************************************************
	// for the heuristic h2, closest unvisited city from root node
	
	
	for(int i = 0; i < not_visited.size(); ++i){
		if(graph[0][not_visited[i]] < min){
			min = graph[0][not_visited[i]];
		}
	}
	if(min < INT_MAX) h2 = min;
	
	
	//**********************************************************
	// for the heuristic h3 using mst
	
	
	std::vector<int> vis;
	int cost = 0, idx = 0, m;
	vis.push_back(node);
	not_visited.erase(std::remove(not_visited.begin(), not_visited.end(), node), not_visited.end());
	while(vis.size() != x){
	

		m = INT_MAX;
		for(int i = 0; i < not_visited.size(); ++i){
			if(node != not_visited[i]){
				if(graph[node][not_visited[i]] < m){
					idx = not_visited[i];
					m = graph[node][not_visited[i]];
				}
			}
		}
		// cout << "pushing " << idx << " to vis\n";
		vis.push_back(idx);
		not_visited.erase(std::remove(not_visited.begin(), not_visited.end(), idx), not_visited.end());
		node = idx;
		// cout << "adding " << m << " to cost .. \n";
		cost += m;
	}
	
	m = INT_MAX;
	for(int i = 0; i < not_v.size(); ++i){
		if(not_v[i] != n){
			if(graph[n][i] < m){
				m = graph[n][i];
			}
		}
	}

//	cout << "node : " << n << "  m : " << m  << " w : " << w << endl;
	return cost + h1 + h2;
}

void a_star_algo(int n, int** graph, int g[], int h[], int node){
	
	vector<int> visited;
	vector<int> not_visited;
	vector<int> open;
	vector<int> closed;
	
	// node graph_data[n];
	int f[n] = {0};

	for(int i = 0; i < n; ++i){
		not_visited.push_back(i);
	}

	open.push_back(node);

	// int c = 0;
	int min = INT_MAX, idx = 0;
	h[0] = heuristic(n, graph, g, not_visited, 0);
	f[0] = g[0] + h[0];

	while(1){
		
		//max value to min, as we have to find the minimum value
		min = INT_MAX;
		
		//loop through to find the city with minimum f value
		for(int i = 0; i < open.size(); ++i){
			
			if(f[open[i]] < min){
				min = f[open[i]];
				idx = open[i];
			}
			
		}

		// current city is stored in node
		node = idx;

		// deleting the city from open list
		open.erase(std::remove(open.begin(), open.end(), node), open.end());

		if(visited.size() == n) break;
		int ct = 0, test_f = 0;
		
		for(int i = 0; i < n; ++i){
			/*
			for(int k = 0; k < closed.size(); ++k){
				if(closed[k] == i){
					ct = 1;
					break;
				}
			}
			*/
			if(i != node){
				
				test_f = g[node] + graph[node][i] + heuristic(n, graph, g, not_visited, i);
				
				if(find(open.begin(), open.end(), i) != open.end()) //if present in open list
				{
				    for(int qw = 0; qw < open.size(); ++qw){
				    	if(open[qw] == i){
				    		if(f[open[qw]] < test_f){
				    			open.erase(std::remove(open.begin(), open.end(), i), open.end()); //delete that value from node
								open.push_back(i);
							}
						}
					}
				} 
				

				//if present in closed list
				else if(find(closed.begin(), closed.end(), i) != closed.end());

				else {
					open.push_back(i);
				}
				
				g[i] = g[node] + graph[node][i];
				f[i] = g[i] + heuristic(n, graph, g, not_visited, i);
			}
			ct = 0;
		}
		// cout << "open .... " << endl;
		// for(int j = 0; j < open.size(); ++j) cout << "open[" << j << "] : " << open[j] << endl;
		// cout << "end .. " << endl;

		// cout << "INSERTING " << node << "INTO CLOSED\n";
	
		closed.push_back(node);
	
		visited.push_back(node);
	
		not_visited.erase(std::remove(not_visited.begin(), not_visited.end(), node), not_visited.end());
		// not_visited.delete(node);
	}
	for(int i = 0; i < visited.size(); ++i){
		cout << visited[i] + 1 << "  ";
	}
}

int main(){
	int n;
	cout << "insert number of cities ... \n";
	cin >> n;
//	n = 4
	int **graph;
	graph = new int *[n];
	for(int i = 0; i <n; i++)
    graph[i] = new int[n];
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cout << "enter graph's' " << i << " " << j << endl;
			cin >> graph[i][j];
		}
	}
	int g[n], h[n];
	for(int i = 0; i < n; ++i){
		g[i] = 0;
		h[i] = 0;
	}
	
	/*
	graph[0][0] = 0;
	graph[0][1] = 10;
	graph[0][2] = 15;
	graph[0][3] = 20;
	graph[1][0] = 10;
	graph[1][1] = 0;
	graph[1][2] = 35;
	graph[1][3] = 25;
	graph[2][0] = 15;
	graph[2][1] = 35;
	graph[2][2] = 0;
	graph[2][3] = 30;
	graph[3][0] = 20;
	graph[3][1] = 25;
	graph[3][2] = 30;
	graph[3][3] = 0;
	*/
	

	a_star_algo(n, graph, g, h, 0);

	return 0;
}
