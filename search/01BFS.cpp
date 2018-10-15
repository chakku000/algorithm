#include <bits/stdc++.h>
using namespace std;


// 辺 (to,cost)
using edge = pair<int,int>;

// graph : 隣接リスト
// start : 始点
vector<long long> bfs01(const vector<vector<edge>>& graph,int start){
    const long long inf = numeric_limits<long long>::max()/3;
    int N = graph.size();
    vector<long long> d(N,inf);
    deque<pair<int,long long>> deq;
    d[start] = 0;
    deq.push_front(make_pair(start,0));
    while(!deq.empty()){
        auto p = deq.front(); deq.pop_front();

        for(const auto q : graph[p.first]){
            if(d[q.first] <= p.second + q.second) continue;

            d[q.first] = p.second + q.second;
            if(q.second == 0) deq.push_front(make_pair(q.first,d[q.first]));
            if(q.second == 1) deq.push_back(make_pair(q.first,d[q.first]));
        }
    }
    return d;
}

// validate : ARC084 D Small Multiple
int main(){
    int K; cin >> K;
    vector<vector<edge>> g(K);
    for(int i=0;i<K;i++){
        g[i].push_back(make_pair((i+1)%K,1));
        g[i].push_back(make_pair((i*10)%K,0));
    }

    auto dist = bfs01(g,1);
    cout << dist[0] + 1 << endl;
}
