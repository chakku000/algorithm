struct BellmanFord{
    struct Edge{
        int from,to;
        long long cost;
        Edge(){}
        Edge(int from,int to,long long cost) : from(from),to(to),cost(cost) {}
    };

    int V;
    vector<Edge> es;
    vector<vector<int>> G,rG;
    vector<bool> reachable_from_s,reachable_from_t;
    BellmanFord(int v) : V(v), G(V), rG(V) {}

    void add_edge(int from,int to, long long cost){
        es.emplace_back(from,to,cost);
        G[from].push_back(to);
        rG[to].push_back(from);
    }

    /* グラフ上に負閉路があるかを判定 O(VE) */
    bool find_negative_loop(){
        vector<long long> d(V,0);
        for(int i=0;i<V;i++){
            for(const Edge& e : es){
                if(d[e.to] > d[e.from] + e.cost){
                    d[e.to] = d[e.from] + e.cost;
                    if(i==V) return true;
                }
            }
        }
        return false;
    }

    void dfs(int u){
        if(reachable_from_s[u]) return;
        reachable_from_s[u] = true;
        for(int v : G[u]){
            dfs(v);
        }
    }
    void rdfs(int u){
        if(reachable_from_t[u]) return;
        reachable_from_t[u] = true;
        for(int v : rG[u]){
            rdfs(v);
        }
    }

    /* 頂点sから頂点tへのパス上に負閉路があるかを判定 O(VE) */
    /* sとtの両方から到達可能な頂点のみ考慮する */
    bool find_negative_path(int s,int t){
        reachable_from_s.resize(V); for(int i=0;i<V;i++) reachable_from_s[i] = false;
        reachable_from_t.resize(V); for(int i=0;i<V;i++) reachable_from_t[i] = false;
        dfs(s);
        rdfs(t);
        vector<bool> ok(V);
        for(int i=0;i<V;i++) ok[i] = reachable_from_s[i] && reachable_from_t[i];
        constexpr long long inf = 1LL << 60;
        vector<long long> d(V,inf);
        d[s] = 0;
        for(int i=0;i<2*V;i++){
            bool upd = false;
            for(auto& e : es){
                if(!ok[e.to]) continue;
                if(!ok[e.from]) continue;
                if(d[e.from] != inf && d[e.to] > d[e.from] + e.cost){
                    d[e.to] = d[e.from] + e.cost;
                    upd = true;
                }
            }
            if(upd && i >= V) return true;
        }
        return false;
    }

    /* 頂点sからの最短距離計算 */
    vector<long long> run(int s){
        constexpr long long inf = 1LL << 60;
        vector<long long> d(V,inf);
        d[s] = 0;
        for(int i=0;i<V;i++){
            for(const Edge& e : es){
                if(d[e.from] != inf && d[e.to] > d[e.from] + e.cost){
                    d[e.to] = d[e.from] + e.cost;
                }
            }
        }
        return d;
    }
};

