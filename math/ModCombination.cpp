#include <bits/stdc++.h>
using namespace std;

// O(N log mod)
template<long long MOD=1000000007ll>
struct ModCombination{
    vector<long long> f,fi;
    ModCombination(){}
    ModCombination(int N){
        init(N);
    }

    // x^-1
    long long invp(long long x){
        return mod_pow(x,MOD-2);
    }

    long long mod_pow(long long x,long long n){
        long long res=1;
        while(n){
            if(n&1) res=(res*x)%MOD;
            x=(x*x)%MOD;
            n>>=1;
        }
        return res;
    }

    void init(int N){
        f.resize(N+1);
        fi.resize(N+1);
        f[0]=1;
        for(int i=1;i<N+1;i++) f[i]=(f[i-1]*i)%MOD;
        for(int i=0;i<N+1;i++) fi[i]=invp(f[i]);
    }

    // nCr
    long long get(long long n,long long r){
        long long ret=f[n];
        ret=(ret*fi[r])%MOD;
        ret=(ret*fi[n-r])%MOD;
        return ret;
    }
};

int main(){
    long long h,w,a,b;
    cin >> h >> w >> a >> b;

    const long long mod = 1e9+7;
    ModCombination<> cmb(h+w+2);

    long long ans=0;
    for(int i=0;i<w-b;i++){
        int x=i+b; 
        int y=h-a-1;
        long long s=cmb.get(x+y,x);
        x=a-1;
        y=w-b-1-i;
        long long t=cmb.get(x+y,x);
        ans += s*t%mod;
        ans %= mod;
    }
    cout << ans << endl;
}
