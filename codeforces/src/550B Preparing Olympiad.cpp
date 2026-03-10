//
// Created by Psy.C on 2026/3/9.
//
/**
n：数组长度
l, r：和的范围 [l, r]
x：最大值与最小值差的最小值
mx, mn：当前选择元素的最大值和最小值
sum：当前选择元素的和
ans：满足条件的方案数
a[N]：输入数组
vis[N]：访问标记数组

遍历选择：从位置p开始，尝试选择未访问的元素
剪枝：如果sum+a[i]>r，不再继续（因为和太大了）
更新状态：
保存当前最大值最小值
更新最大值和最小值
更新和
标记访问
递归：继续从当前位置i开始搜索
回溯：恢复所有状态

最坏情况：O(2^n)，但由于剪枝会快很多
由于n≤15，所以可以接受

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 16;

int n, l, r, x, mx, mn, sum, ans, a[N];
bool vis[N];
void dfs(int p) {
    if (sum >= l && sum <= r && mx - mn >= x) ans++;
    for (int i = p; i < n; ++i) if (!vis[i]) {
        if (sum + a[i] <= r) {
            int lx = mx, ln = mn;
            if (a[i] > mx) mx = a[i];
            if (a[i] < mn) mn = a[i];
            sum += a[i];
            vis[i] = true;
            dfs(i);
            sum -= a[i];
            vis[i] = false;
            mx = lx, mn = ln;
        }
    }
}


int main() {
    fast;
    cin >> n >> l >> r >> x;
    for (int i = 0; i < n; ++i) cin >> a[i];
    mx = -1, mn = 2e9;
    if (n == 1 && l <= a[0] && r >= a[0] && x == 0)
        cout << "1\n";
    else {
        dfs(0);
        cout << ans << '\n';
    }
    return 0;
}