//  10099 - The Tourist Guide
// Bellman-Ford variation

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

struct E {
    int u, v, w;
};

void solve(int n, int m) {
    vector<E> edges(2 * m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        edges[i] = {u, v, w};
        edges[i + m] = {v, u, w};
    }
    int s, t, k;
    cin >> s >> t >> k;
    --s, --t;
    vi d(n, NINF);
    d[s] = k;
    for (int i = 0; i < n; ++i) {
        for (auto [u, v, w]: edges) {
            d[v] = max(d[v], min(d[u], w));
        }
    }
    cout << ceil(k, d[t] - 1) << endl;
}

int main() {
    fast;
    int n;
    int t = 1;
    while (cin >> n && n) {
        int m;
        cin >> m;
        cout << "Scenario #" << t++ << endl;
        cout << "Minimum Number of Trips = ";
        solve(n, m);
        cout << endl;
    }
}
/*



 */
