/******************************************************************************

Name:
CSC 440 - Fall 2021

Programming Assignment 2

*******************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class SocialNetwork{

  // Here are prototypes for all methods explicitly required by the assignment.
  // You are free to add any other methods you need.
  public:
    SocialNetwork();
    void build( int n );
    void print_graph();
    void add_edge( int a, int b );
    void remove_edge( int a, int b );
    bool is_in( stack<int> a, int b);
    bool DFS( int a, int b, stack<int> DFS_connected, stack<int> checked );
    bool BFS( int a, int b );
    vector<int> get_friends( int a );
    vector<int> get_friends_of_friends( int a );

  // Here you will initialize any attributes you need for your class.
  private:
    vector<vector<int> > graph;


};

// Constructor
SocialNetwork::SocialNetwork(){

}

// Method to create a blank graph representation.
void SocialNetwork::build( int n ){
    vector<int> row;
    for (int i = 0; i < n; i++){
      row.push_back(0);
    }
    for (int i = 0; i < n; i++){
      graph.push_back(row);
    }
    cout << "Create adjacency matrix "<< endl;
    print_graph();


}
void SocialNetwork::print_graph(){
  for (int i = 0; i < graph.size(); i++){
    for (int j = 0; j < graph.size(); j++){
      cout << graph[i][j];
    }
    cout << " "<< endl;
  }
  cout << " "<< endl;
}
// Method to add an edge between nodes.
void SocialNetwork::add_edge( int a, int b ){
  graph[a][b] = 1;
  graph[b][a] = 1;

  std::cout << "Add edge between node "<< a << " and " << b << '\n';
  print_graph();
}

// Method to remove an edge between nodes.
void SocialNetwork::remove_edge( int a, int b ){
  graph[a][b] = 0;
  graph[b][a] = 0;

  std::cout << "Remove edge between node "<< a << " and " << b << '\n';
  print_graph();
}
bool SocialNetwork::is_in(stack<int> a, int b){
  stack<int> temp = a;
  while (!temp.empty()){
    if (temp.top() == b){
      return true;
    }
    temp.pop();
  }
  return false;
}
// Method to perform DFS to see if b can be reached from a.
bool SocialNetwork::DFS( int a = 0, int b = 0, stack<int> DFS_connected ={}, stack<int> checked = {} ){
  for (int i = 0; i< graph.size(); i++){
    if (graph[a][i] == 1){
      if (i == b){
        return true;
      }
      if (is_in(checked, i) == false){
        checked.push(i);
        DFS_connected.push(i);
      }
      while (!DFS_connected.empty()){
        int temp = DFS_connected.top();
        DFS_connected.pop();
        if (DFS(temp, b, DFS_connected, checked) == true){
          return true;
        }
      }
      }
    }

return false;
}

// Method to perform BFS to see if b can be reached from a.
bool SocialNetwork::BFS( int a, int b ){
  stack<int> checked;
  queue<int> BFS_connected;
  for (int i = 0; i< graph.size();i++){
    if (graph[a][i] == 1){
      if (i == b){
        return true;
      }
      if (is_in(checked, i) == false){
        checked.push(i);
        BFS_connected.push(i);
      }
      }
      while (!BFS_connected.empty()){
        int temp = BFS_connected.front();
        BFS_connected.pop();
        for (int i = 0; i< graph.size();i++){
          if (graph[temp][i] == 1){
            if (i == b){
              return true;
            }
            if (is_in(checked, i) == false){
              checked.push(i);
              BFS_connected.push(i);
            }
            }
          }
        }
      }

return false;
}

// Method to get all friends of a.
vector<int> SocialNetwork::get_friends( int a ){
  vector<int> friends;

  for (int i=0; i< graph.size(); i++){
    if (graph[a][i] == 1){
      friends.push_back(i);
    }
  }
return friends;
}

// Method to get all friends-of-friends of a.
vector<int> SocialNetwork::get_friends_of_friends( int a ){
  vector<int> friends_of_friends;
  stack<int> checked;
  checked.push(a);
  for (int i = 0; i< graph.size();i++){
    if (graph[a][i] == 1){
      checked.push(i);
      for (int j = 0; j< graph.size(); j++){
        if (graph[i][j] == 1 && is_in(checked, j) == false){
          friends_of_friends.push_back(j);
        }
      }
    }
  }


return friends_of_friends;
}

// Main function can be used for testing purposes.
int main(){
  SocialNetwork sn;
  sn.build(5);
  sn.add_edge(1,2);
  sn.add_edge(0,2);
  sn.add_edge(0,3);
  sn.add_edge(4,3);
  sn.add_edge(1,3);
  sn.remove_edge(1,3);

  std::cout << " " << '\n';
  bool dfs_connected = sn.DFS(1, 3);
  std::cout <<"dfs connected 1 and 3 "<< '\n' << dfs_connected;

  std::cout << " " << '\n';
  bool bfs_connected = sn.BFS(1, 3);
  std::cout <<"bfs connected 1 and 3 "<< '\n' << bfs_connected;

  std::cout << " "<< '\n';
  vector<int> friends_of_0 = sn.get_friends(0);
  std::cout << "Friends of 0: "<< '\n';
  for (int i = 0; i < friends_of_0.size(); i++) {
			cout << friends_of_0[i] << " ";
		}

  std::cout << " " << '\n';
  vector<int> friends_of_friends = sn.get_friends_of_friends(0);
  cout << "friends of 0's friends: " << '\n';
  for (int i = 0; i < friends_of_friends.size(); i++){
    cout << friends_of_friends[i]<< " ";
  }

  return 0;
}
