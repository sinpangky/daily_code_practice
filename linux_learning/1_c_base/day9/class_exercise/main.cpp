#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(){
  vector<int> graph_vector[5];
  graph_vector[0].push_back(2);
  graph_vector[0].push_back(3);

  graph_vector[1].push_back(3);
  graph_vector[1].push_back(4);

  graph_vector[2].push_back(3);
  graph_vector[2].push_back(0);

  graph_vector[3].push_back(0);
  graph_vector[3].push_back(1);
  graph_vector[3].push_back(2);
  graph_vector[3].push_back(4);

  graph_vector[4].push_back(1);
  graph_vector[4].push_back(3);
}