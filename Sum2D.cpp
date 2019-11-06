/*
 * 2次元累積和
 * 注意: Modに非対応
 * 実装: 周囲に番兵として0を配置しているのでprintではx,y軸方向に1増えて表示される
 */
template<typename T=int>
struct Sum2D{
    int H,W;
    vector<vector<T>> tbl;
    Sum2D(int h,int w) : H(h), W(w), tbl(h+10,vector<T>(w+10,0)){}
    void add(int x,int y,T a){
        tbl[x+1][y+1]+=a;
    }
    void run(){
        for(int x=0;x<=H;x++) for(int y=0;y<=W;y++) tbl[x][y+1]+=tbl[x][y];
        for(int x=0;x<=H;x++) for(int y=0;y<=W;y++) tbl[x+1][y]+=tbl[x][y];
    }
    /* [sx,gx) x [sy,gy)の領域の値を取る */
    T get(int sx,int sy,int gx,int gy){
        return tbl[gx][gy]-tbl[sx][gy]-tbl[gx][sy]+tbl[sx][sy];
    }
    /* 左下が(0,0) */
    void print(){
        for(int y=W;y>=0;y--){
            for(int x=0;x<=H;x++){
                cerr << tbl[x][y] << " ";
            }
            cerr << "\n";
        }
    }
};

// verify : https://atcoder.jp/contests/arc089/submissions/8317468
