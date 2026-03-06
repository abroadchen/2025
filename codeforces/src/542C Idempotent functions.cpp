//
// Created by Psy.C on 2026/3/6.
//
/**
vis[N]：访问标记数组，用于检测环
ans：结果变量，初始化为1，将存储所有环长度的LCM
st：偏移量，记录进入环之前的路径长度的最大值
遍历数组的每个位置i
x = a[i]：当前值
len = 0：当前路径长度计数器
fill_n(vis + 1, n, 0)：将vis数组清零，准备新一轮遍历
当前元素未被访问时继续循环
vis[x] = ++len：标记x第一次被访问的时间戳
x = a[x]：跳转到下一个位置
这个循环会一直进行直到遇到已经访问过的元素（形成环）
st = max(st, vis[x] - 1)：更新最大前缀长度（进入环之前的路径长度）
len - vis[x] + 1：计算环的长度（当前总长度 - 第一次访问x的位置 + 1）
ans = lcm(ans, len - vis[x] + 1)：更新所有环长度的最小公倍数

从i=1开始循环
寻找第一个满足 ans*i > st 的值
输出 ans*i 并结束程序
这里 ans*i 是环长度的倍数，我们要找的是大于st的第一个这样的数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 210;
int n, a[N], vis[N];
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int ans = 1, st = 0;
    for (int i = 1; i <= n; ++i) {
        int x = a[i], len = 0;
        fill_n(vis + 1, n, 0);
        while (!vis[x]) {
            vis[x] = ++len;
            x = a[x];
        }
        st = max(st, vis[x] - 1);
        ans = lcm(ans, len - vis[x] + 1);
    }
    for (int i = 1; ; ++i)
        if (ans*i > st)
            return cout << ans*i, 0;
}