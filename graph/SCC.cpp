#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 強連結成分分解(Strongly Connected Components)
 * O(E+V)
 */

struct SCC{
    int V; // # of node
    vector<vector<int>> G,rG;
    vector<int> vs,cmp; // vs:行きかけ順序の並び cmp:どの集合に属するか?
    vector<bool> used;

    SCC(){}
    SCC(int v){ init(v); }

    void init(int v){
        V = v;
        G.assign(V,vector<int>());
        rG.assign(V,vector<int>());
        vs.clear();
        cmp.resize(V);
    }

    void add_edge(int from,int to){
        G[from].emplace_back(to);
        rG[to].emplace_back(from);
    }

    void dfs(int v){
        used[v] = true;
        for(const int& u : G[v]) if(!used[u]) dfs(u);
        vs.push_back(v);
    }

    // @args k 何番目の成分か?
    void rdfs(int v,int k){
        used[v] = true;
        cmp[v] = k;
        for(const int& u : rG[v]) if(!used[u]) rdfs(u,k);
    }

    // @return 強連結成分分解した後の成分の数
    int scc(){
        used.assign(V,false);
        for(int v=0;v<V;v++) if(!used[v]) dfs(v);
        used.assign(V,false);
        int k=0;
        for(int i=vs.size()-1;i>=0;i--){
            if(!used[vs[i]]) rdfs(vs[i],k++);
        }
        return k;
    }

    bool is_same(int i,int j){ return cmp[i] == cmp[j]; }
};

// verify AOJ GRL_3_C
int main(){
    int v,e; cin >> v >> e;
    SCC graph(v);
    for(int i=0;i<e;i++){
        int s,t; cin >> s >> t;
        graph.add_edge(s,t);
    }
    graph.scc();
    int Q; cin >> Q;
    for(int i=0;i<Q;i++){
        int u,v; cin >> u >> v;
        if(graph.is_same(u,v)){
            cout << 1 << endl;
        }else{
            cout << 0 << endl;
        }
    }
}
