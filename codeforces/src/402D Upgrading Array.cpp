//
// Created by Psy.C on 2026/1/31.
//
/**
* n：数组长度，m：特殊素数个数
a[N]：输入数组
st：存储特殊素数的集合
 *
*h：不属于特殊素数集合的质因数个数
b：属于特殊素数集合的质因数个数
 *
 */
#include <iostream>
#include <set>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5005
#define ii pair<int,int>
using namespace std;

int n, m, a[N];
set<int> st;
void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, x; i <= m; ++i) {
        cin >> x;
        st.insert(x);
    }
}

int gcd(const int aa, const int b) { return b == 0 ? aa : gcd(b, aa % b); }
int g[N];
void cal_g() {
    g[1] = a[1];
    //g[i] = gcd(a[1], a[2], ..., a[i])
    for (int i = 2; i <= n; ++i) g[i] = gcd(g[i-1], a[i]);
}

ii get(int x) {//分解x的质因数
    int h = 0, b = 0;
    for (int i = 2, t = static_cast<int>(sqrt(x)); i <= t; ++i) {
        int cnt = 0;
        while (x%i == 0) x /= i, ++cnt;
        if (cnt) {
            if (st.contains(i) > 0) b += cnt;
            else h += cnt;
        }
    }
    if (x != 1) { if (st.contains(x)) b++; else h++; }
    return {h, b};
}

bool ok(const int x) {//x的普通质因数个数是否小于特殊质因数个数
    auto [fst, snd] = get(x);
    return fst < snd;
}

void cal_a() {
    int d = 1;
    for (int i = n; i >= 1; --i) {
        if (ok(g[i]/d)) d = g[i];
        a[i] /= d;
    }
}

int out() {//每个元素的普通质因数个数减去特殊质因数个数的总和
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        auto [fst, snd] = get(a[i]);
        ans += fst - snd;
    }
    return ans;
}


int main() {
    fast;
    init(); cal_g(); cal_a();
    cout << out() << '\n';
    return 0;
}