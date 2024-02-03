#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS (vector<int> vector_graph[], int length) {
  vector<int> visited ;
  for(int i =0;i<length;i++) {
    visited.push_back(0);
  }
  queue<int> visit_queue;
  visit_queue.push(0);
  visited[0] =1;
  while (visit_queue.size()){
    int a = visit_queue.front();
    cout<<a<<" ";
    visit_queue.pop();
    vector<int>::iterator it;
    for(it = vector_graph[a].begin();it!=vector_graph[a].end();++it){
      if(visited[*it]){
        continue;
      } else {
        visit_queue.push(*it);
        visited[*it] =1;
      }
    }
  }
  cout<<'\n';
}



int main() {
// 无向不带权
// 0 1
// /\ /\
// / \/ \
// 2 --- 3 --- 4
//
vector<int> vector_graph[5]; vector_graph[0].push_back(2); vector_graph[0].push_back(3);
      vector_graph[1].push_back(3);
      vector_graph[1].push_back(4);
      vector_graph[2].push_back(0);
      vector_graph[2].push_back(3);
      vector_graph[3].push_back(0);
      vector_graph[3].push_back(1);
      vector_graph[3].push_back(2);
      vector_graph[3].push_back(4);
      vector_graph[4].push_back(1);
      vector_graph[4].push_back(3);
      //DFS(vector_graph, 5);
      BFS(vector_graph, 5);
}