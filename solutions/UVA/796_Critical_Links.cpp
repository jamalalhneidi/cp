/*

Critical Links

https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&category=0&problem=737

graphs
bridges


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

bool chmin(int &a, int b) { return a > b ? a = b, true : false; }

void solve(int n) {
    vvi adj(n);
    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u;
        string s;
        cin >> s;
        s.pop_back();
        s = s.substr(1);
        int k = stoi(s);
        adj[u].resize(k);
        cin(adj[u]);
    }
    set<pii> bridges;
    vpii ans;
    int timer = 0;
    vi tin(n), low(n);
    vb visited(n);
    function<void(int, int)> addBridge = [&](int u, int v) {
        if (u > v) swap(u, v);
        if (bridges.insert({u, v}).S) ans.eb(u, v);
    };
    function<void(int, int)> dfs = [&](int u, int p) {
        visited[u] = true;
        tin[u] = low[u] = timer++;
        for (auto v : adj[u]) {
            if (v == p) continue;
            if (visited[v]) {
                chmin(low[u], tin[v]);
            } else {
                dfs(v, u);
                chmin(low[u], low[v]);
                if (tin[u] < low[v]) addBridge(u, v);
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) dfs(i, -1);
    }
    sort(all(ans));
    cout << ans.size() << " critical links" << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].F << " - " << ans[i].S << endl;
    }
    cout << endl;
}

int main() {
    fast;
    int n;
    while (cin >> n) {
        solve(n);
    }
}
/*



 */