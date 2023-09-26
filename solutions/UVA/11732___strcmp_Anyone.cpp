//  11732 - "strcmp()" Anyone?
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=2832

#include "bits/stdc++.h"

#ifdef LOCAL

#include "../templates/dbg.cpp"

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
#define fast ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
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
#define cin(a) for(auto &_x:(a)) cin>>_x
#define cin2(a) for(auto &_x:(a))for(auto &__x:_x) cin>>__x
#define cout(a) for(auto &_x:(a)) cout<<_x<<spc
#define len(l, r) ((r)-(l)+1)
#define mid(l, r) ((l)+((r)-(l))/2)
#define ceil(a, b) (!(a)?0:((a)-1)/(b)+1)
#define yn(b) ((b)?yes:no)
#define between(x, l, r) ((x) >= (l) && (x) <= (r))
#define between2(i, j, n, m) (between(i,0,n-1) && between(j,0,m-1))

struct Node {
    char key = 0;
    ll cnt = 0, end = 0, cntBros = 0;
    Node *l = 0, *m = 0, *r = 0;

};

struct Trie {
    Node *root = 0;
    ll ans = 0;

    void insert(Node *&u, Node *&p, string &s, int i = 0) {
        if (!u) u = new Node(), u->key = s[i];
        if (s[i] < u->key) return insert(u->l, p, s, i);
        if (s[i] > u->key) return insert(u->r, p, s, i);
        ans += u->cnt + u->end + p->cntBros;
        if (p->m != u) ++p->cntBros;
        if (i < s.length() - 1) {
            insert(u->m, u->m, s, i + 1);
        } else {
            ++u->end;
            ans += u->cnt;
        }
        ++u->cnt;
    }

};

void solve(int n) {
    Trie t;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        t.insert(t.root, t.root, s, 0);
    }
    cout << t.ans;
}

int main() {
    fast;
    int i = 1;
    int n;
    while (cin >> n && n) {
        cout << "Case " << i++ << ": ";
        solve(n);
        cout << endl;
    }
}
/*

 at some lvl:
    1. equal: 2*cnt words passing through the same node
    2. ends: cnt words passing through the same node
    3. not equal: cnt words not passing through the same node

 */
