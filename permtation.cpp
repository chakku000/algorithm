// 置換(Permutation)

/*
 * 置換適用
 * before : 適用対象のベクトル
 * f : 置換
 */
vector<int> replace(const vector<int>& before,const vector<int>& f){
    int n = before.size();
    vector<int> ret(n);
    for(int i=0;i<n;i++){
        ret[i] = before[f[i]];
    }
    return ret;
}

/*
 * 置換累乗
 * 置換を複数回適用する場合は高速累乗したほうが良い
 * f : 置換
 * c : 回数
 * 返り値 : f*f*f*...*f (fをc回かけ合わせた置換)
 */
vector<int> pow(const vector<int>& f,int c){
    int n = f.size();
    vector<int> ret(n);
    iota(all(ret),0);
    vector<int> x(f);
    while(c>0){
        if(c&1) ret = replace(ret,x);
        x = replace(x,x);
        c >>= 1;
    }
    return ret;
}

// not Verify
// You should test on ABC013 D
