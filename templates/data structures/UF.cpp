struct UF {
    vi p, size;
    int cc;

    UF(int n) {
        p = vi(n);
        size = vi(n, 1);
        iota(all(p), 0);
        cc = n;
    }

    int find(int u) {
        return p[u] == u ? u : p[u] = find(p[u]);
    }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)return;
        if (size[u] < size[v])swap(u, v);
        p[v] = u;
        size[u] += size[v];
        --cc;
    }

    int getSize(int u) {
        return size[find(u)];
    }

    int getComponents() const {
        return cc;
    }

};
