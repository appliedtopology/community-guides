// Library to compute H0 using the Union-Find datastructure.

#include "union-find.hpp"

float dist2(int ix, int iy, std::vector<std::array<float,2> > data) {
  return (data[ix][0]-data[iy][0])*(data[ix][0]-data[iy][0]) + (data[ix][1]-data[iy][1])*(data[ix][1]-data[iy][1]);
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

std::vector<node> make_nodes(std::vector<std::array<float,2> > data, int npts) {
  std::vector<node> nodes;
  for(int i=0; i < npts; i++) {
    node* node_i = new node();
    node_i->dataindex = i;
    node_i->parent = node_i;
    
    nodes.push_back(*node_i);
  }
  return nodes;
}

std::vector<std::vector<float> > make_distances(std::vector<std::array<float,2> > data, int npts) {
  std::vector<std::vector<float> > distances;
  for(int i=0; i < npts; i++) {
    std::vector<float> dist_i;
    for(int j=0; j < npts; j++) {
      dist_i.push_back(dist2(i,j, data));
    }
    distances.push_back(dist_i);
  }
  return distances;
}

std::vector<std::pair<int, int> > sorted_edges(std::vector<std::vector<float> > distances) {
  std::vector<std::pair<int,int> > edges;
  for(int i=0; i < distances.size(); i++) {
    for(int j=i+1; j < distances.size(); j++) {
      edges.push_back(std::make_pair(i,j));
    }
  }
  
  // sort distances
  std::sort(edges.begin(), edges.end(), [&](std::pair<int,int> first, std::pair<int,int> second) { return distances[std::get<0>(first)][std::get<1>(first)] < distances[std::get<0>(second)][std::get<1>(second)]; });
  return edges;
}

std::pair<
  std::vector<float>,
  std::vector<std::pair<int,int> >
  > find_deaths_criticals(std::vector<node>& nodes, const std::vector<std::pair<int, int> >& edges, const std::vector<std::vector<float> >& distances) {
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
  return std::make_pair(h0deaths, h1critical);
}

