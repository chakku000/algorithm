#include <bits/stdc++.h>
using namespace std;

template<typename T> ostream& operator<<(ostream& os,const vector<T>& vec){ os << "["; for(const auto& v : vec){ os << v << ","; } os << "]"; return os; }

/*
 * 2次元幾何ライブラリ
 *
 *
 * 誤差の対応
 * a < 0 --> a < -eps
 * a <= 0 --> a < eps
 * a == 0 -> abs(a) < eps
 */

//---------- Copy from here ----------

// 必要なければ0にする
constexpr double eps = 1e-10;


template<typename T=int>
struct Point{
    T x,y;
    Point(){}
    Point(T x, T y) : x(x), y(y){} 

    friend ostream& operator << (ostream& os, const Point<T> &p){
        return os << "(" << p.x << "," << p.y << ")";
    }
};

// 比較
template<typename T>
inline bool operator < (const Point<T> &p1, const Point<T> &p2){
    return abs(p1.x-p2.x) > eps ? (p1.x < p2.x)
                                : (p1.y < p2.y);
}

// ベクトル
template<typename T> using Vector = Point<T>;

// 基本演算
template<typename T>
inline Vector<T> operator - (const Vector<T> &v1, const Vector<T> &v2){
    return Vector<T>(v1.x-v2.x, v1.y-v2.y);
}

// 外積 v1 x v2
template<typename T> 
T cross(const Vector<T> &v1, const Vector<T> &v2){
    return v1.x * v2.y - v1.y * v2.x;
}


// 凸包
// 第2引数の contain_on_the_line は凸包上の3点 a->b->cが直線上にある場合に、
// bを凸法に含むかどうかを決める. trueの場合はbも凸包に含み、falseの場合は含まない
// 返り値は反時計回りになっている(はず)
// 返り値は最も左にある頂点から始まっている
template<typename T>
vector<Point<T>> convex_hull(vector<Point<T>> ps, bool contain_on_the_line = true){
    int n = ps.size();
    sort(ps.begin(), ps.end());

    // cvは外積の値
    auto judge = [contain_on_the_line](const T cv) -> bool {
        if(is_floating_point<T>::value){ // 型Tが不動小数点の場合は誤差に注意にする
            if(contain_on_the_line){ // 直線上の点を含む
                return cv < -eps; // cv < 0 に誤差を追加
            }else{
                return cv < eps;
            }
        }else{
            if(contain_on_the_line){
                return cv < 0;
            }else{
                return cv <= 0;
            }
        }
    };

    vector<Point<T>> res(2*n);
    int k = 0;
    for(int i=0;i<n;i++){
        while(k>=2 && judge(cross(res[k-1]-res[k-2], ps[i]-res[k-1]))){
            k--;
        }
        res[k++] = ps[i];
    }

    for(int i=n-2, t=k; i>=0;i--){
        while(k > t && judge(cross(res[k-1]-res[k-2], ps[i]-res[k-1]))){
            k--;
        }
        res[k++] = ps[i];
    }
    res.resize(k-1);
    return res;
}

//------------------------------------
// verify http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
int main(){
    int n; cin >> n;
    vector<Point<int>> ps(n);
    for(int i=0;i<n;i++){
        int x,y; cin >> x >> y;
        ps[i] = Point<>(x,y);
    }

    auto convex = convex_hull(ps);

    int startid = -1;
    int x,y;
    x = 100000;
    y = 100000;

    int m = convex.size();
    for(int i=0;i<m;i++){
        auto &p = convex[i];
        if(p.y < y){
            startid = i;
            x = p.x;
            y = p.y;
        }else if(p.y == y && p.x < x){
            startid = i;
            x = p.x;
            y = p.y;
        }
    }

    cout << m << endl;
    for(int i=0;i<m;i++){
        int id = (startid + i) % m;
        cout << convex[id].x << " " << convex[id].y << endl;
    }
}
