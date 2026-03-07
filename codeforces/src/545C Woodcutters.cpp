//
// Created by Psy.C on 2026/3/7.
//
/**
ans：选择的树的数量
i == 0：处理边界情况，选择第一棵树
n == i && !used[n-1]：处理边界情况，如果最后一棵树未被使用，选择它

l = tr[i-1].x, r = tr[i].x：获取相邻两棵树的位置
如果前一棵树已被使用：
计算距离d = r - l
如果距离足够放下当前树的高度（d >= tr[i].h + 1），选择当前树
如果前一棵树未被使用：
d = r - l + 1：计算可用空间
如果空间足够同时放下两棵树（d >= tr[i-1].h + 1 + tr[i].h + 1），选择两棵
否则尝试单独选择前一棵树或后一棵树
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct node {
    int x, h;
    bool operator<(const node &o) const {
        return x < o.x;
    }
} tr[N];

int n;
bool used[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> tr[i].x >> tr[i].h;
    sort(tr, tr + n);
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (i == 0) { used[0] = true; ++ans; continue; }
        if (n == i && !used[n-1]) { used[n-1] = true; ++ans; continue; }
        int l = tr[i-1].x, r = tr[i].x;
        if (used[i-1]) {
            int d = r - l;
            if (d >= tr[i].h + 1) { used[i] = true; ++ans; }
        } else {
            int d = r - l + 1;
            if (d >= tr[i-1].h + 1 + tr[i].h + 1) {
                used[i-1] = used[i] = true;
                ans += 2;
            }
            else if (r - l >= tr[i-1].h + 1) { used[i-1] = true; ++ans; }
            else if (r - l >= tr[i].h + 1) { used[i] = true; ++ans; }
        }
    }
    cout << ans << '\n';
    return 0;
}