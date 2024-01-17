/*

Points

https://codeforces.com/contest/19/problem/D

segment tree

*2800

first 2800

Notes:
In the query function, calling both query(left) and query(right) would make it run in O(n)
(cuz we're querying till leaves)
Since we want the first element after ql that meets a condition,
we should only query the right side when we cannot find that element in the left side

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
        int mx = NINF, at = NINF;

        N operator+(N &that) {
            if (mx > that.mx) return {mx, at};
            return {that.mx, that.at};
        }
    };

    int n;
    N *t;

    ST(int n) {
        this->n = n;
        t = new N[n << 2];
    }

    void update(int at, int mx, int i, int l, int r) {
        if (l > at || r < at) return;
        if (l == r) {
            t[i].mx = mx;
            t[i].at = l;
            return;
        }
        int m = mid(l, r);
        update(at, mx, i << 1, l, m);
        update(at, mx, i << 1 | 1, m + 1, r);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }

    int query(int ql, int qr, int y, int i, int l, int r) {
        if (l > qr || r < ql || t[i].mx <= y) return INF;
        if (l == r) return t[i].at;
        int m = mid(l, r);
        int res = query(ql, qr, y, i << 1, l, m);
        if (res != INF) return res;
        return query(ql, qr, y, i << 1 | 1, m + 1, r);
    }
};

void solve() {
    int n;
    cin >> n;
    array<int, 3> a[n];
    mii mx, rx;
    for (int i = 0; i < n; ++i) {
        string s;
        int x, y;
        cin >> s >> x >> y;
        int t;
        if (s[0] == 'a')
            t = 1;
        else if (s[0] == 'r')
            t = 2;
        else
            t = 3;
        a[i] = {t, x, y};
        mx[x];
    }
    int idx = 0;
    for (auto &[k, v] : mx) v = idx++, rx[v] = k;
    for (auto &[t, x, y] : a) x = mx[x];
    ST st(idx);
    si s[idx];
    for (auto &[t, x, y] : a) {
        if (t == 1) {
            int mx = s[x].empty() ? NINF : *s[x].rbegin();
            s[x].insert(y);
            if (mx == *s[x].rbegin()) continue;
            mx = *s[x].rbegin();
            st.update(x, mx, 1, 0, idx - 1);
        } else if (t == 2) {
            int mx = *s[x].rbegin();
            s[x].erase(y);
            if (!s[x].empty() && mx == *s[x].rbegin()) continue;
            mx = s[x].empty() ? NINF : *s[x].rbegin();
            st.update(x, mx, 1, 0, idx - 1);
        } else {
            int ansx = st.query(x + 1, idx - 1, y, 1, 0, idx - 1);
            if (ansx == INF)
                cout << -1 << endl;
            else
                cout << rx[ansx] << spc << *s[ansx].upper_bound(y) << endl;
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