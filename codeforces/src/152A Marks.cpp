//
// Created by Psy.C on 2025/11/23.
//
/*
 *n（字符串数量）和m（字符串长度）
 *
 *对外层循环，遍历每个字符位置j（从0到m-1）
*内层循环找出在位置j上所有字符串中字符的最大值：
初始化x为'0'
遍历所有字符串，如果v[i][j]大于当前最大值x，则更新x
 *再次遍历所有字符串，如果某个字符串在位置j上的字符等于最大值x，
 *则将对应的ok[i]标记为true
 *
 *统计ok向量中值为true的元素个数
 */
#include <vector>
#include <iostream>
#include <algorithm>
#define rep(i,n) for(size_t i=0;i<n;++i)
using namespace std;

int main() {
    size_t n, m; cin >> n >> m;
    vector<string> v(n);
    rep(i,n) cin >> v[i];
    vector<bool> ok(n, false);//标记每个字符串是否在某位置上是最大的
    rep(j,m) {
        char x = '0';
        rep(i,n) if (v[i][j] > x) x = v[i][j];
        rep(i,n) if (v[i][j] == x) ok[i] = true;
    }
    cout << count(ok.begin(), ok.end(), true);
    return 0;
}