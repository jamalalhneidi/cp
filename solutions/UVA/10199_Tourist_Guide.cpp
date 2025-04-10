/*

Tourist Guide

https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1140

graphs (trees)
articulation points

 */

#include "bits/stdc++.h"

#ifdef COTATO

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
#define ceil(a, b) (!(a) ? 0 : ((a) - 1) / (b) + 1)
#define yn(b) ((b) ? yes : no)
#define between(x, l, r) ((x) >= (l) && (x) <= (r))
#define between2(i, j, n, m) (between(i, 0, n - 1) && between(j, 0, m - 1))

void solve(int n) {
    static int tc = 1;
    unordered_map<string, int> toid;
    unordered_map<int, string> toname;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        toid[s] = i;
        toname[i] = s;
    }
    vvi adj(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        int u = toid[s1], v = toid[s2];
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi visited(n), tin(n), low(n), isAP(n);
    int time = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        visited[u] = true;
        tin[u] = low[u] = time++;
        int sub = 0;
        for (auto v : adj[u]) {
            if (v == p) continue;
            if (visited[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, u);
                ++sub;
                low[u] = min(low[u], low[v]);
                isAP[u] |= p != -1 && low[v] >= tin[u];
            }
        }
        isAP[u] |= p == -1 && sub > 1;
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) dfs(i, -1);
    }
    vector<string> ans;
    for (int i = 0; i < n; ++i) {
        if (isAP[i]) ans.pb(toname[i]);
    }
    sort(all(ans));
    cout << "City map #" << tc++ << ": " << ans.size() << " camera(s) found" << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << endl;
    }
}

int main() {
    fast;
    int n;
    string sep = "";
    while (cin >> n, n) {
        cout << sep;
        sep = endl;
        solve(n);
    }
}
/*



 */