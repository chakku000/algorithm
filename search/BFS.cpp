#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(int)(n);i++)
/*
 * BFSで盤面の始点から到達可能な場所を調べる
 */


constexpr int INF = std::numeric_limits<int>::max()/3;
constexpr int dx[]={1,0,-1,0} ,dy[] = {0,1,0,-1};
/*
 * @argv maze 探索する盤面
 * @argv H 盤面の高さ
 * @argv W 盤面の幅
 * @argv dist 始点からの距離の盤面
 * @argv sx,sy 始点
 * @argv NG 盤面上で侵入不可の文字
 */
template<typename Maze,typename Dist>
Dist& bfs(const Maze& maze,int H,int W,Dist& dist,int sx,int sy, char NG){
    for(int i=0;i<H;i++) for(int j=0;j<W;j++) dist[i][j] = INF;

    using P = pair<int,int>;
    queue<P> que;
    que.push(P(sx,sy));
    dist[sx][sy] = 0;
    while(!que.empty()){
        int x = que.front().first;
        int y = que.front().second;
        que.pop();

        for(int k=0;k<4;k++){
            const int nx = x + dx[k];
            const int ny = y + dy[k];
            if(nx<0 || nx>=H || ny<0 || ny>=W) continue;
            if(maze[nx][ny] == NG) continue;
            if(dist[nx][ny] != INF) continue;
            dist[nx][ny] = dist[x][y] + 1;
            que.push(P(nx,ny));
        }
    }
    return dist;
}

/*
 * validate ATC001 A (距離については未検証)
 */

int main(){
    int H,W; cin >> H >> W;
    vector<string> s(H);
    rep(i,H) cin >> s[i];

    int sx,sy,gx,gy;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(s[i][j] == 's'){
                sx = i;
                sy = j;
            }
            if(s[i][j] == 'g'){
                gx = i;
                gy = j;
            }
        }
    }

    vector<vector<int>> dist(H,vector<int>(W,0));
    dist = bfs(s,H,W,dist,sx,sy,'#');

    if(dist[gx][gy] == INF){
        cout << "No" << endl;
    }else{
        cout << "Yes" << endl;
    }
}
