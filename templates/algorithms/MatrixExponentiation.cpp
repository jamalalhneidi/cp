template <class T = int, int N = 2>
struct Matrix {
    T a[N][N];
    Matrix operator*(Matrix &that) {
        Matrix<T, N> res;
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    res.a[i][j] += a[i][k] * that.a[k][j];
                }
            }
        }
        return res;
    }
    Matrix pow(ll n) {
        Matrix<T, N> a = *this;
        Matrix<T, N> res;
        for (int i = 0; i < N; ++i) {
            res.a[i][i] = 1;
        }
        while (n) {
            if (n & 1) res = res * a;
            a = a * a;
            n >>= 1;
        }
        return res;
    }
};
