template <class T = int>
struct Matrix {
    T a[2][2];
    Matrix operator*(Matrix &that) {
        Matrix res{{{0, 0}, {0, 0}}};
        for (int k = 0; k < 2; ++k) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    res.a[i][j] += a[i][k] * that.a[k][j];
                }
            }
        }
        return res;
    }
    Matrix pow(ll n) {
        Matrix a = *this;
        Matrix res{{{1, 0}, {0, 1}}};
        while (n) {
            if (n & 1) res = res * a;
            a = a * a;
            n >>= 1;
        }
        return res;
    }
};
