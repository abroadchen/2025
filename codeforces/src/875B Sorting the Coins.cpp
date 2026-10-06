//
// Created by Psy.C on 2026/10/6.
//
/**
a[]：标记数组（a[x]=1 表示数字 x 已被使用）。
cnt：当前从末尾（n）往左连续被使用的位置个数。
tot：累计所有被"跳过折叠"的数字个数计数器
读入总人数/总数 n。
先输出 1（初始"还有 1 个可安排"，即第一个总是可用）
每次读入一个被用掉的数字 x，a[x] = 1 标记它。

if (i == n) { cout << 1; return 0; }：当输入完第 n 个数时，直接输出 1 并结束（此时全用完了）
从位置 j = n - cnt 开始，只要 a[j] 已被标记（即该数字已被使用），就继续往前，同时 cnt++ 和 tot++。
意思：尾部一段连续被使用的数字。cnt 记录尾部这段长度。
输出 i - tot + 1：

i 是当前已读入个数，tot 是累计的"尾部被填补"总数，i - tot + 1 表示"还剩多少位置/人数"
cnt/tot 维护的是"从末尾数起连续被占用的个数"。每读入一个新数，就把尾巴上连续被占用的部分"折叠"掉（用 tot 累计折叠走的数字个数），然后 i - tot + 1 就是剩余可用的位置数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+10;
int a[N], cnt, tot;
int main() {
    fast;
    int n; cin >> n;
    cout << 1 << ' ';
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (i == n) { cout << 1; return 0; }
        a[x] = 1;
        for (int j = n-cnt; a[j]; --j) cnt++, tot++;
        cout << i - tot + 1 << ' ';
    }
    return 0;
}