//
// Created by Psy.C on 2025/11/24.
//
/*
 *a、b用于存储要查找的字符对
 *计算当前段的贡献：min(l,r)
 *
 *时间复杂度是O(k×n)，其中k是查询次数，n是字符串长度
 *
 *循环内的处理：只有遇到分界符时才会触发段的结算
 *
 */
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ostream::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; getline(cin, s);
    int k; cin >> k;
    char a, b;
    int ans(0);
    for (int i = 1, l, r; i <= k; ++i) {
        cin >> a >> b; l = 0; r = 0;
        for (int j = 0; j <= s.size() - 1; ++j) {
            if (s[j] == a) l++;
            else if (s[j] == b) r++;
            else { ans += min(l, r); l = 0; r = 0; }
        }
        ans += min(l, r);//处理末尾的最后一段
    }
    cout  << ans;
    return 0;
}