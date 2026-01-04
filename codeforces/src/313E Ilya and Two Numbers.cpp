#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 100005
using namespace std;

struct Bitset {
    const int w = 64;
    int len;
    typedef unsigned long long ull;
    vector<ull> v;

    explicit Bitset(const int len) : len(len) {
        v.resize((len + w - 1) / w, 0);
    }
    void set(const int pos) {
        v[pos / w] |= 1ull << (pos & w - 1);
    }
    void unset(const int pos) {
        v[pos / w] &= ~(1ull << (pos & w - 1));
    }
    void shift() {
        if (len == 0) return;
        const int b = v[0] & 1;
        for (int i = 0; i < v.size(); ++i) {
            if (i + 1 < v.size()) {
                v[i] >>= 1;
                v[i] |= (v[i + 1] & 1) << (w - 1);
            } else {
                v[i] >>= 1;
                if (b) v[i] |= 1ull << (w - 1);
            }
        }
        if (len % w != 0) {
            const int idx = (len - 1) / w;
            const ull mask = (1ull << (len % w)) - 1;
            v[idx] &= mask;
        }
    }
    void join(const Bitset& o) {
        assert(len == o.len);
        for (int i = 0; i < v.size(); ++i) v[i] |= o.v[i];
    }
    int find(const int bgn) const {
        if (bgn >= len) return -1;
        int wi = bgn / w;
        int bi = bgn & (w - 1);
        const ull mask = ~((1ull<<bi) - 1);
        ull x = v[wi] & mask;
        while (wi < v.size()) {
            if (v[wi] != 0) {
                x = v[wi];
                if (wi == bgn / w) { x &= ~((1ull<bi) - 1); }
                if (x != 0) {
                    const int offset = __builtin_ctzll(x);
                    const int pos = wi * w + offset;
                    return pos < len ? pos : -1;
                }
            }
            wi++;
            bi = 0;
        }
        return -1;
    }
};


int main() {
    fast;
    int n, m, a[2][N]; cin >> n >> m;
    for (int k = 0; k < 2; ++k) {
        for (int i = 1, x; i <= n; ++i) {
            cin >> x;
            a[k][x]++;
        }
    }
    Bitset x(m), y(m);
    for (int i = 0; i < m; ++i) if (a[0][i]) x.set(i);
    for (int i = 0; i < m; ++i) if (a[1][i]) y.set(m - 1 - i);
    for (int v = m - 1, idx = 0, idx2, t; v >= 0; --v) {
        Bitset z = x; z.join(y); idx = 0;
        while (true) {
            idx = z.find(idx);
            if (idx < 0) break;
            idx2 = (v - idx + m) % m; t = min(a[0][idx], a[1][idx2]);
            for (int i = 1; i <= t; ++i) cout << v << ' ';
            if ((a[0][idx] -= t) == 0) x.unset(idx);
            if ((a[1][idx2] -= t) == 0) y.unset(m - 1 - idx2);
            idx++;
        }
        y.shift();
    }
    cout << '\n';
    return 0;
}