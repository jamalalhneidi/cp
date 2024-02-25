const int HASH_CNT = 2;
static_assert(HASH_CNT <= 2);
typedef __int128 lll;
typedef array<lll, HASH_CNT> H;
const lll P[2] = {53, 59};
const lll M[2] = {984162944621615729, 984162944621615797};
H hsh(const string &s) {
    H res, p;
    for (int i = 0; i < HASH_CNT; ++i) res[i] = 0, p[i] = 1;
    for (auto c : s) {
        for (int i = 0; i < HASH_CNT; ++i) {
            res[i] += (c - 'a' + 1) * p[i] % M[i];
            p[i] = p[i] * P[i] % M[i];
        }
    }
    return res;
}
