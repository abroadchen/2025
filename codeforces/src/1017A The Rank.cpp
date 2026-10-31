//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
id：选手编号。
o：该选手四科总分。
p[N]：一个长度为 N 的结构体数组，保存所有选手
优先按总分 o 降序比较（return x.o > y.o，总分高的排前面）；
若总分相同（x.o == y.o），则按编号 id 升序（return x.id < y.id，编号小的排前面）
对每个选手 i：

p[i].id = i：记录选手编号。
内层循环读入 4 个整数 x（四科成绩），并对 p[i].o 累加，得到该选手总分。
注意 p[i].o 没有在每次循环前清零，但因为数组是全局的（初值为 0），每个选手只累加一次，所以结果是正确的
用 sort 对 p[1] 到 p[n] 排序，排序规则用 cmp。排序后，p 数组中选手按 "总分降序、同分编号升序" 排列，p[1] 就是第一名
遍历排序后的数组，找到编号为 1 的选手（p[i].id == 1），输出它的排名 i（即它排第几位），换行后结束
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1001;

struct node { int id, o; } p[N];
bool cmp(node x, node y) {
    if (x.o != y.o) return x.o > y.o;
    return x.id < y.id;
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        p[i].id = i;
        for (int j = 1, x; j <= 4; j++) { cin >> x; p[i].o += x; }
    }
    sort(p+1, p+1+n, cmp);
    for (int i = 1; i <= n; i++)
        if (p[i].id == 1) cout << i << '\n';
    return 0;
}