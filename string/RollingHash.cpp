#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct fin{ fin(){ cin.tie(0); ios::sync_with_stdio(false); } } fin_;

// 4つのHashを用いる場合はこのようになる

/*
 * H[l,r) := 文字列S[l,r)のhash値
 * B := 基数
 *
 * S := 長さmの文字列
 * H[0,m) = (s[0]*B^(m-1) + s[1]*B^(m-2) + ... + s[m-1]*B^0) % MOD
 *
 * H[l,r) = H[0,r) - H[0,l)*B^(r-l) (mod注意)
 */

/*
 * NOTE:
 * TLEする場合はhash_sizeを1にする
 */

struct RollingHash{
    static const int hash_size = 2;
    vector<long long> mod{999999937LL, 1000000007LL};
    const long long base = 9973;
    vector<long long> pw[hash_size], hs[hash_size];
    RollingHash(const string& s){
        int n = s.size();
        for(int i=0;i<hash_size;i++){
            pw[i].resize(n+1);
            pw[i][0] = 1;
            for(int j=0;j<n;j++) pw[i][j+1] = pw[i][j] * base % mod[i];
 
            hs[i].resize(n+1);
            hs[i][0] = 0;
            for(int j=0;j<n;j++){
                hs[i][j+1] = hs[i][j]*base%mod[i]+s[j];
                if(hs[i][j+1]>=mod[i]) hs[i][j+1] -= mod[i];
            }
        }
    }
 
    long long get(int l,int r,int i) const {
        long long ret = hs[i][r] + mod[i] - (hs[i][l]*pw[i][r-l]%mod[i]);
        if(ret >= mod[i]) ret -= mod[i];
        return ret;
    }
 
    bool match(int l1, int r1, int l2, int r2) const {
        for(int i=0;i<hash_size;i++){
            if(get(l1,r1,i) != get(l2,r2,i)) return false;
        }
        return true;
    }
 
    bool match(int l, int r,const RollingHash& p, int pl, int pr) const {
        for(int i=0;i<hash_size;i++){
            if(get(l,r,i) != p.get(pl,pr,i)) return false;
        }
        return true;
    }
};

// AOJ ALDS1_14_B
int main(){
    string s1,s2;
    cin >> s1 >> s2;
    RollingHash rh1(s1);
    RollingHash rh2(s2);
    int n = s1.size();
    int m = s2.size();

    for(int i=0;i+m<=n;i++){
        if( rh1.match(i,i+m,rh2,0,m) ){
            cout << i << endl;
        }
    }
}

// ABC 141-E
