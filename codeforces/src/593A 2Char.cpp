//
// Created by Psy.C on 2026/3/19.
//
/**
int len = 0;：当前字母组合(i,j)能获得的总长度
for (int k = 0; k < n; ++k)：遍历所有字符串
int flag = 1;：标记当前字符串是否只包含字母i和j
for (int h = 0; h < a[k].size(); ++h)：遍历当前字符串的每个字符
if (a[k][h] != i && a[k][h] != j)：如果字符既不是i也不是j
flag = 0; break;：标记为无效并跳出内层循环
if (flag) len += a[k].size();：如果字符串有效，将其长度加入总长度
时间复杂度：O(26×26×n×m)，其中n是字符串数量，m是平均字符串长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 105;
string a[N];
int n;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int mx = -1;
    for (char i = 'a'; i <= 'z'; ++i)
        for (char j = 'a'; j <= 'z'; ++j) {
            int len = 0;
            for (int k = 0; k < n; ++k) {
                int flag = 1;
                for (int h = 0; h < a[k].size(); ++h)
                    if (a[k][h] != i && a[k][h] != j) {
                        flag = 0; break;
                    }
                if (flag) len += a[k].size();
            }
            mx = max(mx, len);
        }
    cout << mx;
    return 0;
}