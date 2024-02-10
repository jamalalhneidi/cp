struct ST {
    struct D {
        ll v = 0;
        D() {}
        D(ll v) : v(v) {}
        void reset() {
            v = 0;
        }
        // combine
        D operator+=(const D &x) {
            v += x.v;
            return *this;
        }
        // accumulating D over a segment of length x
        D operator*(const int x) {
            return {v * x};
        }
        // return true if nothing to propagate
        bool operator!() {
            return !v;
        }
    };

    struct T {
        ll v = 0;
        // combine
        T operator+(const T &that) const {
            return {v + that.v};
        }
        // combine with lazy
        T operator+=(const D &d) {
            v += d.v;
            return *this;
        }
        // the final useful piece of info we're interested in
        // make sure the return type matches the actual type of the returned value
        ll res() {
            return v;
        }
    };

    int n, h;
    vector<T> t;
    vector<D> d;
    vi ln;

    ST(int n) {
        this->n = n;
        this->h = 31 - countl_zero(unsigned(n));
        t.resize(n << 1);
        ln.resize(n << 1);
        d.resize(n);
        for (int i = 0; i < n; ++i) ln[i + n] = 1;
        for (int i = n - 1; i; --i) ln[i] = ln[i << 1] + ln[i << 1 | 1];
    }
    ST(vi &a) : ST(a.size()) {
        for (int i = 0; i < n; ++i) t[i + n] = T(a[i]);
        for (int i = n - 1; i; --i) calc(i);
    }
    void update(int l, int r, D x) {
        l += n, r += n + 1;
        int l0 = l, r0 = r;
        push(l, r);
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, x);
            if (r & 1) apply(--r, x);
        }
        pull(l0, r0);
    }
    T query(int l, int r) {
        l += n, r += n + 1;
        push(l, r);
        T resl, resr;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + t[l++];
            if (r & 1) resr = t[--r] + resr;
        }
        return resl + resr;
    }

   private:
    void calc(int i) {
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void apply(int i, D x) {
        t[i] += x * ln[i];
        if (i < n) d[i] += x;
    }
    void push(int i) {
        if (!d[i]) return;
        apply(i << 1, d[i]);
        apply(i << 1 | 1, d[i]);
        d[i].reset();
    }
    void push(int l, int r) {
        for (int i = h; i; --i) {
            if (l >> i << i != l) push(l >> i);
            if (r >> i << i != r) push(r >> i);
        }
    }
    void pull(int l, int r) {
        for (int i = 1; i <= h; ++i) {
            if (l >> i << i != l) calc(l >> i);
            if (r >> i << i != r) calc(r >> i);
        }
    }
};
