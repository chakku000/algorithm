#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <list>
using namespace std;

/*
 * LRU Cache
 * 直近にアクセスしたN個のキーとその対応する値を記憶している
 * 
 * template parameter
 *  Key_T : キーの型
 *  Val_T : 値の型
 *  invalid : 直近Nでアクセスされていないキーに対するアクセスがあった時に返す値
 *
 *  例えばLRU<int,int,-1> cache(2)は直近2つのキーを保存し、直近アクセスしていないキーにアクセスすると-1を返す
 */
template<typename Key_T,typename Val_T, Val_T invalid> 
class LRU{
    public:
        using Node = std::pair<Val_T,Key_T>;

        int cap;
        std::list<Node> lst;
        std::unordered_map<Key_T,typename std::list<Node>::iterator> mp;

        LRU(int c) : cap(c){} // コンストラクタに直近いくつの値を記録するかを与える

        Val_T get(Key_T key){
            if(!mp.count(key)) return invalid;

            auto itr = mp[key];
            auto retp = *itr;
            lst.erase(itr);
            lst.push_front(retp);
            mp[key] = lst.begin();
            return retp.first;
        }

        void put(Key_T key,Val_T val){
            if(mp.count(key)){
                auto itr = mp[key];
                auto tmp = *itr;
                tmp.first = val;
                lst.erase(itr);
                lst.push_front(tmp);
                mp[key] = lst.begin();
            }else{
                if(lst.size() == cap){ // delete last
                    auto last = *lst.rbegin();
                    mp.erase(last.second);
                    lst.pop_back();
                }
                lst.push_front(Node(val,key));
                mp[key] = lst.begin();
            }
        }
};

int main(){
    LRU<int,int,-1> cache(2);

    cache.put(2,1);
    cache.put(2,2);
    cout << cache.get(2) << endl;
    cache.put(1,1);
    cache.put(4,1);
    cout << cache.get(2) << endl;
}
