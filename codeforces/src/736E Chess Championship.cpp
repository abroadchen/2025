//
// Created by Psy.C on 2026/4/28.
//
/**
a[N]存储分数-索引对
d[N][N]二维字符数组存储比赛结果矩阵
总队伍数m和已知分数队伍数n
t用于累计总分，mn初始化为极大值用于记录最小分数
从位置m-n+1到m读入已知分数
a[i].first存储分数，a[i].second存储队伍索引
累计总分t，同时更新最小分数mn
检查已知分数总和是否超过理论最大值m*(m-1)
计算剩余未分配分数
将剩余分数平均分配给前m-n个未知分数的队伍
使用整除和余数分配实现尽可能均匀分配
如果存在未知分数队伍且最高未知分数大于已知最低分数，则无解
按分数排序
验证是否满足图形序列条件（类似Havel-Hakimi定理）
设置对角线元素为'X'，表示自己对自己的比赛
从分数最高的队伍开始，逐个分配比赛结果
每轮重新排序以确保正确处理
根据当前剩余分数决定比赛结果：
x > 1：当前队胜，得2分，设置'W'/'L'
x == 1：平局，各得1分，设置'D'
x == 0：当前队负，对方得2分，设置'L'/'W'
输出"yes"表示有解
输出完整的比赛结果矩阵
程序结束
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 3007;
int m, n;
ii a[N];
char d[N][N];
int main() {
    fast;
    cin >> m >> n;
    int t = 0, mn = 1<<30;
    for (int i = m-n+1; i <= m; ++i)
        cin >> a[i].first, a[i].second = i, t += a[i].first, mn = min(mn, a[i].first);
    if (t > m*(m-1)) return cout << "no\n", 0;
    t = m*(m-1) - t;
    for (int i = 1; i <= m-n; ++i) a[i] = {t/(m-n)+(i<=t%(m-n)), i};
    if (m-n && a[1].first > mn) return cout << "no\n", 0;
    sort(a + 1, a + m + 1);
    t = 0;
    for (int i = 1; i <= m; ++i) {
        t += a[i].first;
        if (t < i*(i-1)) return cout << "no\n", 0;
    }
    for (int i = 1; i <= m; ++i) d[i][i] = 'X';
    for (int i = m; i; --i) {
        sort(a + 1, a + i + 1);
        int x = a[i].first;
        for (int j = 1; j < i; ++j) {
            if (x > 1) x -= 2, d[a[i].second][a[j].second] = 'W', d[a[j].second][a[i].second] = 'L';
            else if (x == 1) x--, a[j].first--, d[a[i].second][a[j].second] = d[a[j].second][a[i].second] = 'D';
            else a[j].first -= 2, d[a[i].second][a[j].second] = 'L', d[a[j].second][a[i].second] = 'W';
        }
    }
    cout << "yes\n";
    for (int i = 1; i <= m; ++i) cout << d[i] + 1 << '\n';
    return 0;
}