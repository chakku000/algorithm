/*
 * Range Maximum Query
 *
 * T データ型
 * iniv 初期値(最大値なのでデフォルト0にしてある)
 */
template<typename T,T iniv=0>
struct Segtree{
    int n;
    vector<T> dat;
    Segtree(int n_){
        n = 1;
        while(n < n_) n *= 2;
        dat.resize(2*n-1);
        for(int i=0;i<2*n-1;i++) dat[i]=iniv;
    }

    void update(int k,T a){
        k+=n-1;
        dat[k]=a;
        while(k>0){
            k=(k-1)/2;
            dat[k]=max(dat[k*2+1],dat[k*2+2]);
        }
    }

    T query(int a,int b,int k,int l,int r){
        if(r<=a or b<=l) return iniv;
        else if(a<=l and r<=b) return dat[k];
        else{
            T vl = query(a,b,k*2+1,l,(l+r)/2);
            T vr = query(a,b,k*2+2,(l+r)/2,r);
            return max(vl,vr);
        }
    }

    T query(int a,int b){
        return query(a,b,0,0,n);
    }
};

// verify: yukicoder 777

using P = tuple<ll,ll,ll>;
ostream& operator<<(ostream& os,const P& p){ ll a,b,c; tie(a,b,c) = p;os << "(" << a << ","<< b <<","<<c <<")"; return os; }

int main(){
    ll N; scanf("%lld",&N);
    vector<P> cakes(N);
    rep(i,N){
        ll a,b,c; scanf("%lld %lld %lld",&a,&b,&c);
        b *= -1;
        cakes[i] = make_tuple(a,b,c);
    }
    sort(all(cakes));
    for(int i=0;i<N;i++){
        ll& b = get<1>(cakes[i]);
        b *= -1;
    }

    map<ll,ll> mp;
    for(int i=0;i<N;i++){
        mp[get<1>(cakes[i])] = 0;
    }
    int id = 0;
    for(auto& b : mp){
        b.second = id++;
    }
    for(int i=0;i<N;i++){
        ll& b = get<1>(cakes[i]);
        b = mp[b];
    }

    Segtree<ll,0> seg(N);
    vector<ll> dp(N+10,0);
    for(int i=0;i<N;i++){
        // dp[i] : cake[i]が1番下に有るときのカロリーの合計値の最大値
        ll b = get<1>(cakes[i]);
        ll c = get<2>(cakes[i]);
        ll q = seg.query(0,b);
        dp[i] = q + c;
        seg.update(b,dp[i]);
    }

    ll ans = 0;
    for(int i=0;i<N;i++){
        ans = max(ans,dp[i]);
    }
    cout << ans << endl;
}
