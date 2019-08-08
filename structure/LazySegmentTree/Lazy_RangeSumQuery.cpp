#include <bits/stdc++.h>
using namespace std;


/*
 * 区間更新 O(logN)
 * 区間和   O(logN)
 */
template<typename T=long long>
struct LazyRangeSumQuery{
    int n;
    vector<T> data,lazy;

    /* ルートはnode[0] */
    /* 葉はnode[n-1,2*n-1) */
    /* ノードkの子は2*k+1,2*k+2 */

    LazyRangeSumQuery(const vector<T>& v){
        n=1;
        while(n<(int)v.size()) n*=2;
        data.resize(2*n-1);
        lazy.resize(2*n-1,0);
        for(int i=0;i<(int)v.size();i++) data[i+n-1] = v[i];
        for(int i=n-2;i>=0;i--) data[i] = data[i*2+1] + data[i*2+2];
    }

    // 区間[a,b)に値xを加算する
    void add_impl(int a,int b,T x,int k,int l,int r){
        data[k] += lazy[k];
        if(2*k+2 < 2*n-1){
            lazy[2*k+1] += lazy[k]/2;
            lazy[2*k+2] += lazy[k]/2;
        }
        lazy[k] = 0;

        if(b <= l || r <= a) return;
        if(a <= l && r <= b){ // 完全被覆 [l,r)の全てにxを加算
            const T diff = (r-l)*x;
            lazy[k] += diff;
            data[k] += lazy[k];
            if(2*k+2<2*n-1){
                lazy[2*k+1] += lazy[k]/2;
                lazy[2*k+2] += lazy[k]/2;
            }
            lazy[k] = 0;
        }
        else{   // 部分更新ではlazyには加算されない
            lazy[2*k+1] += lazy[k]/2;
            lazy[2*k+2] += lazy[k]/2;
            lazy[k] = 0;
            add_impl(a,b,x,2*k+1,l,(l+r)/2);
            add_impl(a,b,x,2*k+2,(l+r)/2,r);
            data[k] = data[2*k+1] + data[2*k+2];
        }
    }

    void add(int a,int b,T x){ add_impl(a,b,x,0,0,n); }

    // 区間[a,b)の総和を計算する
    T sum_impl(int a,int b,int k,int l,int r){
        if(b <= l || r <= a) return 0;

        if(a <= l && r <= b){ // 完全被覆 [l,r)を求める
            data[k] += lazy[k];
            if(2*k+2 < 2*n-1){
                lazy[2*k+1] += lazy[k]/2;
                lazy[2*k+2] += lazy[k]/2;
            }
            lazy[k] = 0; 
            return data[k];
        }
        else{   // 部分被覆
            data[k] += lazy[k];
            lazy[2*k+1] += lazy[k]/2;
            lazy[2*k+2] += lazy[k]/2;
            lazy[k] = 0;
            T left = sum_impl(a,b,2*k+1,l,(l+r)/2);
            T right =  sum_impl(a,b,2*k+2,(l+r)/2,r);
            return left + right;
        }
    }

    T sum(int a,int b){ return sum_impl(a,b,0,0,n); }
};

template<typename T>
void LazySegment_Viewer(const LazyRangeSumQuery<T>& seg){
    int w = 1;
    int idx = 0;
    cerr << "Lazy Segment Tree" << endl;
    while(idx < 2*seg.n-1){
        for(int i=0;i<w;i++){
            cerr << "(" << seg.data[idx+i] << "," << seg.lazy[idx+i] << ")";
            cerr << " | ";
        }
        cerr << endl;
        idx += w;
        w *= 2;
    }
}

// Verify http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G

int main(){
    int n,q; cin >> n >> q;
    vector<long long> v(n,0);
    LazyRangeSumQuery<> seg(v);
    for(int i=0;i<q;i++){
        int t; cin >> t;
        if(t==0){
            int s,t;
            long long x;
            cin >> s >> t >> x;
            s--;
            seg.add(s,t,x);
        }else{
            int s,t; cin >> s >> t;
            s--;
            long long ans = seg.sum(s,t);
            cout << ans << endl;
        }
        //LazySegment_Viewer(seg);
    }
}
