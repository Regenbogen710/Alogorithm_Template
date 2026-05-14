#include<bits/stdc++.h>

#define cbug(x) cerr<<"[ "<<(#x)<<" ]:"<<x<<" "<<"\n"

using namespace std;
typedef long long ll;

//#define bogen
#ifdef bogen
const ll LEN = 1 << 22;
char buf[LEN], *P1, *P2;
#define getchar() (P1 == P2 && (P2 = (P1 = buf) + fread(buf, 1, LEN, stdin), P1 == P2)? EOF: *P1++)
#endif

inline void File(string file, string sec = "") {
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((((sec == "") ? file : sec) + ".out").c_str(), "w", stdout);
}

inline ll read() {
    ll x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') { f |= ch == '-', ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); }
    return f ? -x : x;
}

template<typename T>
inline void read(T &x) { x = read(); }

template<typename T, typename... Args>
inline void read(T &x, Args &... args) {
    read(x);
    read(args...);
}


int main() {


    return 0;
}

/*
Start coding at 20:05
Finish debugging at ???
*/
