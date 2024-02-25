/*

Intern Florist

https://codeforces.com/gym/104974/problem/E

hashing


 */

#include "bits/stdc++.h"

#ifdef LOCAL

#include "templates/others/dbg.cpp"

#else
#define dbg(...)
#define dbgln(...)
#endif

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef queue<int> qi;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool>> vvb;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vector<pll>> vvpll;
typedef vector<char> vc;
typedef vector<vector<char>> vvc;
typedef vector<string> vs;
typedef set<int> si;
typedef set<ll> sll;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
#define fast ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define endl '\n'
#define all(a) a.begin(), a.end()
#define yes "YES"
#define no "NO"
#define spc ' '
#define INF INT_MAX
#define LLINF LONG_LONG_MAX
#define NINF INT_MIN
#define LLNINF LONG_LONG_MIN
#define pb push_back
#define pf push_front
#define eb emplace_back
#define F first
#define S second
#define cin(a) \
    for (auto &_x : (a)) cin >> _x
#define cin2(a)          \
    for (auto &_x : (a)) \
        for (auto &__x : _x) cin >> __x
#define cout(a) \
    for (auto &_x : (a)) cout << _x << spc
#define len(l, r) ((r) - (l) + 1)
#define mid(l, r) ((l) + ((r) - (l)) / 2)
#define ceil(a, b) (!(a) ? 0 : ((a)-1) / (b) + 1)
#define yn(b) ((b) ? yes : no)
#define between(x, l, r) ((x) >= (l) && (x) <= (r))
#define between2(i, j, n, m) (between(i, 0, n - 1) && between(j, 0, m - 1))

typedef __int128 lll;
typedef pair<lll, lll> plll;

const lll P[2] = {53, 59};
const lll M[2] = {984162944621615729, 984162944621615797};

plll f(string &s) {
    plll res;
    lll p[2] = {1, 1};
    for (auto c : s) {
        res.F += (c - 'a' + 1) * p[0] % M[0];
        res.S += (c - 'a' + 1) * p[1] % M[1];
        p[0] = p[0] * P[0] % M[0];
        p[1] = p[1] * P[1] % M[1];
    }
    return res;
}

void solve() {
    int q;
    cin >> q;
    set<plll> st;
    cin.ignore();
    while (q--) {
        string s;
        getline(cin, s);
        if (s == "ask") {
            cout << st.size() << endl;
            continue;
        }
        string filename = s.substr(s.find(' ') + 1);
        auto h = f(filename);
        if (s.starts_with("touch"))
            st.insert(h);
        else
            st.erase(h);
    }
}

int main() {
    fast;
    int t = 1;
#ifdef MULTI
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i) {
        solve();
        i != t &&cout << endl;
    }
}
/*



 */