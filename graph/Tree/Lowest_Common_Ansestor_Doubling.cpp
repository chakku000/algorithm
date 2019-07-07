#include <bits/stdc++.h>
using namespace std;

/*
 * LCA (Lowest Common Ancestor)
 * ダブリングで求める
 *
 * NOTE: グラフGはvector<vector<int>>を仮定している.
 * TODO; できればグラフGはもう少し一般化したい
 */

class LCA{
public:
    int n,root,log2_n;
    vector<vector<int>> parent; // parent[i][v]:=vから2^i回親を辿ったノード
    vector<int> depth;

    LCA(){}
    /* g:graph, r:root */
    LCA(const vector<vector<int>>& g,int r){
        init(g,r);
    }
    void init(const vector<vector<int>>& g,int r){
        n = g.size();
        log2_n = log2(n)+1;
        root = r;
        parent = vector<vector<int>>(log2_n,vector<int>(n));
        depth = vector<int>(n);
        dfs(g,root,-1,0);   // parent[0],depthの初期化
        // parentの計算
        for(int k=0;k+1<log2_n;k++){
            for(int v=0;v<n;v++){
                if(parent[k][v]<0) parent[k+1][v] = -1;
                else parent[k+1][v] = parent[k][parent[k][v]];
            }
        }
    }
    void dfs(const vector<vector<int>>& G,int v,int p,int d){
        parent[0][v] = p;
        depth[v] = d;
        for(const auto& u : G[v]){
            if(u != p) dfs(G,u,v,d+1);
        }
    }

    int get(int u,int v){
        if(depth[u]>depth[v])swap(u,v);
        for(int k=0;k<log2_n;k++){
            if((depth[v]-depth[u]) >> k & 1){
                v = parent[k][v];
            }
        }
        if(u==v) return u;
        for(int k=log2_n-1;k>=0;k--){
            if(parent[k][u] != parent[k][v]){
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};

/* verify AOJ GRL_5_C */
int main(){
    int n; cin >> n;
    vector<vector<int>> G(n);
    for(int i=0;i<n;i++){
        int k; cin >> k;
        for(int j=0;j<k;j++){
            int u; cin >> u;
            G[i].push_back(u);
        }
    }
    LCA lca(G,0);
    int q; cin >> q;
    for(int i=0;i<q;i++){
        int u,v; cin >> u >> v;
        int ans = lca.get(u,v);
        cout << ans << endl;
    }
}
