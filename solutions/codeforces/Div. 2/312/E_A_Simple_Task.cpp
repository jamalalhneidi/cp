/*

A Simple Task

https://codeforces.com/contest/558/problem/E

segment tree (lazy propagation - range assignment)

*2300


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

struct ST {
    int n, h;
    int *t, *d;

    ST(int n, string &s, char c) {
        this->n = n;
        h = 32 - countl_zero(unsigned(n));
        t = new int[2 * n]{0};
        d = new int[n];
        fill(d, d + n, -1);
        for (int i = 0; i < n; ++i) {
            t[i + n] = s[i] == c;
        }
        for (int i = n - 1; i; --i) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    void apply(int i, int x, int k) {
        t[i] = x * k;
        if (i < n) d[i] = x;
    }

    void calc(int i, int k) {
        if (d[i] == -1)
            t[i] = t[i << 1] + t[i << 1 | 1];
        else
            t[i] = d[i] * k;
    }

    void push(int l, int r) {
        int j = h, k = 1 << (h - 1);
        for (l += n, r += n; j; --j, k >>= 1) {
            for (int i = l >> j; i <= r >> j; ++i) {
                if (d[i] != -1) {
                    apply(i << 1, d[i], k);
                    apply(i << 1 | 1, d[i], k);
                    d[i] = -1;
                }
            }
        }
    }

    void build(int l, int r) {
        int k = 2;
        for (l += n, r += n; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = l; i <= r; ++i) {
                calc(i, k);
            }
        }
    }

    void update(int l, int r, int x) {
        push(l, l);
        push(r, r);
        int l0 = l, r0 = r, k = 1;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) apply(l++, x, k);
            if (r & 1) apply(--r, x, k);
        }
        build(l0, l0);
        build(r0, r0);
    }

    int query(int l, int r) {
        push(l, l);
        push(r, r);
        int res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<ST> st;
    for (int i = 0; i < 26; ++i) {
        st.pb(ST(n, s, i + 'a'));
    }
    while (q--) {
        int l, r, t;
        cin >> l >> r >> t;
        --l, --r;
        vi cnt(26);
        for (int i = 0; i < 26; ++i) {
            int x = st[i].query(l, r);
            cnt[i] = x;
            st[i].update(l, r, 0);
        }
        for (int i = t ? 0 : 25; t ? i < 26 : i >= 0; t ? ++i : --i) {
            if (!cnt[i]) continue;
            st[i].update(l, l + cnt[i] - 1, 1);
            l += cnt[i];
        }
    }
    for (int i = 0; i < 26; ++i) {
        st[i].push(0, n - 1);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (st[j].t[i + n]) cout << char(j + 'a');
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