struct Trie {
    struct N {
        char key;
        bool end;
        N *l, *m, *r;
        bool isErasable() {
            return !end && !l && !m && !r;
        }
    };
    int sz = 0;
    N *root = 0;
    void insert(const string &s) {
        insert(root, 0, s);
    }
    void insert(N *&u, int i, const string &s) {
        if (!u) u = new N{s[i]};
        if (s[i] < u->key) return insert(u->l, i, s);
        if (s[i] > u->key) return insert(u->r, i, s);
        if (i < s.length() - 1) return insert(u->m, i + 1, s);
        sz += !u->end;
        u->end = true;
    }
    void erase(const string &s) {
        erase(root, 0, s);
    }
    void erase(N *&u, int i, const string &s) {
        if (!u) return;
        if (s[i] < u->key)
            erase(u->l, i, s);
        else if (s[i] > u->key)
            erase(u->r, i, s);
        else if (i < s.length() - 1)
            erase(u->m, i + 1, s);
        else {
            sz -= u->end;
            u->end = false;
        }
        if (u->isErasable()) {
            delete u;
            u = 0;
        }
    }
    int size() {
        return sz;
    }
};
