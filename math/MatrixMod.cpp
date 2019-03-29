/*
 * 行列ライブラリ
 * Note: initMat,unitMatの呼び出しにはパラメータ指定が必要
 */

template<typename T = long long>
using Mat = std::vector<std::vector<T>>;

/* n*mの零行列 */
template<typename T = long long>
Mat<T> initMat(int n,int m){
    Mat<T> ret(n,std::vector<T>(m,0));
    return ret;
}

/* サイズm*mの単位行列 */
template<typename T = long long>
Mat<T> unitMat(int m){
    Mat<T> res = initMat<T>(m,m);
    for(int i=0;i<m;i++)res[i][i]=1;
    return res;
}

template<typename T = long long>
Mat<T> mulmat(Mat<T>& a,Mat<T>& b){
    int n = a.size();
    int m = b[0].size();
    Mat<T> res = initMat<T>(n,m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        res[i][j] = 0;
        for(int k=0;k<(int)a[0].size();k++){
            res[i][j] += (a[i][k] * b[k][j])%mod;
            res[i][j] %= mod;
        }
    }
    return res;
}

template<typename T>
Mat<T> pow(Mat<T>& base,long long n){
    Mat<T> res = unitMat<ll>(base.size());
    while(n){
        if(n&1) res = mulmat(res,base);
        base = mulmat(base,base);
        n >>= 1;
    }
    return res;
}

// verified Educational Codeforces Round 60 D Magic Gems
// https://codeforces.com/contest/1117/problem/D
int main(){
    ll n,m;
    cin >> n >> m;

    vector<ll> dp(m,0);
    dp[0] = 1;
    rep(i,m){
        if(i-1 >= 0) dp[i] += dp[i-1];
        if(i-m >= 0) dp[i] += dp[i-m];
    }


    if(n < m){
        cout << dp[n] << endl;
        return 0;
    }

    auto mat = initMat<long long>(m,m);
    mat[0][0] = 1;
    mat[0][m-1] = 1;
    for(int i=1;i<m;i++) mat[i][i-1] = 1;

    auto m2 = pow(mat,n-m+1);

    ll ans = 0;
    rep(i,m){
        ans += (m2[0][i] * dp[i]);
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}
