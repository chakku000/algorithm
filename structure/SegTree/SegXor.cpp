// 1点更新
// 区間取得
template<typename T = long long>
struct SegTreeXor{
public:
    int n;
    vector<T> data;
    // data[i] <- data[i*2+1], data[i*2+2]

    SegTreeXor(){}
    SegTreeXor(int n_){
        init(n_);
    }

    void init(int n_){
        n = 1;
        while(n < n_) n *= 2;
        data.assign(2*n-1, 0LL);
    }

    void update(int idx, T x){
        idx += n-1;
        data[idx] = x;
        while(idx > 0){
            idx = (idx-1)/2;
            data[idx] = data[idx*2+1] ^ data[idx*2+2];
        }
    }

    // xor of [a,b)
    T query(int a, int b, int k, int l, int r){
        if(r <= a or b <= l) return 0;
        if(a <= l and r <= b) return data[k];
        T vl = query(a,b,k*2+1,l,(l+r)/2);
        T vr = query(a,b,k*2+2,(l+r)/2,r);
        return vl^vr;
    }

    T query(int a, int b){
        return query(a, b, 0, 0, n);
    }

    T get(int k){
        return data[k+n-1];
    }

    void print(){
        int t = 1;
        int i = 0;
        while(i < 2*n-1){
            for(int j=0;j<t;j++){
                cerr << data[i++] << " ";
            }
            t *= 2;
            cerr << endl;
        }
    }
};
