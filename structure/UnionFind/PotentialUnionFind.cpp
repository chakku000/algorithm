/*
 * 重み付きUnionFind
 *
 * 各ノードの重みを保存
 * 各ノード間の重みのdiffを計算可能
 */
struct PotentialUnionFind{
    vector<int> par,rank;
    vector<long long> diff_weight;

    PotentialUnionFind(int n){
        par.resize(n);
        rank.resize(n);
        diff_weight.resize(n);
        for(int i=0;i<n;i++){
            par[i]=i;   //自身を親に設定
            rank[i]=0;
            diff_weight[i]=0;
        }
    }

    int root(int x){
        if(par[x]==x) return x;
        else{   // 経路圧縮
            int r=root(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = r;
        }
    }

    bool same(int x,int y){ return root(x) == root(y); }

    long long weight(int x){
        root(x);    // 経路圧縮
        return diff_weight[x];
    }

    // @assert root(x) == root(y)
    // @return weight[y] - weight[x]
    long long diff(int x,int y){
        return weight(y) - weight(x);
    }

    // weight(y) - weight(x) = w となるようにmerge
    bool merge(int x,int y,long long w){
        w += weight(x);
        w -= weight(y);

        x = root(x); y = root(y);
        if(x == y) return false;

        if(rank[x] < rank[y]){
            swap(x,y);
            w = -w;
        }
        // @assert rank[x] > rank[y]

        if(rank[x] == rank[y]){
            rank[x]++;
        }
        par[y] = x;

        // xがyの親になる -> xとyの差分をdiff_weight[y]に記録
        diff_weight[y] = w;
        return true;
    }
};

// verify ABC087D

int main(){
    int L[200005],R[200005];
    ll D[200005];
    ll N,M; scanf("%lld %lld",&N,&M);
    PotentialUnionFind puf(N);
    for(int i=0;i<M;i++){
        scanf("%d %d %lld",&L[i],&R[i],&D[i]);
        L[i]--;
        R[i]--;
        puf.merge(R[i],L[i],D[i]);
    }


    for(int i=0;i<M;i++){
        if(puf.diff(R[i],L[i]) == D[i]) continue;
        else{
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
