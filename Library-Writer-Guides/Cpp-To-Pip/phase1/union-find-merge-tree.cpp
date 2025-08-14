// Tiny script to compute H0 using the Union-Find datastructure.

#include <iostream>
#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>

float sampleData[][2] = {
  {1.0,0.0}, {1.0,1.0}, {0.0, 1.0}, {0.0,0.0},
  {0.5,0.5}, {0.75,0.25}, {0.25,0.75}
};

struct node {
  int dataindex;
  node* parent;
};

float dist2(int ix, int iy) {
  return (sampleData[ix][0]-sampleData[iy][0])*(sampleData[ix][0]-sampleData[iy][0]) + (sampleData[ix][1]-sampleData[iy][1])*(sampleData[ix][1]-sampleData[iy][1]);
}

// climb the union-find tree until you find the representative of the current component
node* find(node* x) {
  while(x->parent != x) {
    x = x->parent;
  }
  return x;
}

void unite(node* x, node* y) {
  if(x->dataindex > y->dataindex)
    return unite(y,x);
  x = find(x);
  x->parent = y;
}

int main() {
  std::vector<node> nodes;
  std::vector<std::vector<float> > distances;

  // Create tree nodes; compute distances
  for(int i=0; i < sizeof(sampleData)/sizeof(sampleData[0]); i++) {
    node* node_i = new node();
    node_i->dataindex = i;
    node_i->parent = node_i;
    
    nodes.push_back(*node_i);
    std::vector<float> dist_i;
    for(int j=0; j < sizeof(sampleData)/sizeof(sampleData[0]); j++) {
      dist_i.push_back(dist2(i,j));
    }
    distances.push_back(dist_i);
  }

  std::vector<std::pair<int,int> > edges;
  for(int i=0; i < sizeof(sampleData)/sizeof(sampleData[0]); i++) {
    for(int j=i+1; j < sizeof(sampleData)/sizeof(sampleData[0]); j++) {
      edges.push_back(std::make_pair(i,j));
    }
  }
  
  // sort distances
  std::sort(edges.begin(), edges.end(), [&](std::pair<int,int> first, std::pair<int,int> second) { return distances[std::get<0>(first)][std::get<1>(first)] < distances[std::get<0>(second)][std::get<1>(second)]; });

  // one edge at a time, merge components (if necessary), or file the edge as an H1 critical edge (otherwise)
  std::vector<std::pair<int,int> > h1critical;
  std::vector<float> h0deaths;
  for(const auto& edge : edges) {
    int s = std::get<0>(edge);
    int t = std::get<1>(edge);
    node* sr = find(&nodes[s]);
    node* tr = find(&nodes[t]);
    if(sr && tr && sr != tr) {
      // merge event
      unite(sr,tr);
      h0deaths.push_back(distances[s][t]);
    } else {
      // new critical edge
      h1critical.push_back(edge);
    }
  }

  std::cout << "H0 intervals:" << std::endl;
  for(float h0d : h0deaths) {
    std::cout << "[0," << h0d << ")" << std::endl;
  }
  std::cout << "[0,∞)" << std::endl;
}
