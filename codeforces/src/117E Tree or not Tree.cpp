//
// Created by Psy.C on 2025/11/15.
//

#include <vector>
#include <iostream>
using namespace std;

static constexpr uint_fast32_t N = 100'000;
static vector<vector<uint_fast32_t>> g;
static uint_fast32_t i[1 + N] = {}, p[1 + N] = {},
r[1 + N] = {}, c = 0, q[1 + N] = {}, t = 0, o[1 + N], k, s = 0;
static bool e[1 + N] = {};

static uint_fast32_t find(const uint_fast32_t v=1, const uint_fast32_t z=0) noexcept {
    i[v] = true;
    for (const uint_fast32_t w : g[v]) {
        if (w == z) continue;
        p[w] = v;
        if (i[w]) return w;
        if (const uint_fast32_t h = find(w, v)) return h;
    }
    return 0;
}

static void trav(const uint_fast32_t v, const uint_fast32_t j) noexcept {
    i[v] = t++;
    for (const uint_fast32_t w : g[v]) {
        if (r[w]) continue;
        r[w] = j;
        p[w] = v;
        trav(w, j);
    }
    o[v] = t++;
}


static inline void preprocess() {
    const auto cycle = [h = find()](const auto& f) noexcept {
        uint_fast32_t y = h;
        do {
            f(y);
            y = p[y];
        } while (y != h);
    };
    cycle([](const uint_fast32_t y) noexcept {
        r[y] = 1 + c++;
        q[p[y]] = y;
    });
    cycle([](const uint_fast32_t y) noexcept {
        trav(y, r[y]);
    });
    k = g.size() - 1;
}

template<typename T>
static inline void move(uint_fast32_t& w, const T& x) noexcept {
    for (; !x(); w = p[w]) {
        if ((e[w] = !e[w])) k--;
        else k++;
    }
}

static inline void change(uint_fast32_t v, uint_fast32_t u) noexcept {
    if (r[v] == r[u]) {
        move(v, [&v, &u]() noexcept { return i[v] <= i[u] && o[u] <= o[v]; });
        move(u, [&v, &u]() noexcept { return i[u] <= i[v] && o[v] <= o[u]; });
        return;
    }
    move(v, [&v]() noexcept { return q[v]; });
    move(u, [&u]() noexcept { return q[u]; });
    {
        const auto move_around = [&v, u](const uint_fast32_t (&d)[1 + N], const auto& f) noexcept {
            for (; v != u; v = d[v]) {
                const uint_fast32_t w = f(v);
                if ((e[w] = !e[w])) {
                    s++;
                    if (s < c) k--;
                } else {
                    if (s < c) k++;
                    s--;
                }
            }
        };
        if ((r[u] + c - r[v]) % c < (r[v] + c - r[u]) % c) goto p;
        if ((r[u] + c - r[v]) % c > (r[v] + c - r[u]) % c) goto q;
        if (p[v] < q[v])
            p: move_around(p, [](const uint_fast32_t v) noexcept { return v; });
        else
            q: move_around(q, [](const uint_fast32_t v) noexcept { return q[v]; });
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    uint_fast32_t n, m; cin >> n >> m;
    g.resize(n + 1);
    for (; n; --n) {
        uint_fast32_t a, b; cin >> a >> b;
        g[a].push_back(b); g[b].push_back(a);
    }
    preprocess();
    for (; m; --m) {
        uint_fast32_t v, u; cin >> v >> u;
        change(v, u);
        cout << k << '\n';
    }
    return 0;
}