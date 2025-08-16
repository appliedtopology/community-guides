#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>

#include "union-find-config.h"

struct node {
  int dataindex;
  node* parent;
};

float dist2(int ix, int iy, std::vector<std::array<float,2> > data);

node* find(node* x);

void unite(node* x, node* y);

std::vector<node> make_nodes(std::vector<std::array<float,2> > data, int npts);

std::vector<std::vector<float> > make_distances(std::vector<std::array<float,2> > data, int npts);

std::vector<std::pair<int, int> > sorted_edges(std::vector<std::vector<float> > distances);

std::pair<
  std::vector<float>,
  std::vector<std::pair<int,int> >
  > find_deaths_criticals(std::vector<node>& nodes, const std::vector<std::pair<int, int> >& edges, const std::vector<std::vector<float> >& distances);
