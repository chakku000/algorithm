/*
 * UnionFind
 * + 経路圧縮
 * + 深さ保持
 * + 集合のサイズ保持
 */
struct UnionFind{
    // par[i] >= 0 --> 親
    // par[i] < 0  --> size
    // rank --> 深さ
    vector<int> par, rank;
    UnionFind(int n){
        par.resize(n,-1);
        rank.resize(n,0);
    }

    int root(int x){
        if(par[x]<0) return x;
        else return par[x]=root(par[x]);
    }

    bool same(int x,int y){
        return root(x) == root(y);
    }

    int size(int x){
        return -par[root(x)];
    }

    void merge(int x,int y){
        x = root(x);
        y = root(y);
        if(x==y) return;
        if(rank[x] < rank[y]) swap(x,y);

        // x <-- y
        par[x]+=par[y]; // fix size
        par[y]=x;
        rank[x]+=(rank[x]==rank[y]);
    }
};

// Verify
// https://atcoder.jp/contests/abc120/tasks/abc120_d
// https://atcoder.jp/contests/kupc2019/tasks/kupc2019_b
