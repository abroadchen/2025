//
// Created by Psy.C on 2025/12/22.
//
/*
*n：整型变量，存储学生人数
f：整型变量，临时存储每个学生的评分
tot = 0：整型变量，初始化为0，用于累计所有学生的评分总和
ans = 0：整型变量，初始化为0，用于存储最终答案
 *
*(tot + i)：当前总分加上可能的评分i
% (n + 1)：对(n+1)取模运算
 *
 *第(n+1)个学生  学生总数(n+1)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, f, tot = 0, ans = 0; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> f;
        tot += f;
    }
    for (int i = 1; i <= 5; ++i) {
        if ((tot + i) % (n + 1) != 1) ans++;
    }
    cout << ans << '\n';
    return 0;
}