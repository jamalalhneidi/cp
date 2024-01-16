/*

Double Profiles

https://codeforces.com/problemset/problem/154/C

hashing

*2300

notes:
used 2 different hashing bases to further reduce the probability of collisions
altho one was enough apparently

also, not using the regular Σs[i]p[i] formula
but rather we're doing Σs[i]p[s[i]]
since elements positions are irrelevant
and only their values are important for comparing hashes

vectors are expensive in such tightly time limited (maybe not?) problems, better use static arrays
(same code one sub barely AC, the next sub got TLE)

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

vll P = {(ll)1e6 + 3, (ll)1e6 + 33};
vll M = {(ll)1e9 + 9, (ll)1e9 + 33};
vector<array<ll, 2>> p;
void pre() {
    if (p.size()) return;
    int n = 1e6 + 1;
    p.resize(n);
    p[0][0] = p[0][1] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            p[i][j] = p[i - 1][j] * P[j] % M[j];
        }
    }
}

void solve() {
    pre();
    int n, m;
    cin >> n >> m;
    vvi adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for (auto &v : adj) sort(all(v));
    auto hash = [&](vi &a, int k) {
        ll res = 0;
        for (int i = 0; i < a.size(); ++i) {
            res = (res + (a[i] + 1) * p[a[i] + 1][k]) % M[k];
        }
        return res;
    };
    vector<array<ll, 2>> h(n);
    vector<map<pll, ll>> b(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            h[i][j] = hash(adj[i], j);
        }
        ++b[adj[i].size()][{h[i][0], h[i][1]}];
    }
    ll ans = 0;
    for (int u = 0; u < n; ++u) {
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            array<ll, 2> h1 = h[u];
            array<ll, 2> h2 = h[v];
            for (int j = 0; j < 2; ++j) {
                h1[j] = ((h1[j] - (v + 1) * p[v + 1][j]) % M[j] + M[j]) % M[j];
                h2[j] = ((h2[j] - (u + 1) * p[u + 1][j]) % M[j] + M[j]) % M[j];
            }
            ans += h1 == h2;
        }
    }
    ans /= 2;
    for (int i = 0; i < n; ++i) {
        for (auto &[k, v] : b[i]) ans += v * (v - 1) / 2;
    }
    cout << ans;
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