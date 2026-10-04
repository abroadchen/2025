//
// Created by Psy.C on 2026/10/3.
//
/**
N=110：数组上限（对应 n 较小，魔法常数给足 2n 空间）。
a[]：存储全部 2n 个数。
输入 n，再读入 2n 个数
外层 i、内层 j 枚举要删除的两个数的原始下标（i 和 j 不同）。
sum：本次配对差值之和；num：剩余元素计数。
因为没有强制 i<j，所以同一对 (i,j) 会出现两次（(i,j) 与 (j,i)），属于冗余但正确（不影响 min）
把除 i、j 外的所有元素复制到 b[1..num]
对剩余数升序排序。
相邻两两配对：(b1,b2), (b3,b4), ...，差值 b[k+1]-b[k]（排序后保证非负）。
sum += b[k+1]-b[k] 累加。
这是最优配对策略：排序后相邻配对得到的差值之和最小（经典结论——把数排好序相邻配对，总和最小）。
更新 ans = min(ans, sum)
输出所有"删两数方案"中的最小差值之和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 110, inf = 0x3f3f3f3f;
int n, ans, a[N], b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= 2*n; ++i) cin >> a[i];
    ans = inf;
    for (int i = 1, sum, num; i <= 2*n; ++i) {
        for (int j = 1; j <= 2*n; ++j) {
            if (i == j) continue;
            sum = 0, num = 0;
            memset(b, 0, sizeof b);
            for (int k = 1; k <= 2*n; ++k) {
                if (k != i && k != j) {
                    num++;
                    b[num] = a[k];
                }
            }
            sort(b+1, b+num+1);
            for (int k = 1; k <= num; k += 2)
                sum += b[k+1] - b[k];
            ans = min(ans, sum);
        }
    }
    cout << ans;
    return 0;
}