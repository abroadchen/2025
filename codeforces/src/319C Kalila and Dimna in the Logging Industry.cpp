//
// Created by Psy.C on 2026/1/7.
//
/**
* 第一个while: 寻找最优决策点，当队首元素的斜率大于-a[i]时出队
状态转移: d[i] = d[q[h]] + b[q[h]] * a[i]，使用最优决策点计算当前状态
第二个while: 维护凸包性质，移除无用决策点
将当前索引加入队列
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2000005
using namespace std;

ll d[N]; int b[N];
double calc(const int j, const int k) {
    return static_cast<double>(d[j] - d[k]) / (b[j] - b[k]);
}

int a[N], q[N];
void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    int h = 0, t = -1; d[1] = 0; q[++t] = 1;
    for (int i = 2; i <= n; ++i) {
        while (h < t && calc(q[h], q[h + 1]) > -a[i]) ++h;
        d[i] = d[q[h]] + 1ll * b[q[h]] * a[i];
        while (h < t && calc(i, q[t-1]) < calc(i, q[t])) --t;
        q[++t] = i;
    }
    cout << d[n] << '\n';
}


int main() {
    fast; solve();
    return 0;
}