//
// Created by Psy.C on 2026/4/14.
//
/**
质数: 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47
平方数: 4(=2²), 9(=3²), 25(=5²), 49(=7²)

printf("%d\n", i): 输出当前数字，询问"这个数是因子吗？"
fflush(stdout): 强制刷新输出缓冲区（交互式题目必需）
cin >> s: 读取回答（"yes"或"no"）
if (s == "yes") ans++: 如果是"yes"，计数器+1
if (ans >= 2): 如果至少有两个"yes"回答
输出"composite"（合数）
否则输出"prime"（质数）
fflush(stdout): 再次刷新输出

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int p[] = {
    2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,4,9,25,49
};
int main() {
    fast;
    int ans = 0;
    for (int i : p) {
        string s; printf("%d\n", i);
        fflush(stdout);
        cin >> s;
        if (s == "yes") ans++;
    }
    if (ans >= 2) cout << "composite\n";
    else cout << "prime\n";
    fflush(stdout);
    return 0;
}