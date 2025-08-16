#include <iostream>


#include "union-find.hpp"

float sampleData[][2] = {
  {1.0,0.0}, {1.0,1.0}, {0.0, 1.0}, {0.0,0.0},
  {0.5,0.5}, {0.75,0.25}, {0.25,0.75}
};


int main() {
  std::vector<node> nodes = make_nodes(sampleData, sizeof(sampleData)/sizeof(sampleData[0]));
  std::vector<std::vector<float> > distances = make_distances(sampleData, sizeof(sampleData)/sizeof(sampleData[0]));

  std::vector<std::pair<int,int> > edges = sorted_edges(distances);

  std::pair<
  std::vector<float>,
  std::vector<std::pair<int,int> > > deaths_critical = find_deaths_criticals(nodes, edges, distances);

  auto h0deaths = std::get<0>(deaths_critical);
  auto h1critical = std::get<1>(deaths_critical);

  std::cout << "Union-Find H0/H1 Version " << UnionFind_VERSION_MAJOR << "." << UnionFind_VERSION_MINOR << std::endl << std::endl;
  
  std::cout << "H0 intervals:" << std::endl;
  for(float h0d : h0deaths) {
    std::cout << "[0," << h0d << ")" << std::endl;
  }
  std::cout << "[0,∞)" << std::endl;
}
