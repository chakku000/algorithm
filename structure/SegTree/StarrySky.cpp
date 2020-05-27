#include <bits/stdc++.h>
using namespace std;

/*
 * 区間加算 / 区間最小 を求める遅延伝播セグメント木
 */
template<typename T, T max_v>
struct StarrySky{
    size_t n;
    vector<T> dat, lazy;

    StarrySky(vector<T> a){
        n = 1;
        while(n<a.size()) n <<= 1;
        dat.resize(2*n-1,max_v);
        lazy.resize(2*n-1,0);
        for(size_t i=0;i<a.size();i++) dat[i+n-1]=a[i];
        for(int i=n-2;i>=0;i--) dat[i]=min(dat[i*2+1],dat[i*2+2]);
    }

    inline void propagation(int k,int l,int r){
        dat[k]+=lazy[k];
        if((size_t)k<n-1){    // 最下段でない場合
            lazy[2*k+1]+=lazy[k];
            lazy[2*k+2]+=lazy[k];
        }
        lazy[k]=0;
    }

    // add to [a,b)
    void add(int a, int b, T x, int k, int l, int r){
        propagation(k,l,r);
        if(r<=a||b<=l) return; // no overlap area
        if(a<=l&&r<=b){ // [a,b) contains [l,r)
            lazy[k]+=x;
            propagation(k,l,r);
        }else{ // overlap
            add(a,b,x,2*k+1,l,(l+r)/2);
            add(a,b,x,2*k+2,(l+r)/2,r);
            dat[k]=min(dat[2*k+1],dat[2*k+2]);
        }
    }
    void add(int a,int b, T x){
        add(a,b,x,0,0,n);
    }

    // min of [a,b)
    T get(int a,int b,int k,int l,int r){
        propagation(k,l,r);
        if(r<=a||b<=l) return max_v;
        if(a<=l&&r<=b){ // [a,b) contains [l,r)
            return dat[k];
        }else{ // overlap
            T lv=get(a,b,2*k+1,l,(l+r)/2);
            T rv=get(a,b,2*k+2,(l+r)/2,r);
            return min(lv,rv);
        }
    }
    T get(int a,int b){
        return get(a,b,0,0,n);
    }
};

// verify https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H
int main(){
    int n,q; cin >> n >> q;
    vector<long long> a(n,0);
    StarrySky<long long,(1LL<<60)> seg(a);
    for(int i=0;i<q;i++){
        int type; cin >> type;
        if(type == 0){
            int s,t,x; cin >> s >> t >> x;
            seg.add(s,t+1,x);
        }else{
            int s,t; cin >> s >> t;
            cout << seg.get(s,t+1) << endl;
        }
    }
}
