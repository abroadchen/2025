//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
n /= 2：实际输入是 2n 个数（后半段题目会用来判断合理性），这里只读前 n 个作为 a[i]。
对每个 a[i]，枚举其较小因子 j（j < sqrt），记录对应的大因子 a[i]/j 到 v[i]，再升序排序
利用恒等式 a[i] = x*y = p² - q²（其中 p=(x+y)/2, q=(x-y)/2）：

(x+y) 必须为偶数才让 p,q 是整数。
要让整个序列严格递增，需要 q > now（全局单调约束，now 记录上一步的 p）。
找到一个合法的 (p,q) 后，算出本项差分 ans[i] = q² - now²，更新 now=p，跳出
只要有一项无法构造 → No。
全部可行 → Yes，依次输出 ans[i] 和 a[i]（即还原序列的相邻两项）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

int n, a[N], now;
vector<int> v[N];
ll ans[N];
int main() {
    fast;
    cin >> n; n /= 2;
    rep(i,n) {
        cin >> a[i];
        for (int j = 1; j < sqrt(a[i]); j++)
            if (a[i]%j == 0) v[i].push_back(a[i]/j);
        ranges::sort(v[i]);
    }
    bool f = 1;
    rep(i,n) {
        rep(j,v[i].size()) {
            int x = v[i][j], y = a[i]/x;
            if ((x+y)%2) continue;
            int p = (x+y)/2, q = (x-y)/2;
            if (q <= now) continue;
            ans[i] = 1ll * q * q - 1ll * now * now;
            now = p;
            break;
        }
        if (ans[i] == 0) f = 0;
        if (!f) break;
    }
    if (!f) cout << "No\n";
    else {
        cout << "Yes\n";
        rep(i,n) cout << ans[i] << ' ' << a[i] << ' ';
    }
    return 0;
}