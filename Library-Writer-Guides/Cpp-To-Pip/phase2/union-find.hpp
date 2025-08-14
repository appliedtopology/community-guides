#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>

struct node {
  int dataindex;
  node* parent;
};

float dist2(int ix, int iy);

node* find(node* x);

void unite(node* x, node* y);

std::vector<node> make_nodes(float data[][2], int npts);

std::vector<std::vector<float> > make_distances(float data[][2], int npts);

std::vector<std::pair<int, int> > sorted_edges(std::vector<std::vector<float> > distances);

std::pair<
  std::vector<float>,
  std::vector<std::pair<int,int> >
  > find_deaths_criticals(std::vector<node>& nodes, const std::vector<std::pair<int, int> >& edges, const std::vector<std::vector<float> >& distances);
