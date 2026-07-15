/******************************************************************************
 * Bakaford/tilequizoneer: An automatic incidence geoquiz formulator          *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.5.30 (latest upd)                                              *
 * @Description: Ref. Incidences and Tilings [arXiv]						  *
 * @Modules: {}                                                               *
 ******************************************************************************/
 
// #pragma once
#pragma GCC optimize (2)

#include <sstream>
#include <vector>
#include <iostream>
namespace Bakaford {
	class Graph {
		public: std::vector<std::vector<signed int>> edge;
		public: std::vector<bool> vertexflag;
		public: std::vector<std::pair<signed int,signed int>> lineref;
		public: int vertexamt;
		public: Graph(void) = default;
		public: Graph(int va): vertexamt(va) {
			va++;
			vertexflag.resize(va);
			edge.resize(va);
			lineref.resize(va);
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
			quiz << "Consider " << vertexamt/2 << " free points and " << vertexamt/2 << " lines on a projective plane,\n";
			quiz << "Denote \n";
			
			for(int i=0; i<vertexamt; i+=2) {
				quiz << "  l" << i << ":=(v" << lineref[i].first << "v" << lineref[i].second << "); \n";
			}
			quiz << "Then \n";
			for(int a=0; a<vertexamt; a++) {
				for(int b=a+1; b<vertexamt; b++) {
					for(int c=b+1; c<vertexamt; c++) {
						for(int d=c+1; d<vertexamt; d++) {
							bool ring1 = (edge[a][b] && edge[b][c] && edge[c][d] && edge[d][a]);
							bool ring2 = (edge[a][b] && edge[b][d] && edge[d][c] && edge[c][a]);
							bool ring3 = (edge[a][c] && edge[c][b] && edge[b][d] && edge[d][a]);
							bool istiling1 = vertexflag[a] && !vertexflag[b] && vertexflag[c] && !vertexflag[d];
							bool istiling2 = !vertexflag[a] && vertexflag[b] && !vertexflag[c] && vertexflag[d];
							
							if((ring1 || ring2 || ring3) && (istiling1 || istiling2)) {
								count++;								
								// [Master Theorem] If all of the tilings except t0 have collinear conditions, then t0 has the collinear condition too.
								//   Then name the quiz in a format.
								if(vertexflag[a]) quiz << count << ") {v" << a << ", v" << c << ", l" << b << "^l" << d << "} are collinear.\n";
								else	          quiz << count << ") {v" << b << ", v" << d << ", l" << a << "^l" << c << "} are collinear.\n";
							}
						}
					}
				}
			}
			quiz << "If all conditions but one exist, then the remaining one does as well.";
			return quiz.str();
		}
	};
}


int main(void) {
	const int volume = 12;
	const float rho=0.7;
	Bakaford::Graph g(volume);
	srand (time(0));
	
  // Initialize the graph with random tilings here...
	for(int i = 0; i < volume; i++) {
		if(i%2) g.vertexflag[i]=1;
		else    g.vertexflag[i]=0;
		int s0=0, s1=0;
		while(s0==s1)
			s0 = (((rand()%volume)>>1)<<1)+1, s1 = (((rand()%volume)>>1)<<1)+1;
		if(i%2==0) g.lineref[i]=std::make_pair(s0,s1);
	}

	for(int epc=0; g.findtilings()<=std::max(epc,3) && epc<=rho*volume; epc++) {
		int v0idx=0, v1idx=0, l0idx=0, l1idx=0;
		while(v0idx==v1idx||l0idx==l1idx) {
			v0idx = rand()%(volume/2);
			v1idx = rand()%(volume/2);
			l0idx = rand()%(volume/2)+1;
			l1idx = rand()%(volume/2)+1;
			bool taut0=(g.lineref[l0idx].first==v0idx&&g.lineref[l0idx].second==v1idx)||(g.lineref[l0idx].first==v1idx&&g.lineref[l0idx].second==v0idx);
			bool taut1=(g.lineref[l1idx].first==v0idx&&g.lineref[l1idx].second==v1idx)||(g.lineref[l1idx].first==v1idx&&g.lineref[l1idx].second==v0idx);
			if(!taut0&&!taut1) continue;
		}
		g.addtiling(v0idx,l0idx,v1idx,l1idx);
	}

	// g.print();
	std::cout << g.exportquiz() << "\n";

	return 0;
}
