//
// Created by Psy.C on 2025/12/17.
//
/*
*n: 排列的长度
k: 操作次数限制
i, j: 循环变量
a, b: 计数器，初始值为0
*q[]: 存储给定的排列
s[]: 存储目标排列
t[]: 临时数组，用于中间计算
p[]: 当前排列状态
 *
*从位置1开始检查当前排列p是否与目标排列s相同
如果p[j]等于s[j]就继续检查下一个位置
一旦发现不同元素或检查完所有元素就退出循环
 *如果j等于n+1，说明已经检查完所有位置且都相同，跳出while循环
 *
*对每个位置j，将p[q[j]]的值赋给t[j]
这实际上是应用排列q到当前排列p上
 *
 *
*t[j] = p[q[j]]：正向置换
把位置j的元素替换为原来位置q[j]的元素
意思是"位置j接收来自位置q[j]的元素"
t[q[j]] = p[j]：逆向置换
把位置q[j]的元素替换为原来位置j的元素
意思是"位置j的元素移动到位置q[j]"
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 103
#define rep(i,n) for(i=1;i<=n;++i)
using namespace std;


int main() {
    fast;
    int n, k, i, j, a = 0, b = 0; cin>>n>>k;
    int q[N], s[N], t[N], p[N];
    rep(i,n) cin>>q[i];
    rep(i,n) cin>>s[i];
    rep(i,n) t[i] = p[i] = i;//单位排列[1,2,3,...,n]
    while (a <= k) {
        for (j = 1; j <= n && p[j] == s[j]; ++j) {}
        if (j == n + 1) break;
        rep(j,n) t[j] = p[q[j]];
        rep(j,n) p[j] = t[j];//不能直接修改正在使用的数组
        a++;
    }
    rep(i,n) t[i] = p[i] = i;
    while (b <= k) {
        for (j = 1; j <= n && p[j] == s[j]; ++j) {}
        if (j == n + 1) break;
        rep(j,n) t[q[j]] = p[j];//第一种操作的逆操作
        rep(j,n) p[j] = t[j];
        b++;
    }
    if (a == 1 && b == 1 && k == 1) cout << "YES";
    else if (a == 1 && b == 1) cout << "NO";
    else if (a == k + 1 && b == k + 1) cout << "NO";
    else if (!a && !b) cout << "NO";
    else if (b + k + 1 & 1 || a + k + 1 & 1) cout << "YES";
    else cout << "NO";
    return 0;
}