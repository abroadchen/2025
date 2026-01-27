//
// Created by Psy.C on 2026/1/27.
//
/*
* 时间复杂度
O(n²)，其中n是字符串长度
需要检查所有可能的子串
空间复杂度
O(1)，只使用常数额外空间（不计算输入字符串）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

string s1 = "bear";

int main() {
    fast;
    string s; cin >> s;
    ll ans = 0;//包含"bear"的子串数量
    for (ll i = 0, cnt, k; i < s.size(); ++i) {//子串的起始位置
        cnt = 0, k = 0;
        for (ll j = i; j < s.size(); ++j) {//子串的结束位置
            if (s[j] == s1[0]) cnt = 1;//当前匹配到"bear"的第几个字符 开始新的匹配
            else if (s[j] == s1[cnt]) cnt++;//继续匹配
            else cnt = 0;//重置匹配状态
            if (cnt == 4) k = 1;//是否已经匹配到完整"bear"
            ans += k;
        }
    }
    cout << ans << '\n';
    return 0;
}