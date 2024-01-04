/*

Lucky Queries

https://codeforces.com/contest/145/problem/E

segment tree (lazy propagation)

*2400



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

struct Node {
    int ans[2]{0}, c[2][2]{0};
    bool state = false;

    Node() {}

    Node(int v) {
        c[state][v]++;
        c[!state][!v]++;
        ans[0] = ans[1] = 1;
    }

    Node operator+(Node &that) {
        Node res;
        for (int i = 0; i < 2; ++i) {
            res.ans[res.state ^ i] = max(c[state ^ i][0] + that.ans[that.state ^ i],
                                         ans[state ^ i] + that.c[that.state ^ i][1]);
            for (int j = 0; j < 2; ++j) {
                res.c[res.state ^ i][j] = c[state ^ i][j] + that.c[that.state ^ i][j];
            }
        }
        return res;
    }

    Node operator^(int x) {
        state ^= x;
        return *this;
    }

    Node operator^=(int x) {
        return *this ^ x;
    }
};

struct ST {
    int n, h;
    vector<Node> t;
    vi d;

    ST(int n, vi &a) {
        this->n = n;
        h = 32 - countl_zero(unsigned(n));
        t.resize(2 * n);
        d.resize(n);
        for (int i = 0; i < n; ++i) {
            t[i + n] = {a[i]};
        }
        for (int i = n - 1; i; --i) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    void apply(int i) {
        t[i] ^= 1;
        if (i < n) d[i] ^= 1;
    }

    void push(int p) {
        for (int j = h; j; --j) {
            int i = p >> j;
            if (d[i]) {
                apply(i << 1);
                apply(i << 1 | 1);
                d[i] = 0;
            }
        }
    }

    void build(int i) {
        for (i >>= 1; i; i >>= 1) {
            t[i] = (t[i << 1] + t[i << 1 | 1]) ^ d[i];
        }
    }

    void update(int l, int r) {
        l += n, r += n + 1;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++);
            if (r & 1) apply(--r);
        }
        build(l0);
        build(r0 - 1);
    }

    int query(int l, int r) {
        l += n, r += n + 1;
        push(l);
        push(r - 1);
        Node resl, resr;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + t[l++];
            if (r & 1) resr = t[--r] + resr;
        }
        Node res = resl + resr;
        return res.ans[res.state];
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        a[i] = c == '7';
    }
    ST st(n, a);
    while (q--) {
        string s;
        cin >> s;
        if (s == "count") {
            cout << st.query(0, n - 1) << endl;
        } else {
            int l, r;
            cin >> l >> r;
            st.update(l - 1, r - 1);
        }
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