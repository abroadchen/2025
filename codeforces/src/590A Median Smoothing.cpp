//
// Created by Psy.C on 2026/3/18.
//
/**
a[N]: 主要操作的数组
get(l, r): 将区间[l,r]两端的值扩展到整个区间
x = a[l], y = a[r]: 记录区间两端的值
while (l <= r): 从两端向中间填充
a[l++] = x; a[r--] = y: 左端填x，右端填y
b[N]: 标记数组，标记哪些位置是特殊位置
将首尾元素标记为特殊位置（b[1] = b[n] = 1）
遍历中间元素，如果当前元素与左邻居或右邻居相等，则标记为特殊位置

ans: 记录最大长度
len: 当前连续非特殊位置的长度
p: 上一个特殊位置
遇到特殊位置时：
调用get(p, i)将区间[p,i]用两端值填充
更新最大长度（区间长度的一半向上取整）
重置长度计数器，更新p为当前位置
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5;

int a[N];
void get(int l, int r) {
    int x = a[l], y = a[r];
    while (l <= r) { a[l++] = x; a[r--] = y; }
}

int n, b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    b[1] = b[n] = 1;
    for (int i = 2; i < n; ++i)
        if (a[i] == a[i-1] || a[i] == a[i+1])
            b[i] = 1;
    int ans = 0, len = 0, p = 0;
    for (int i = 1; i <= n; ++i) {
        if (b[i]) {
            get(p, i);
            ans = max(ans, (len + 1)>>1);
            len = 0; p = i;
        } else len++;
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) cout << a[i] << " \n"[i==n];
    return 0;
}