struct UF {
   private:
    vi p, size;
    int cc;

   public:
    UF(int n) {
        p = vi(n);
        size = vi(n, 1);
        iota(all(p), 0);
        cc = n;
    }

    int find(int u) {
        return p[u] == u ? u : p[u] = find(p[u]);
    }

    bool join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (size[u] < size[v]) swap(u, v);
        p[v] = u;
        size[u] += size[v];
        --cc;
        return true;
    }

    bool connected(int u, int v) {
        return find(u) == find(v);
    }

    int getSize(int u) {
        return size[find(u)];
    }

    int getCC() const {
        return cc;
    }
};