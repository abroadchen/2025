//
// Created by Psy.C on 2026/2/18.
//
/**
dp[N]: LIS长度为i时的最小末尾元素
len: 最长递增子序列长度
ty[N]: 每个位置的类型（1=普通，2=可能在LIS中，3=必在LIS中）

构建LIS：O(n log n)
反向处理：O(n²)（最坏情况）
总体：O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 100005;

vector<int> c[N];//每个长度LIS中元素的索引
int a[N];// 输入数组
inline int get(const int i, const int val) {//权值≥val的第一个位置
    int l = 0, r = c[i].size()-1;
    while (l < r) {
        if (const int m = (l+r)>>1; a[c[i][m]] >= val) l = m + 1;
        else r = m;
    }
    return l;
}

int n, dp[N], len=0, ty[N];
int main() {
    fast;
    cin >> n;
    memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        int x = lower_bound(dp, dp + n + 1, a[i]) - dp;//可以放置a[i]的最小位置
        dp[x] = min(dp[x], a[i]);// 更新长度为x的序列的最小末尾元素
        c[x].push_back(i);// 记录在长度x的LIS中位置i
        len = max(len, x);//更新最长长度
    }
    for (int i = 1; i <= n; ++i) ty[i] = 1;//默认所有位置类型为1（普通）
    if (c[len].size() == 1) ty[c[len][0]] = 3;//最长LIS只有一个结尾元素，标记为3（必在LIS中）
    else {
        for (int i = 0; i < c[len].size(); ++i)
            ty[c[len][i]] = 2;
    }
    for (int i = len; i >= 2; --i) {
        for (int j = 0; j < c[i].size(); ++j) {
            if (int idx = c[i][j]; ty[idx] > 1) {
                //前一层权值≥当前元素的位置 前一层索引≥当前索引的位置
                const int l = get(i-1, a[idx]),
                r = ranges::lower_bound(c[i-1], idx) - c[i-1].begin() - 1;
                for (int k = l; k <= r; ++k) ty[c[i-1][k]] = 2;
            }
        }
        int cnt = 0, pos = 0;
        for (int j = 0; j < c[i-1].size(); ++j)
            if (ty[c[i-1][j]] == 2) { cnt++; pos = j; }
        if (cnt == 1) ty[c[i-1][pos]] = 3;
    }
    for (int i = 1; i <= n; ++i) cout << ty[i];
    return 0;
}