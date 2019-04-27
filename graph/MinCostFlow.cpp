#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 最小費用流
 * O(FVE)
 * 注意 :: この実装はOne Shot. min_cost_flowの内部でGに対する変更があるので2回以上呼び出すと間違った出力になる
 */
struct MinCostFlow{
    const int inf = std::numeric_limits<int>::max()/3;
    struct edge{
        int to,cap,cost,rev;
        edge(){}
        edge(int t,int ca,int co,int r) : to(t),cap(ca),cost(co),rev(r){}
    };

    int V;  // # of node 
    vector<vector<edge>> G;
    MinCostFlow(){}
    MinCostFlow(int V_){ init(V_); }

    void init(int V_){
        V = V_;
        G.resize(V);
    }

    void add_edge(int from,int to,int cap,int cost){
        G[from].emplace_back(to,cap,cost,G[to].size());
        G[to].emplace_back(from,0,-cost,G[from].size()-1);
    }

    // s->tに向かって流量f流すときの最小費用
    // もしs->tに向かってf流せない場合は-1
    int min_cost_flow(int s,int t,int f){
        int res=0;
        vector<int> dist(V,inf);
        vector<int> prevv(V),preve(V);
        while(f>0){
            dist.assign(V,inf);
            dist[s] = 0;
            bool update=true;
            while(update){
                update=false;
                for(int v=0;v<V;v++){
                    if(dist[v]==inf) continue;
                    for(int i=0;i<(int)G[v].size();i++){
                        edge &e = G[v][i];
                        if(e.cap>0 and dist[e.to] > dist[v]+e.cost){
                            dist[e.to] = dist[v] + e.cost;
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            update = true;
                        }
                    }
                }
            }

            if(dist[t] == inf) return -1;   // 流量fを流すことは不可能

            int d = f;
            for(int v=t;v!=s;v=prevv[v]) d = min(d,G[prevv[v]][preve[v]].cap);
            f -= d;
            res += d * dist[t];
            for(int v=t;v!=s;v=prevv[v]){
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};


// Verify : AOJ GRL_6_B: Minimum Cost Flow
int main(){
    int V,E,F; cin >> V >> E >> F;
    MinCostFlow graph(V);
    for(int i=0;i<E;i++){
        int u,v,c,d;
        cin >> u >> v >> c >> d;
        graph.add_edge(u,v,c,d);
    }

    cout << graph.min_cost_flow(0,V-1,F) << endl;
}
