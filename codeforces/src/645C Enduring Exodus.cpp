//
// Created by Psy.C on 2026/4/1.
//
/**
n: 字符串长度
sum[N]: 前缀和数组，记录'0'的个数
k: 目标'0'的个数

检查以位置i为中心，半径为dis的区间内'0'的个数是否≥k+1
l = max(1, i-dis), r = min(n, i+dis): 确保区间边界在[1,n]范围内
sum[r] - sum[l-1]: 计算区间[l,r]内'0'的个数
注意：这里是k+1，因为要包含中心位置的'0'
二分搜索找到位置i所需的最小半径
l = 1, r = n: 搜索范围[1,n]
如果ok(i, mid)为真，说明半径mid足够，记录并尝试更小半径
否则需要更大半径
返回最小可行半径

如果当前字符是'0'，计数加1
否则保持前一个位置的计数
遍历每个位置i
只对字符'0'的位置进行处理（因为要找以'0'为中心的区间）
对每个'0'位置，计算所需最小半径，并更新全局最小值
时间复杂度：O(n log n)，其中每个位置需要O(log n)的二分搜索

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5+5, inf = 0x3f3f3f3f;

int n, sum[N], k;
bool ok(int i, int dis) {
    int l = max(1, i-dis), r = min(n, i+dis);
    return sum[r] - sum[l-1] >= k+1;
}
int get(int i) {
    int mn = 0, l = 1, r = n;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (ok(i, mid)) { mn = mid, r = mid - 1; }
        else l = mid + 1;
    }
    return mn;
}

char a[N];
int main() {
    cin >> n >> k;
    scanf("%s", a + 1); sum[0] = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == '0') sum[i] = sum[i-1] + 1;
        else sum[i] = sum[i-1];
    }
    int ans = inf;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == '1') continue;
        ans = min(ans, get(i));
    }
    cout << ans << '\n';
    return 0;
}