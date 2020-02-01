/*
 * 最長増加部分列の長さを求める
 * 計算量 : O(NlogN)
 *
 * 実装 : is_strictがtrueなら厳密単調増加部分列列
 *      : is_strictがfalseなら広義単調増加部分列
 *
 * 注意 : 求めるのは部分列は連続しなくてもよい
 */


#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T,const T inf = (1LL<<30)>
int lis(const std::vector<T>& s, bool is_strict=true){
    vector<T> dp(s.size()+5,inf);
    for(const auto& v : s){
        auto idx = is_strict ?  lower_bound(dp.begin(),dp.end(),v) :
                                 upper_bound(dp.begin(),dp.end(),v);
        *idx = v;
    }
    return lower_bound(dp.begin(),dp.end(),inf) - dp.begin();
}

int main(){
    int n; cin >> n;
    vector<long long> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }

    cout << lis(a) << endl;
}
