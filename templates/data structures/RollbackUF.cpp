struct RollbackUF {
   private:
    vector<int> data;
    stack<pair<int, int>> history;
    int cc;

    void snapshot(int u, int v) {
        history.emplace(u, data[u]);
        history.emplace(v, data[v]);
        history.emplace(-1, cc);
    }

   public:
    RollbackUF(int n) {
        data.assign(n, -1);
        cc = n;
    }

    int find(int u) {
        return data[u] < 0 ? u : find(data[u]);
    }

    bool join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        snapshot(u, v);
        if (data[u] > data[v]) swap(u, v);
        data[u] += data[v];
        data[v] = u;
        --cc;
        return true;
    }

    bool connected(int u, int v) { return find(u) == find(v); }

    int getSize(int u) { return (-data[find(u)]); }

    int getCC() { return cc; }

    void undo() {
        cc = history.top().second;
        history.pop();
        data[history.top().first] = history.top().second;
        history.pop();
        data[history.top().first] = history.top().second;
        history.pop();
    }
};