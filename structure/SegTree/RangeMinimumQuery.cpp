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
            dat[k]=min(dat[k*2+1],dat[k*2+2]);
        }
    }

    T query(int a,int b,int k,int l,int r){
        if(r<=a or b<=l) return iniv;
        else if(a<=l and r<=b) return dat[k];
        else{
            T vl = query(a,b,k*2+1,l,(l+r)/2);
            T vr = query(a,b,k*2+2,(l+r)/2,r);
            return min(vl,vr);
        }
    }

    T query(int a,int b){
        return query(a,b,0,0,n);
    }
};
