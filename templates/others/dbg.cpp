#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> vec_splitter(string s) {
    s = ' ' + s + ',';
    vector<string> res;
    while (!s.empty()) {
        auto open = s.find('(');
        auto comma = s.find(',');
        string::size_type split;
        if (open > comma)
            split = comma;
        else {
            int x = 0;
            int i;
            for (i = 0; i < s.length(); ++i) {
                if (s[i] == '(')
                    ++x;
                else if (s[i] == ')')
                    --x;
                else if (s[i] == ',' && !x)
                    break;
            }
            split = i;
        }
        res.push_back(s.substr(0, split));
        s = s.substr(split + 1);
    }
    return res;
}

template<class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
    return os << '{' << p.first << ", " << p.second << '}';
}

template<class T, class = decay_t<decltype(*begin(declval<T>()))>,
        class = enable_if_t<!is_same<T, string>::value>>
ostream &operator<<(ostream &os, const T &c) {
    os << '[';
    for (auto it = c.begin(); it != c.end(); ++it)
        os << &", "[2 * (it == c.begin())] << *it;
    return os << ']';
}

void debug_out(
        const vector<string> __attribute__((unused)) &args,
        __attribute__((unused)) int idx,
        __attribute__((unused)) int LINE_NUM,
        __attribute__((unused)) bool ln) { cerr << endl; }

template<typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, bool ln, Head H, Tail... T) {
    cerr << "\033[92m";
    if (!ln && idx)
        cerr << ", ";
    else {
        if (idx) cerr << endl;
        cerr << "Line " << LINE_NUM << ":";
    }
    stringstream ss;
    ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, ln, T...);
}

#define dbg(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, false, __VA_ARGS__)
#define dbgln(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, true, __VA_ARGS__)
