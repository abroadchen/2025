//
// Created by Psy.C on 2026/4/13.
//
/**
n: 范围的上界（区间[1,n]）
m: 查询次数
l = 1, r = n: 初始化交集区间为[1,n]
对于每个查询区间[x,y]：
cin >> x >> y: 读入查询区间的左右端点
if (x > y) swap(x, y): 确保x ≤ y，标准化区间
l = max(l, x): 更新交集区间的左端点为较大值
r = min(r, y): 更新交集区间的右端点为较小值

r - l: 计算交集区间的长度
如果r - l >= 0（区间存在），输出区间长度
否则（区间不存在），输出0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
int main() {
    fast;
    cin >> n >> m;
    int l = 1, r = n;
    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        if (x > y) swap(x, y);
        l = max(l, x);
        r = min(r, y);
    }
    if (r - l >= 0) cout << r - l << '\n';
    else cout << "0\n";
    return 0;
}