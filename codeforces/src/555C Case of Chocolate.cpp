//
// Created by Psy.C on 2026/3/10.
//
/**
x, y: 读入的坐标和参数
c: 方向字符（'L' 或 'R'）
mp: 有序映射，键为站点位置，值为 {方向字符, 累积距离}
读入查询参数（实际只需要x和c）
lower_bound(x): 查找第一个位置≥x的站点
如果正好在该位置，返回0
如果目标方向是'L'，向前一个站点移动
计算当前位置到最近站点的距离
如果当前站点的方向与目标方向一致，则加上累积距离
在map中记录新站点信息
返回计算的距离

读入轨道长度n和查询次数q
在位置0设置虚拟站点（方向'U'，距离0）
在位置n+1设置虚拟站点（方向'L'，距离0）

每次查询：O(log n)，由于map的查找和插入操作
总体：O(q log q)，其中q是查询次数
 */
#include <bits/stdc++.h>
using namespace std;

int x, y;
char c;
map<int, pair<char, int>> mp;
int get() {
    scanf("%d%d%c%c", &x, &y, &c, &c);
    auto it = mp.lower_bound(x);
    if (it->first == x) return 0;
    if (c == 'L') --it;
    int ans = abs(it->first - x);
    if (it->second.first == c)
        ans += it->second.second;
    mp[x] = {c, ans};
    return ans;
}

int n, q;
int main() {
    scanf("%d%d", &n, &q);
    mp[0] = {'U', 0}; mp[n+1] = {'L', 0};
    for (int i = 1; i <= q; ++i)
        printf("%d\n", get());
    return 0;
}