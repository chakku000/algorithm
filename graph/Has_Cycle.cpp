#include <bits/stdc++.h>
using namespace std;

/*
 * 有向グラフに閉路があるかをチェックする
 * 多分O(E+V)
 * 一応AOJ-GRL4Aでチェックしているがバグっている場合はSCCを用いた方がいいかも....
 */

namespace GraphCheck{
    template<typename T> struct is_graph : std::false_type{};
    template<> struct is_graph<vector<vector<int>>> : std::true_type{};
    template<> struct is_graph<vector<set<int>>> : std::true_type{};
    template<> struct is_graph<map<int,vector<int>>> : std::true_type{};
    template<> struct is_graph<map<int,set<int>>> : std::true_type{};


    vector<bool> visited,traversed;

    template<typename T> 
    bool dfs(int v,T& G){
        if(traversed[v]) return true;
        if(visited[v]) return false;
        visited[v] = true;
        traversed[v] = true;

        for(int u : G[v]){
            if(traversed[u]) return true;
            if(dfs(u,G)) return true;
        }

        traversed[v] = false;
        return false;
    }

    template<typename T>
        bool hasCycle(const T& G){
            static_assert(is_graph<T>::value, "T is not appropriate Graph Type");
            visited.assign(G.size(),false);
            traversed.assign(G.size(),false);
            for(int i=0;i<(int)G.size();i++){
                if(visited[i]) continue;
                if(dfs(i,G)) return true;
            }
            return false;
        }
};


// verify AOJ GRL_4_A
int main(){
    int v,e;
    cin >> v >> e;
    vector<vector<int>> G(v);
    for(int i=0;i<e;i++){
        int s,t; cin >> s >> t;
        G[s].push_back(t);
    }

    bool cyclic = GraphCheck::hasCycle(G);
    if(cyclic) cout << 1 << endl;
    else cout << 0 << endl; 
}
