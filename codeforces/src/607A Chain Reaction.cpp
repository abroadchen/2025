//
// Created by Psy.C on 2026/3/22.
//
/**
位置x、速度v、k值

dp[i]表示以第i个节点结尾的最长序列长度
pos = i - a[i].k - 1表示能够转移到当前状态的前一个状态位置
如果pos < 0，说明不能从前一个状态转移，dp[i] = 1
否则dp[i] = dp[pos] + 1
n - mx，即最少需要删除的节点数

len = sz: 搜索范围的长度
f = 0: 搜索范围的起始位置
h = len>>1: 即len/2，取中间偏左的位置
情况1: a[mid].x < x（中间值小于目标值）
说明目标值在右半部分
将左边界移到mid + 1
搜索长度变为len - h - 1
情况2: a[mid].x >= x（中间值大于等于目标值）
说明目标值在左半部分或就是mid位置
不移动边界，将搜索长度缩小为h

按x坐标排序
对每个节点i，计算关键值key = a[i].x - a[i].v
使用二分查找找到第一个x坐标不小于key的位置pos
计算k值：k = i - pos（表示在当前节点之前有多少节点满足条件）


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct node {
    int x, v, k;
    bool operator<(const node &o) const {
        return x < o.x;
    }
} a[N];

///在前sz个元素中查找第一个x坐标不小于给定值x的位置
int get(int sz, int x) {
    int len = sz, f = 0, mid, h;
    while (len > 0) {
        h = len>>1; mid = f + h;
        if (a[mid].x < x) {
            f = mid + 1;
            len = len - h - 1;
        } else len = h;
    }
    return f;
}

int n, dp[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].v;
    sort(a, a + n); a[0].k = 0;
    int key, pos, num;
    for (int i = 1; i < n; ++i) {
        key = a[i].x - a[i].v; pos = get(i, key);
        num = i - pos; a[i].k = num;
    }
    dp[0] = 1;
    for (int i = 1; i < n; ++i) {
        pos = i - a[i].k - 1;
        if (pos < 0) dp[i] = 1;
        dp[i] = dp[pos] + 1;
    }
    int mx = 0;
    for (int i = 0; i < n; ++i)
        if (mx < dp[i]) mx = dp[i];
    cout << n-mx << '\n';
    return 0;
}