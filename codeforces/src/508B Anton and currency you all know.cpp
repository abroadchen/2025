//
// Created by Psy.C on 2026/2/26.
//
/**

寻找偶数数字的位置
如果找到的偶数小于最后一位数字，则停止查找
idx记录找到的最左边符合条件的位置

交换最后一位和找到的偶数位
输出修改后的字符串
时间复杂度为O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

string s;
ll n;
int main() {
    fast;
    cin >> s;
    n = s.size() - 1;//最后一位的索引
    ll idx = -1;
    for (int i = 0; i < n; ++i)
        if ((s[i] - '0') % 2 == 0) {
            idx = i;
            if (s[n] > s[i]) break;
        }
    if (idx == -1) cout << "-1\n";
    else {
        swap(s[n], s[idx]);
        cout << s << '\n';
    }
    return 0;
}