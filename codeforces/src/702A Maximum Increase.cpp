//
// Created by Psy.C on 2026/4/18.
//
/**
n: 序列长度
pre: 上一个读入的数值，用于比较
l = 1: 记录最长递增序列长度，初始化为1（至少有一个元素）
num = 1: 记录当前递增序列长度，初始化为1

从第二个元素开始遍历（i从1开始）
cin >> t: 读入当前元素
if (t > pre): 如果当前元素大于前一个元素
num++: 当前递增序列长度加1
l = max(l, num): 更新最大递增序列长度
else num = 1: 如果不满足递增，重置当前长度为1
pre = t: 更新前一个元素为当前元素
时间复杂度：O(n)，只需遍历一次数组
空间复杂度：O(1)，只使用常数个变量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, pre, l = 1, num = 1;
int main() {
    fast;
    cin >> n >> pre;
    for (int i = 1, t; i < n; ++i) {
        cin >> t;
        if (t > pre) num++, l = max(l, num);
        else num = 1;
        pre = t;
    }
    cout << l;
    return 0;
}