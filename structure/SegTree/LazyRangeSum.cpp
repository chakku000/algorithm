#include <bits/stdc++.h>
using namespace std;

// 遅延セグメントツリー
// 区間加算 / 区間和
template<typename T>
struct LazyRangeSum{
    int n;
    vector<T> dat, lazy;

    LazyRangeSum(vector<T> v){
        int sz = (int)v.size();
        n = 1;
        while(n < sz) n <<= 1;
        dat.resize(2*n-1,0);
        lazy.resize(2*n-1,0);

        for(int i=0;i<sz;i++) dat[i+n-1]=v[i];
        for(int i=n-2;i>=0;i--) dat[i]=dat[i*2+1]+dat[i*2+2];
    }

    inline void propagation(int k,int l,int r){
        dat[k]+=lazy[k];
        if(2*k+2<2*n-1){
            lazy[2*k+1]+=(lazy[k]/2);
            lazy[2*k+2]+=(lazy[k]/2);
        }
        lazy[k]=0;
    }

    // add to [a,b)
    void add(int a,int b, T x, int k, int l, int r){
        propagation(k,l,r);
        if(r<=a||b<=l) return;  // not overlap
        if(a<=l&&r<=b){ // [a,b) contains [l,r)
            lazy[k]+=(r-l)*x;
            propagation(k,l,r);
        }else{ // overlap
            add(a,b,x, 2*k+1, l, (l+r)/2);
            add(a,b,x, 2*k+2, (l+r)/2, r);
            dat[k]=dat[2*k+1]+dat[2*k+2];
        }
    }
    void add(int a,int b, T x){ add(a,b,x,0,0,n); }

    // sum of [a,b)
    T get(int a,int b,int k,int l, int r){
        propagation(k,l,r);
        if(r<=a||b<=l) return 0; // not overlap
        if(a<=l&&r<=b){ // contain
            return dat[k]; // 既に伝播済みなのでdatの値を返せば良い
        }
        T lv=get(a,b,2*k+1,l,(l+r)/2);
        T rv=get(a,b,2*k+2,(l+r)/2,r);
        return lv+rv;
    }
    T get(int a,int b){
        return get(a,b,0,0,n);
    }
};

// verify https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G
int main(){
    int n,q; cin >> n >> q;
    vector<long long> a(n,0);
    LazyRangeSum<long long> seg(a);
    for(int i=0;i<q;i++){
        int type; cin >> type;
        if(type==0){
            int s,t,x;
            cin >> s >> t >> x;
            s--; t--;
            seg.add(s,t+1,x);
        }else{
            int s,t; cin >> s >> t;
            s--; t--;
            cout << seg.get(s, t+1) << endl;
        }
    }
}
