template <class T = int>
struct FT2D {
    int n, m;
    vector<vector<T>> t;

    FT2D(int n, int m) {
        this->n = n + 1;
        this->m = m + 1;
        t.resize(n + 1, vector<T>(m + 1));
    }

    FT2D(vector<vector<T>> &a) : FT2D(a.size(), a.front().size()) {
        for (int i = 1; i <= a.size(); ++i) {
            for (int j = 1; j <= a.front().size(); ++j) {
                t[i][j] += a[i - 1][j - 1];
                int ii = i + (i & -i);
                int jj = j + (j & -j);
                if (ii < n + 1) t[ii][j] += t[i][j];
                if (jj < m + 1) t[i][jj] += t[i][j];
                if (ii < n + 1 && jj < m + 1) t[ii][jj] -= t[i][j];
            }
        }
    }

    void add(int x, int y, T v) {
        for (int i = x + 1; i < n; i += i & -i) {
            for (int j = y + 1; j < m; j += j & -j) {
                t[i][j] += v;
            }
        }
    }

    //          top left        bottom right
    int sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) + sum(x1 - 1, y1 - 1) -
               sum(x1 - 1, y2) - sum(x2, y1 - 1);
    }

    int sum(int x, int y) {
        T res = 0;
        for (int i = x + 1; i; i -= i & -i) {
            for (int j = y + 1; j; j -= j & -j) {
                res += t[i][j];
            }
        }
        return res;
    }
};
