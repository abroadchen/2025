//
// Created by Psy.C on 2026/5/26.
//
/**
n: 总共需要构造的字符串长度
k: 连续相同字符的最大允许数量
a[2]: 存储两种字符的数量，a[0]和a[1]
s[2]: 存储两个字符类型，默认为{'G', 'B'}
计算两种字符数量的最小值和最大值
检查可行性条件：如果较少字符数量加1乘以k仍小于较多字符数量，则无解
这个条件确保我们有足够的较少字符来分隔较多字符
初始化结果字符串
如果a[0] > a[1]，交换两者的值，并相应调整字符映射
确保a[0]始终是较小的值，对应较少的字符类型

cnt跟踪当前连续相同字符的数量
如果剩余的较少字符数量≤较多字符数量且未达到连续上限：
添加较多的字符类型(s[1])
减少其计数，增加连续计数
否则：
添加较少的字符类型(s[0])作为分隔
重置连续计数，减少其计数
输出结果字符串（截取前n个字符）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n, k, a[2];
char s[2] = {'G', 'B'};
int main() {
    fast;
    cin >> n >> k >> a[0] >> a[1];
    int mn = min(a[0], a[1]), mx = max(a[0], a[1]);
    if (1ll*(mn+1)*k < mx) {
        cout << "NO\n";
        return 0;
    }
    string ans;
    if (a[0] > a[1]) {
        s[0] = 'B', s[1] = 'G';
        swap(a[0], a[1]);
    }
    for (int i = 0, cnt = 0; i < n; ++i) {
        if (a[0] <= a[1] && cnt < k) {
            ans += s[1];
            a[1]--, cnt++;
        } else {
            ans += s[0];
            cnt = 0, a[0]--;
        }
    }
    cout << ans.substr(0, n) << '\n';
    return 0;
}