//
// Created by Psy.C on 2026/3/28.
//
/**
检查单独的个位数是否能被4整除
如果能，这一个数字本身就是一个满足条件的子串
if (i > 0): 确保不是第一个字符，有前一个字符可用
int t = num + (s[i-1] - '0')*10: 构造两位数（前一位*10+当前位）
t % 4 == 0: 检查两位数是否能被4整除
ans += i: 关键部分 - 如果两位数能被4整除，以这两位结尾的子串有多少个？
ans += i 表示有多少个以位置i结尾且包含这两位的子串
从位置0到i-1的每个位置都可以作为子串的起始位置
所以有i个这样的子串（从位置0到i的子串，从位置1到i的子串，...，从位置i-1到i的子串）
时间复杂度: O(n)，其中n是字符串长度
空间复杂度: O(1)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    ll ans = 0;//满足条件的子串总数
    for (int i = s.size()-1; i >= 0; --i) {//从字符串末尾开始遍历
        int num = s[i] - '0';
        if (num % 4 == 0) ans++;
        if (i > 0) {
            int t = num + (s[i-1] - '0')*10;
            if (t % 4 == 0) ans += i;
        }
    }
    cout << ans << '\n';
    return 0;
}