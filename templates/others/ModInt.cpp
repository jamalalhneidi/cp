template<int MOD>
struct ModInt {
    int value;

    ModInt(long long v = 0) {
        value = v % MOD;
        if (value < 0) value += MOD;
    }

    ModInt &operator+=(ModInt const &b) {
        value += b.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    ModInt &operator-=(ModInt const &b) {
        value -= b.value;
        if (value < 0) value += MOD;
        return *this;
    }

    ModInt &operator*=(ModInt const &b) {
        value = (long long) value * b.value % MOD;
        return *this;
    }

    ModInt &operator/=(const ModInt &b) { return *this *= b.inv(); }

    friend ModInt operator+(ModInt a, ModInt const b) { return a += b; }

    friend ModInt operator-(ModInt a, ModInt const b) { return a -= b; }

    friend ModInt operator-(ModInt const a) { return 0 - a; }

    friend ModInt operator*(ModInt a, ModInt const b) { return a *= b; }

    friend ModInt operator/(ModInt a, ModInt const b) { return a /= b; }

    friend ostream &operator<<(std::ostream &os, ModInt const &a) { return os << a.value; }

    friend bool operator==(ModInt const &a, ModInt const &b) { return a.value == b.value; }

    friend bool operator!=(ModInt const &a, ModInt const &b) { return a.value != b.value; }

    ModInt &operator++() {
        *this += 1;
        return *this;
    }

    ModInt operator++(int) {
        ModInt old = *this;
        operator++();
        return old;
    }

    ModInt &operator--() {
        *this -= 1;
        return *this;
    }

    ModInt operator--(int) {
        ModInt old = *this;
        operator--();
        return old;
    }

    ModInt pow(long long e) const {
        if (e < 0) return inv().pow(-e);
        ModInt a = *this, res = 1;
        while (e) {
            if (e & 1) res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }

    ModInt inv() const { return pow(MOD - 2); }

};

const int MOD = 1e9 + 7;

typedef ModInt<MOD> mint;
typedef vector<mint> vmi;
typedef vector<vmi> vvmi;
