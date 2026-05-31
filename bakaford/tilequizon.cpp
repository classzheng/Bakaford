/******************************************************************************
 * Bakaford/tilequizon: An automatic quiz naming formulator                   *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.5.30 (latest upd)                                              *
 * @Description: A automatic quiz naming formulator                           *
 *				  Ref: Incidences and Tilings [arXiv]						  *
 * @Modules: {}                                                               *
 ******************************************************************************/
 
#pragma once
#pragma GCC optimize (2)

#include <sstream>
#include <vector>
#include <iostream>
namespace Bakaford {
	class Graph {
		public: std::vector<std::vector<signed>> edge;
		public: std::vector<bool> vertexflag;
		public: int vertexamt;
		public: Graph(void) = default;
		public: Graph(int va): vertexamt(va) {
			vertexflag.resize(va);
			edge.resize(va);
			for(auto& is:edge) {
				is.resize(va);
				for(auto& si:is) si = 0;
			}
			return ;
		}
		public: ~Graph(void) = default;
		
		public: void print(void) {
			std::cout << "graph G {\n";
	        for (int i = 0; i < vertexamt; ++i) {
	            for (int j = i + 1; j < vertexamt; ++j) {
	                if (edge[i][j]) {
	                    std::cout << "\t" << (vertexflag[i]?"v":"l") << i << " -- " << (vertexflag[j]?"v":"l") << j << ";\n";
	                }
	            }
	        }
			std::cout << "}\n";
			return ;
	    }
	    
		public: inline void addedge(int a, int b) {
			edge[a][b] = edge[b][a] = 1;
			return ;
		}
		
		public: inline void addtiling(int a, int b, int c, int d) {
			edge[a][b] = edge[b][a] = 1;
			edge[b][c] = edge[c][b] = 1;
			edge[c][d] = edge[d][c] = 1;
			edge[d][a] = edge[a][d] = 1;
			return ;
		}
		
		public: int findtilings(void) {
			int count = 0;
			for(int a=0; a<vertexamt; a++){
				for(int b=a+1; b<vertexamt; b++){
					for(int c=b+1; c<vertexamt; c++){
						for(int d=c+1; d<vertexamt; d++){
							bool ring1 = (edge[a][b] && edge[b][c] && edge[c][d] && edge[d][a]);
							bool ring2 = (edge[a][b] && edge[b][d] && edge[d][c] && edge[c][a]);
							bool ring3 = (edge[a][c] && edge[c][b] && edge[b][d] && edge[d][a]);
							bool istiling1 = vertexflag[a] && !vertexflag[b] && vertexflag[c] && !vertexflag[d];
							bool istiling2 = !vertexflag[a] && vertexflag[b] && !vertexflag[c] && vertexflag[d];
							
							if((ring1 || ring2 || ring3) && (istiling1 || istiling2)) {
								count++;
							}
						}
					}
				}
			}
			return count;
		}
		
		public: std::string exportquiz(void) {
			int count = 0;
			std::stringstream quiz("");
			for(int a=0; a<vertexamt; a++){
				for(int b=a+1; b<vertexamt; b++){
					for(int c=b+1; c<vertexamt; c++){
						for(int d=c+1; d<vertexamt; d++){
							bool ring1 = (edge[a][b] && edge[b][c] && edge[c][d] && edge[d][a]);
							bool ring2 = (edge[a][b] && edge[b][d] && edge[d][c] && edge[c][a]);
							bool ring3 = (edge[a][c] && edge[c][b] && edge[b][d] && edge[d][a]);
							bool istiling1 = vertexflag[a] && !vertexflag[b] && vertexflag[c] && !vertexflag[d];
							bool istiling2 = !vertexflag[a] && vertexflag[b] && !vertexflag[c] && vertexflag[d];
							
							if((ring1 || ring2 || ring3) && (istiling1 || istiling2)) {
								count++;
								if(vertexflag[a]) std::cout << "{v" << a << ", v" << c << ", l" << b << "^l" << d << "} are conlinear.\n";
								else	          std::cout << "{v" << b << ", v" << d << ", l" << a << "^l" << c << "} are conlinear.\n";

								
								// [Master Theorem] If all of the tilings except t0 have conlinear conditions, then t0 has the conlinear condition too.
								//   Then name the quiz in a format.
							}
						}
					}
				}
			}
			return quiz.str();
		}
		
		public: void shrink(void) {  // Delete isolated edges.
			for(int a=0; a<vertexamt; a++){
				for(int b=a+1; b<vertexamt; b++){
					for(int c=b+1; c<vertexamt; c++){
						for(int d=c+1; d<vertexamt; d++){
							bool ring1 = (edge[a][b] && edge[b][c] && edge[c][d] && edge[d][a]);
							bool ring2 = (edge[a][b] && edge[b][d] && edge[d][c] && edge[c][a]);
							bool ring3 = (edge[a][c] && edge[c][b] && edge[b][d] && edge[d][a]);
							bool istiling1 = vertexflag[a] && !vertexflag[b] && vertexflag[c] && !vertexflag[d];
							bool istiling2 = !vertexflag[a] && vertexflag[b] && !vertexflag[c] && vertexflag[d];
							
							if((ring1 || ring2 || ring3) && (istiling1 || istiling2)) {
								edge[a][b]++, edge[b][a]++;
								edge[b][c]++, edge[c][b]++;
								edge[c][d]++, edge[d][c]++;
								edge[d][a]++, edge[a][d]++;
							}
						}
					}
				}
			}
			for(auto &is: edge) {
				for(auto &si: is) {
					if(si==1) si=0;
					// else 	  si=1;
				}
			}
			return ;
		}
	};
}


int main(void) {
	const int volume = 12, rho=7;
	Bakaford::Graph g(volume);
	srand (time(0));
	
  // Initialize the graph with random tilings here...
	for(int i = 0; i < volume; i++) {
		if(i%2) g.vertexflag[i]=1;
		else    g.vertexflag[i]=0;
	}

	for(int epc=0; g.findtilings()<=std::max(epc,3) && epc<=(rho/10.f)*volume; epc++) {
		int v0=0, v1=0, l0=0, l1=0;
		while(v0==v1||l0==l1) {
			v0 = rand()%(volume/2);
			v1 = rand()%(volume/2);
			l0 = rand()%(volume/2)+1;
			l1 = rand()%(volume/2)+1;
		}
		g.addtiling(v0,l0,v1,l1);
	}

	g.shrink();
	g.print();
	g.exportquiz();

	return 0;
}
