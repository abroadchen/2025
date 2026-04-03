//
// Created by Psy.C on 2026/4/2.
//
/**
n: 字符串长度
a: 某种操作的代价
b: 另一种操作的代价
T: 总时间/预算
o[N]: 输入字符串
计算处理位置x的总代价
1: 基础代价
(o[x] == 'w')*b: 如果字符是'w'，额外消耗b
(bool)x*a: 如果x非零（不是第一个位置），额外消耗a

当处理第一个字符的代价不超过T时继续
从第1个位置开始处理（第0个位置已处理）
依次处理后续字符，直到时间不够
更新最大处理数量
如果全部处理完则跳出

从后往前逐步减少处理的前缀数量
同时从后面开始处理
动态调整时间预算
更新最大处理数量
从最后一个字符开始向前处理
更新最大处理数量
类似的双向处理策略
从前面开始补充处理
更新答案后跳出内层循环
时间复杂度：O(n²)最坏情况，空间复杂度：O(n)


t: 剩余时间（已经减去了(i-1)*a）
i: 当前考虑保留的前缀长度
j: 从字符串末尾开始处理的字符数
初始化部分：t -= (i-1)*a, j = 0
调整时间预算：减去(i-1)*a（可能是某种补偿或重置）
j = 0：从字符串末尾开始计数
循环条件：i >= 2
至少保留前2个字符
迭代部分：t += get(i-1)+a, i--
t += get(i-1)+a：将位置i-1的代价和额外代价a加回到时间预算中
i--：减少前缀长度，即减少前面处理的字符数
循环条件1：j < n-i
n-i：剩余未处理的字符数（从末尾开始）
不能超过这个限制
循环条件2：get(n-j-1) <= t
检查处理位置n-j-1的字符是否时间充足
n-j-1：从末尾开始的第j+1个字符
循环体：j++, t -= get(n-j-1)
j++：处理的字符数增加
t -= get(n-j-1)：从时间预算中扣除当前字符的处理代价


初始化部分：t -= (i-1)*a, j = 0
调整时间预算（可能是一种重置操作）
j = 0：从字符串开头开始处理的字符数
循环条件：i >= 2
至少保留2个后缀字符
迭代部分：t += get(n-i+1)+a, i--
get(n-i+1): 位置 n-i+1 的处理代价（后缀的最前面那个）
t += get(n-i+1)+a: 将位置 n-i+1 的代价和额外代价a加回时间预算
i--: 减少保留的后缀长度（释放一个后缀字符）
循环条件1：j < n-i
n-i: 当前未被处理的前缀长度
从位置1到n-i是可以处理的范围
循环条件2：get(j+1) <= t
检查处理位置 j+1 的字符是否时间充足
j+1: 从开头开始的第j+1个字符（注意是1-indexed）
循环体：j++, t -= get(j+1)
j++: 处理的前缀字符数增加
t -= get(j+1): 从时间预算中扣除当前字符的处理代价

第一部分策略（前面的代码）：
前缀：从前往后 [0, i-1]
后缀：从后往前 [n-j, n-1]
第二部分策略（当前代码）：
后缀：从后往前 [n-i+1, n-1]（注意这里是n-i+1）
前缀：从前往后 [1, j]（注意从位置1开始）


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5;
int n, a, b, T;
char o[N];
int get(int x) { return 1 + (o[x] == 'w')*b + (bool)x*a; }

int main() {
    fast;
    while (cin >> n >> a >> b >> T >> o) {
        int ans = 0;
        while (get(0) <= T) {
            int t = T - get(0), i, j;
            for (i = 1; i < n; i++) {
                if (get(i) > t) break;
                t -= get(i);
            }
            ans = max(ans, i);
            if (ans == n) break;
            for (t -= (i-1)*a, j = 0; i >= 2; t += get(i-1)+a, i--) {
                for (; j < n-i && get(n-j-1) <= t; j++)
                    t -= get(n-j-1);
                ans = max(ans, i+j);
            }
            if (ans == n) break;
            t = T - get(0);
            for (i = 1; i < n; i++) {
                if (get(n - i) > t) break;
                t -= get(n - i);
            }
            ans = max(ans, i);
            if (ans == n) break;
            for (t -= (i-1)*a, j = 0; i >= 2; t += get(n-i+1)+a, i--) {
                for (; j < n-i && get(j+1) <= t; j++)
                    t -= get(j+1);
                ans = max(ans, i+j);
            }
            break;
        }
        cout << ans << '\n';
    }
    return 0;
}