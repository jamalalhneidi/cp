/*

KQUERY - K-query

https://www.spoj.com/problems/KQUERY/

persistent segment tree

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

struct PST {
    struct N {
        N *l = 0, *r = 0;
        int s = 0;

        N(int s) {
            this->s = s;
        }

        N(N *l, N *r) : l(l), r(r) {
            if (l) s += l->s;
            if (r) s += r->s;
        }
    };

    int n;
    vector<N *> roots;

    PST(int n, vi &a) {
        this->n = n;
        roots.pb(build(0, n - 1));
        for (auto x : a) {
            roots.pb(update(roots.back(), 0, n - 1, x));
        }
    }

    N *build(int l, int r) {
        if (l == r) return new N(0);
        int m = mid(l, r);
        return new N(build(l, m), build(m + 1, r));
    }

    N *update(N *n, int l, int r, int x) {
        if (l == r) return new N(n->s + 1);
        int m = mid(l, r);
        if (x <= m)
            return new N(update(n->l, l, m, x), n->r);
        else
            return new N(n->l, update(n->r, m + 1, r, x));
    }

    int query(int l, int r, int x) {
        return query(roots[l], roots[r + 1], x + 1, n - 1, 0, n - 1);
    }

    int query(N *nl, N *nr, int ql, int qr, int l, int r) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return nr->s - nl->s;
        int m = mid(l, r);
        return query(nl->l, nr->l, ql, qr, l, m) + query(nl->r, nr->r, ql, qr, m + 1, r);
    }
};

void solve() {
    int n;
    cin >> n;
    vi a(n);
    mii m;
    cin(a), m[_x];
    int q;
    cin >> q;
    vector<array<int, 3>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin(queries[i]);
        m[queries[i][2]];
        queries[i][0]--;
        queries[i][1]--;
    }
    int id = 0;
    for (auto &[k, v] : m) v = id++;
    for (auto &x : a) x = m[x];
    PST pst(id, a);
    for (auto [l, r, k] : queries) {
        k = m[k];
        cout << pst.query(l, r, k) << endl;
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