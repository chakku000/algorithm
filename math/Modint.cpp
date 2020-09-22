// Mは法 (%Mで計算をする)

template<uint64_t M>
struct Modint{
    uint64_t x;

    Modint() : x(0){}
    Modint(uint64_t b) : x((b>=0) ? (b%M) : ((b%M+M)%M)){}

    Modint operator+(const Modint &v) const {
        return Modint(x+v.x);
    }
    Modint operator-(const Modint &v) const {
        return Modint(x-v.x);
    }
    Modint operator*(const Modint &v) const {
        return Modint(x*v.x);
    }
    Modint operator/(const Modint &v) const {
        return *this * v.inverse();
    }

    Modint &operator*=(const Modint &v){
        x = x * v.x % M;
        return *this;
    }

    Modint inverse() const {
        return this->pow(M-2);
    }

    Modint pow(uint64_t n) const {
        Modint ret(1);
        Modint z(x);
        while(n>0){
            if(n&1) ret *= z;
            z *= z;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream& os, const Modint &a){
        return os << a.x;
    }
};

// using modint = Modint<1000000007LL> とかするといい


// Verify
// https://atcoder.jp/contests/kupc2019/tasks/kupc2019_d
