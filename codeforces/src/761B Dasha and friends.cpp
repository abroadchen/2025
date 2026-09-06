//
// Created by Psy.C on 2026/9/5.
//
/**
n: 序列中可能出现的最大数字范围（通常是
1
∼
n
1∼n）。
l: 实际使用的序列长度。
a[N], b[N]: 两个布尔型数组，分别用于标记两个序列中每个位置上的数值
lst = a[l-1]; 保存原数组最后一个元素（这里实际上是取第 l-1 位，因为数组是从 0 开始索引）。
for (int j = l-1; j; --j) a[j] = a[j-1]; 将数组从 0 到 l-2 的元素全部向右移动一位。
a[0] = lst; 将保存的最后一个元素放到数组首位，实现了循环左移（左旋转）

遍历 0 到 l-1 的所有位置：
如果发现任意位置 a[j] != b[j]，则说明当前左移后的数组还未匹配成功，设置 flag = true 并跳出循环。
如果整个循环结束都没有触发 flag，则意味着当前左移状态恰好与目标数组相同
如果 flag 为 false（即没有不相等的地方），输出 "YES" 并提前结束程序
如果所有 l 次左移尝试完毕仍未找到匹配项，则输出 "NO"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4+5;
int n, l;
bool a[N], b[N];
int main() {
    fast;
    cin >> n >> l;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        a[x] = true;
    }
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        b[x] = true;
    }
    for (int i = 1; i <= l; ++i) {
        int lst = a[l-1];
        for (int j = l-1; j; --j) a[j] = a[j-1];
        a[0] = lst;
        bool flag = false;
        for (int j = 0; j < l; ++j)
            if (a[j] != b[j]) { flag = true; break; }
        if (not flag) { puts("YES"); return 0; }
    }
    cout << "NO\n";
    return 0;
}