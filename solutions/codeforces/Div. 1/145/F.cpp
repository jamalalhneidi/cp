/*

TorCoder

https://codeforces.com/contest/240/problem/F

segment tree (lazy propagation - range assignment)

*2600


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
    vi t, d;

    ST(int n, string &s, char c) {
        this->n = n;
        h = 32 - countl_zero(unsigned(n));
        t.resize(2 * n);
        d.resize(n, -1);
        for (int i = 0; i < n; ++i) {
            t[i + n] = s[i] == c;
        }
        for (int i = n - 1; i; --i) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    void calc(int i, int k) {
        if (d[i] == -1)
            t[i] = t[i << 1] + t[i << 1 | 1];
        else
            t[i] = d[i] * k;
    }

    void apply(int i, int x, int k) {
        t[i] = x * k;
        if (i < n) d[i] = x;
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
        if (l > r) return;
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
        int l, r;
        cin >> l >> r;
        --l, --r;
        vi cnt(26);
        int odd = 0;
        for (int i = 0; i < 26; ++i) {
            cnt[i] = st[i].query(l, r);
            odd += cnt[i] % 2;
        }
        if ((len(l, r) % 2 && odd > 1) || (len(l, r) % 2 == 0 && odd)) continue;
        int l0 = l, r0 = r;
        for (int i = 0; i < 26; ++i) {
            if (!cnt[i]) continue;
            st[i].update(l0, r0, 0);
            int h = cnt[i] / 2;
            st[i].update(l, l + h - 1, 1);
            st[i].update(r - h + 1, r, 1);
            if (cnt[i] % 2) st[i].update(mid(l, r), mid(l, r), 1);
            l += h, r -= h;
        }
    }
    for (int i = 0; i < 26; ++i) {
        st[i].push(0, n - 1);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (st[j].query(i, i)) cout << char(j + 'a');
        }
    }
}

int main() {
    fast;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
