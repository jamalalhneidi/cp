template <class T = int>
struct FT {
    int n;
    vector<T> t;

    FT(int n) {
        this->n = n + 1;
        t.resize(n + 1);
    }

    FT(vector<T> &a) : FT(a.size()) {
        for (int i = 1; i <= a.size(); ++i) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j < n + 1) t[j] += t[i];
        }
    }

    void add(int i, T x) {
        for (++i; i < n; i += i & -i) t[i] += x;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    int sum(int i) {
        T res = 0;
        for (++i; i; i -= i & -i) res += t[i];
        return res;
    }
};
