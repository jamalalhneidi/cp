const int _MAX = 2e5 + 1;
int idx = 0;
struct N {
    int l, r, s;
} nodes[22 * _MAX];
int create(int s) {
    nodes[idx].s = s;
    return idx++;
}
int merge(int l, int r) {
    nodes[idx].l = l;
    nodes[idx].r = r;
    nodes[idx].s = 0;
    if (l != -1) nodes[idx].s += nodes[l].s;
    if (r != -1) nodes[idx].s += nodes[r].s;
    return idx++;
}
struct PST {
    int n;
    int *roots;
    PST(int n, vi &a) {
        this->n = n;
        roots = new int[a.size() + 1];
        roots[0] = build(0, n - 1);
        for (int i = 0; i < a.size(); ++i) {
            roots[i + 1] = update(roots[i], 0, n - 1, a[i]);
        }
    }
    int build(int l, int r) {
        if (l == r) return create(0);
        int m = mid(l, r);
        return merge(build(l, m), build(m + 1, r));
    }
    int update(int n, int l, int r, int at) {
        if (l == r) return create(nodes[n].s + 1);
        int m = mid(l, r);
        if (at <= m) return merge(update(nodes[n].l, l, m, at), nodes[n].r);
        return merge(nodes[n].l, update(nodes[n].r, m + 1, r, at));
    }
    int query(int l, int r, int x) {
        return query(roots[l], roots[r + 1], x, n - 1, 0, n - 1);
    }
    int query(int nl, int nr, int ql, int qr, int l, int r) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return nodes[nr].s - nodes[nl].s;
        int m = mid(l, r);
        return query(nodes[nl].l, nodes[nr].l, ql, qr, l, m) +
               query(nodes[nl].r, nodes[nr].r, ql, qr, m + 1, r);
    }
};
