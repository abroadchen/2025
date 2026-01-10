//
// Created by Psy.C on 2026/1/10.
//
/**
 * 函数返回一个 MInt 的引用。这样可以实现链式操作，如 a *= b *= c
 * 参数列表后的 &
 * 对象的引用限定符（reference qualifier），它指定这个成员函数只能被左值（lvalue）调用
 *  & - 左值限定：只能被左值调用
    && - 右值限定：只能被右值调用
 * friend 关键字的使用是为了让全局的 operator* 函数能够访问 MInt 类的私有成员（private 或 protected 成员）
 * [[nodiscard]] 告诉编译器该函数的返回值不应该被忽略
 * explicit 用于防止意外的隐式类型转换

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}

    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
i64 MLong<0LL>::Mod = 1;
 */
#include <iostream>
#include <vector>
#include <cassert>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (int i=0; i<n; ++i)
using namespace std;

template<class T>
T pw(T a, ll b) {
    T res = 1;
    for (; b; b>>=1, a*=a) if (b&1) res*=a;
    return res;
}


template<int P>
struct MInt {
    int x;
    MInt() : x{} {}
    explicit MInt(const ll x) : x{norm(x%get())} {}
    static int mod;

    static int get() {
        if (P > 0) return P;
        return mod;
    }

    static void set(const int m) { mod = m; }
    [[nodiscard]] static constexpr int norm(int x) {
        if (x < 0) x += get();
        if (x >= get()) x -= get();
        return x;
    }
    [[nodiscard]] int val() const { return x; }
    explicit operator int() const { return x; }//从当前类到 int 的转换  常量成员函数，不会修改对象
    MInt operator-() const { MInt res; res.x = norm(get() - x); return res; }
    [[nodiscard]] MInt inv() const { assert(x != 0); return pw(*this, get()-2); }
    MInt& operator=(const int val) { x = norm(val%get()); return *this; }
    MInt& operator*=(MInt rhs) & { x = 1ll * x * rhs.x % get(); return *this; }
    MInt& operator+=(MInt rhs) & { x = norm(x + rhs.x); return *this; }
    MInt& operator-=(MInt rhs) & { x = norm(x - rhs.x); return *this; }
    MInt& operator/=(const MInt rhs) & { return *this *= rhs.inv(); }
    friend MInt operator*(const MInt lhs, MInt rhs) { MInt res = lhs; res *= rhs; return res; }
    friend MInt operator+(const MInt lhs, MInt rhs) { MInt res = lhs; res += rhs; return res; }
    friend MInt operator-(const MInt lhs, MInt rhs) { MInt res = lhs; res -= rhs; return res; }
    friend MInt operator/(const MInt lhs, MInt rhs) { MInt res = lhs; res /= rhs; return res; }
    friend istream& operator>>(istream& is, MInt& res) { ll v; is >> v; res = MInt(v); return is; }
    friend ostream& operator<<(ostream& os, const MInt& res) { return os << res.val(); }
    friend bool operator==(const MInt lhs, const MInt rhs) { return lhs.val() == rhs.val(); }
    friend bool operator!=(const MInt lhs, const MInt rhs) { return lhs.val() != rhs.val(); }
};

template<>
int MInt<0>::mod = 1;

constexpr int P = 1000000007;
using Z = MInt<P>;



int main() {
    fast;
    int n, m; cin >> n >> m;
    vector e(n, vector(n, false));
    vector v(n, vector(n, vector<int>()));
    for (int i = 0, x, y, k; i < m; ++i) {
        cin >> x >> y; x--, y--; e[x][y] = true;
        cin >> k; v[x][y].resize(k);
        rep(j,k) cin >> v[x][y][j], v[x][y][j]--;
    }
    vector<tuple<int,int,int>> f[2][2];
    rep(x,n) rep(y,n) if (e[x][y]) rep(i,v[x][y].size()+1) {
        if ((!i || v[x][y][i-1]==x) && (i==v[x][y].size() || v[x][y][i]==y)) {
            vector<int> l, r; l.assign(v[x][y].rend()-i, v[x][y].rend());
            if (!l.empty()) {
                bool ok = true;
                for (int j = 0; j+1<l.size() && l.size() <= 2*n+1; ++j) {
                    if (!e[l[j+1]][l[j]]) { ok = false; break; }
                    auto& f = v[l[j+1]][l[j]];
                    l.insert(l.end(), f.rbegin(), f.rend());
                }
                if (!ok || l.size() > 2*n+1) break;
            }
            r.assign(v[x][y].begin()+i, v[x][y].end());
            if (!r.empty()) {
                bool ok = true;
                for (int j = 0; j+1<r.size() && r.size() <= 2*n+1; ++j) {
                    if (!e[r[j]][r[j+1]]) { ok = false; break; }
                    auto& f = v[r[j]][r[j+1]];
                    r.insert(r.end(), f.begin(), f.end());
                }
                if (!ok || r.size() > 2*n+1) break;
            }
            f[!l.empty()][!r.empty()].emplace_back(l.empty() ? x : l.back(),
                r.empty() ? y : r.back(), l.size() + r.size());
        }
    }
    vector dp(2*n+2, vector(n, array<Z, 2>{}));
    rep(i,n) dp[0][i][0] = 1;
    vector<Z> ans(2*n+2);
    rep(i,2*n+2) {
        rep(u,2) rep(v,2) for (auto [x,y,l] : f[u][v]) {
            if (i + l <= 2*n+1) dp[i+l][y][v] += dp[i][x][!u];
        }
        rep(x,n) ans[i] += dp[i][x][1];
    }
    for (int i = 2; i <= 2*n+1; ++i) cout << ans[i] << '\n';
    return 0;
}