/*

Alphabet Permutations

https://codeforces.com/contest/610/problem/E

segment tree (lazy propagation - recursive)

*2500

Tight ML

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
    struct N {
        char l, r;
        int cnt[10][10]{0};

        void reset() {
            memset(cnt, 0, sizeof cnt);
        }

        N operator+(N &that) {
            N res;
            res.l = l;
            res.r = that.r;
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    res.cnt[i][j] = cnt[i][j] + that.cnt[i][j];
                }
            }
            res.cnt[that.l - 'a'][r - 'a']++;
            return res;
        }
    };

    int n, k;
    vector<N> t;
    vector<char> d;

    ST(int n, string &s, int k) {
        this->n = n;
        this->k = k;
        t.resize(n << 2);
        d.resize(n << 2);
        build(1, 0, n - 1, s);
    }

    void build(int i, int l, int r, string &s) {
        if (l == r) {
            t[i].l = t[i].r = s[l];
            return;
        }
        int m = mid(l, r);
        build(i << 1, l, m, s);
        build(i << 1 | 1, m + 1, r, s);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }

    void apply(int i, char c, int l, int r) {
        t[i].reset();
        t[i].l = t[i].r = c;
        t[i].cnt[c - 'a'][c - 'a'] = r - l;
        d[i] = c;
    }

    void push(int i, int l, int r) {
        if (!d[i]) return;
        int m = mid(l, r);
        apply(i << 1, d[i], l, m);
        apply(i << 1 | 1, d[i], m + 1, r);
        d[i] = 0;
    }

    void update(int ql, int qr, char c, int i, int l, int r) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            apply(i, c, l, r);
            return;
        }
        push(i, l, r);
        int m = mid(l, r);
        update(ql, qr, c, i << 1, l, m);
        update(ql, qr, c, i << 1 | 1, m + 1, r);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
};

void solve() {
    int n, q, k;
    cin >> n >> q >> k;
    string s;
    cin >> s;
    ST st(n, s, k);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            char c;
            cin >> l >> r >> c;
            --l, --r;
            st.update(l, r, c, 1, 0, n - 1);
        } else {
            string t;
            cin >> t;
            int ans = 1;
            for (int i = 0; i < k; ++i) {
                for (int j = i; j < k; ++j) {
                    ans += st.t[1].cnt[t[i] - 'a'][t[j] - 'a'];
                }
            }
            cout << ans << endl;
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