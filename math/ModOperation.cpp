// x^n
long long mod_pow(long long x,long long n,long long MOD=1000000007LL){
    long long res=1;
    while(n){
        if(n&1) res=(res*x)%MOD;
        x=(x*x)%MOD;
        n>>=1;
    }
    return res;
}

// x^-1
long long mod_inv(long long x,long long MOD=1000000007LL){
    return mod_pow(x,MOD-2);
}

// x + y
long long mod_add(long long x,long long y,long long MOD=1000000007LL){
    return (x+y)%MOD;
}

// x-y
long long mod_sub(long long x,long long y,long long MOD=1000000007LL){
    return (x-y+MOD)%MOD;
}

// x * y
long long mod_mul(long long x, long long y, long long MOD=1000000007LL){
    return x * y % MOD;
}

// x / y
long long mod_div(long long x,long long y,long long MOD=1000000007LL){
    return x * mod_inv(y,MOD) % MOD;
}


// verify M-SOLUTION C
