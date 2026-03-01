//
// Created by Psy.C on 2026/3/1.
//
/**
n：数组长度
k：分组大小
a[N]：存储处理后的数组

对每个分组i（1到k）：
遍历该分组中的已知数字
如果a[j] <= 0：向前填充递减序列
如果a[j] >= 0：向后填充递增序列
只填充'?'位置（值为inf）

找到分组i中第一个'?'位置s
找到连续'?'段的结束位置t
计算中间段的起始值
考虑前后已知数字的约束
填充中间连续'?'段

检查是否还有未填充的'?'（inf）
检查每个分组是否严格递增


(t-s)/k：计算从s到t之间有多少个k步间隔
/2：取一半作为起始值的偏移量
这是在计算连续'?'段的中心位置的值
s - k >= i：检查前面是否有已知元素
a[s-k] >= d：如果前面的元素值大于等于当前计算的d值
d = a[s-k] + 1：调整d值使其满足递增要求
确保 a[s-k] < a[s]（前一个小于后一个）
t + k <= n：检查后面是否有已知元素
(t-s)/k：从s到t的步数
d + (t-s)/k：如果按当前d值填充，t位置的值会是d + (t-s)/k
a[t+k] <= d + (t-s)/k：如果后面的元素小于等于当前计算的t位置值
d = a[t+k] - 1 - (t-s)/k：调整d值确保a[t] < a[t+k]

从位置s开始，每隔k步填充一个值
++d：每次填充后d递增1，保证严格递增
j += k：跳到下一个待填充位置
a[j] = d：填充当前值


// 方法1：stoi函数
a[i] = stoi(s);

// 方法2：atoi函数
a[i] = atoi(s.c_str());

// 方法3：stringstream（当前代码使用）
stringstream ss(s);
ss >> a[i];

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+1, inf = 0x3f3f3f3f;
int n, k, a[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        if (s[0] == '?') a[i] = inf;
        else {
            stringstream ss(s);
            ss >> a[i];
        }
    }
    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= n; j += k) if (a[j] != inf) {
            if (a[j] <= 0) {
                int now = a[j];
                for (int x = j - k; x >= i; x -= k) {
                    if (a[x] == inf) a[x] = --now;
                    else break;
                }
            }
            if (a[j] >= 0) {
                int now = a[j];
                for (int x = j + k; x <= n; x += k) {
                    if (a[x] == inf) a[x] = ++now;
                    else break;
                }
            }
        }
        int s = i;
        while (a[s] != inf && s <= n) s += k;
        if (s > n) continue;
        int t = s;
        while (a[t] == inf && t <= n) t += k;
        t -= k;
        int d = (s-t)/k/2;
        if (s - k >= i && a[s-k] >= d) d = a[s-k] + 1;
        if (t + k <= n && a[t+k] <= d + (t-s)/k) d = a[t+k] - 1 - (t-s)/k;
        for (int j = s; j <= t; ++d, j += k) a[j] = d;
    }
    for (int i = 1; i <= n; ++i)
        if (a[i] == inf) return cout << "Incorrect sequence\n", 0;
    for (int i = 1; i <= k; ++i)
        for (int j = i+k; j <= n; j += k)
            if (a[j] <= a[j-k])
                return cout << "Incorrect sequence\n", 0;
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}