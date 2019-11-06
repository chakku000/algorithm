/* 2次元imos */
struct Imos2D{
    int h,w;
    vector<vector<int>> tbl;
    Imos2D(int xsize,int ysize) : h(xsize), w(ysize), tbl(xsize+5,vector<int>(ysize+5,0)){}

    /* 座標(x,y)から縦にhi,横にwiの領域だけa加算 */
    void add(int x,int y,int hi,int wi,int a){
        tbl[x][y]+=a;
        tbl[x+hi][y]-=a;
        tbl[x][y+wi]-=a;
        tbl[x+hi][y+wi]+=a;
    }

    /* 各マスの値を計算 */
    vector<vector<int>> run(){
        for(int x=0;x<h;x++){
            for(int y=1;y<w;y++){
                tbl[x][y]+=tbl[x][y-1];
            }
        }
        for(int y=0;y<w;y++){
            for(int x=1;x<h;x++){
                tbl[x][y]+=tbl[x-1][y];
            }
        }
        return tbl;
    }

    /* 出力: 左下が(0,0) */
    void print(){
        for(int y=4*K-1;y>=0;y--){
            for(int x=0;x<4*K;x++){
                cerr << tbl[x][y] << " ";
            }
            cerr << "\n";
        }
    }
};

// verify https://atcoder.jp/contests/arc089/submissions/8317071
