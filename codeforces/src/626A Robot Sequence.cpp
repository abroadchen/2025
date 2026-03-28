//
// Created by Psy.C on 2026/3/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 205;
int n;
char s[N];
int main() {
    fast;
    cin >> n;
    cin >> s;
    int ans = 0;
    for (int i = 0; i < n; ++i)//起始位置
        for (int j = i + 1; j < n; ++j) {//结束位置
            int ud = 0, lr = 0;//坐标计数器
            for (int k = i; k <= j; ++k) {//遍历子串
                if (s[k] == 'U') ud++;//上移
                else if (s[k] == 'D') ud--;
                else if (s[k] == 'L') lr++;
                else lr--;
            }
            if (!ud && !lr) ans++;//回到原点则计数+1
        }
    cout << ans << '\n';
    return 0;
}