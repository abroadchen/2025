//
// Created by Psy.C on 2026/3/30.
//
/**
t: 统计每个数字的出现次数
g: 临时统计当前斐波那契序列中已使用的数字
统计每个数字出现次数
排序便于后续优化
0的个数本身就是答案的一部分（全为0的斐波那契数列）

外层循环
枚举斐波那契数列的第一项 a[i]
内层循环
枚举斐波那契数列的第二项 a[j]
g[f3]: 当前序列中数字f3已使用的次数
t[f3]: 原数组中数字f3总的可用次数
while (g[f3] < t[f3]): 只要还能找到f3，就继续扩展序列

外层嵌套循环：O(n²)
内层斐波那契扩展：取决于斐波那契序列长度
总体：O(n² × log(max_value))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
int n, a[N], ans;
map<int, int> t, g;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; t[a[i]]++;
    }
    sort(a + 1, a + n + 1);
    ans = max(ans, t[0]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1, f1, f2, f3, res; j <= n; ++j) {
            if (i == j) continue;//同一个元素
            if (!a[i] && !a[j]) continue;//两个0的情况
            if (a[i] == a[i-1] && i > 1) break;//跳过重复的第一个元素
            g.clear();
            f1 = a[i], f2 = a[j], f3 = f1 + f2, res = 2;
            g[f1]++, g[f2]++;
            while (g[f3] < t[f3]) {//当前数字f3的使用次数未超过可用次数
                res++, g[f3]++;
                f1 = f2, f2 = f3, f3 = f1 + f2;//斐波那契递推
            }
            ans = max(ans, res);
        }
    cout << ans;
    return 0;
}