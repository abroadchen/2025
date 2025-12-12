//
// Created by Psy.C on 2025/12/13.
//
/*
*sum[N]数组存储前缀和，sum[i]表示从1到i中素数的个数
p[N]布尔数组标记合数(true表示是合数)
init()函数使用埃拉托斯特尼筛法预处理素数：
sum[i] = sum[i-1]：继承前面的素数个数
如果p[i]为true(是合数)，则跳过
否则sum[i]++：素数个数加1
标记i的所有倍数为合数
这样sum[i]就表示区间[1,i]中素数的个数。
 *
*a, b, k是全局变量，分别表示区间起点、终点和要求的素数个数
ok(mid)函数检查是否存在长度为mid的子区间，使得每个这样的区间都至少包含k个素数：
遍历所有长度为mid的子区间[i, i+mid-1]
使用前缀和计算区间素数个数：sum[i+mid-1] - sum[i-1]
如果有任何一个区间素数个数小于k，返回false
如果所有区间都满足条件，返回true
 *
*预处理：O(N log log N)
二分搜索：O(log N)
每次检查：O(N)
总体：O(N log log N + N log N)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;

int sum[N]; bool p[N];
void init() {
    for (int i = 2; i < N; ++i) {
        sum[i] = sum[i - 1];
        if (p[i]) continue;
        sum[i]++;
        for (int j = i + i; j < N; j += i) p[j] = true;
    }
}

int a, b, k;
bool ok(const int mid) {
    for (int i = a; i <= b - mid + 1; ++i)
        if (sum[i + mid - 1] - sum[i - 1] < k) return false;
    return true;
}

int main() {
    fast;
    init(); cin >> a >> b >> k;
    if (sum[b] - sum[a - 1] < k) { cout << "-1\n"; return 0; }//整个区间[a,b]中的素数个数都少于k
    int l = 1, r = b - a + 1, ans = 0;
    while (l <= r) {
        const int mid = (l + r) >> 1;
        if (ok(mid)) ans = mid, r = mid - 1;//长度mid可行，尝试更小的值(r = mid - 1)
        else l = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}