#include <bits/stdc++.h>
using namespace std;

struct BIT{
    using T = long long;
    int n;
    vector<T> bit;
    BIT(){}
    BIT(int n_){
        n = n_;
        bit.assign(n,0);
    }
    // sum of data[0] + ... + data[i-1]
    T sum(int a){
        T ret=0;
        for(int x=a-1;x>=0;x=(x&(x+1))-1){
            ret+=bit[x];
        }
        return ret;
    }
    void add(int a,int w){
        for(int x=a;x<n;x|=x+1){
            bit[x]+= w;
        }
    }

    // sum(i) >= xとなる最小のiを返す
    // つまり前から何個の要素の累積を取るとxを超えるかを返す
    // sum(all) < xの場合はnを返す
    // TODO : 動作が正しい自信がないので何かでVerifyする必要がある
    int lower_bound(T x){
        if(x==0) return 0;
        int l=0;
        int r=n;
        while(r-l>1){
            const int m=(l+r)/2;
            if(sum(m)>=x) r=m;
            else l=m;
        }
        return r;
    }
};
