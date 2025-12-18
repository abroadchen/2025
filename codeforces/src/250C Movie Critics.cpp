//
// Created by Psy.C on 2025/12/17.
//
/*
*珠子总数n和颜色种类数k
num[N]：统计每种颜色的重要性得分，初始化为0
a[N]：存储去重后的颜色序列
len：去重后序列的长度
t：临时变量用于读取颜色
初始化：a[0] = 0，len = 0
*读取所有珠子颜色
只有当当前颜色与序列最后一个颜色不同时才添加
这样去除连续相同的珠子，简化后续计算
 *
*遍历去重序列中除首尾外的所有位置
如果某个颜色的前一个和后一个颜色相同：
该颜色重要性加2（因为它连接了两个相同颜色）
否则重要性加1
*序列的第一个和最后一个颜色重要性各加1
因为它们位于端点，具有特殊意义
 *
*v：当前最高重要性分数
ans：最重要颜色的编号
遍历所有可能的颜色(1到k)，找出重要性最高的
输出结果
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    int num[N] = {}, a[N], len, t;
    a[0] = len = 0;
    int q = n;
    while (q--) {
        cin >> t;
        if (a[len] != t) { len++; a[len] = t; }//只有当当前颜色与序列最后一个颜色不同时才添加
    }
    for (int i = 2; i <= len - 1; ++i) {
        if (a[i - 1] == a[i + 1]) num[a[i]] += 2;
        else num[a[i]]++;
    }
    num[a[1]]++; num[a[len]]++;
    int v = 0, ans = 1;
    for (int i = 1; i <= k; ++i) if (num[i] > v) {
        v = num[i]; ans = i;
    }
    cout << ans << '\n';
    return 0;
}