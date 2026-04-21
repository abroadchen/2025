//
// Created by Psy.C on 2026/4/20.
//
/**
s[i][0] 和 s[i][1]: 左侧两个座位
s[i][2]: 分隔符 |
s[i][3] 和 s[i][4]: 右侧两个座位
遍历每一排寻找连续两个'O'（可用座位）
检查左侧两个座位是否都是'O'，如果是则改为'+'（已占用）
检查右侧两个座位是否都是'O'，如果是则改为'+'（已占用）
flag = 1表示找到了可用座位
break表示找到第一个可用座位后立即停止
时间复杂度：O(n)，最多遍历n排座位
空间复杂度：O(n)，存储n排座位的状态
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
char s[2000][10];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    int flag = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i][0] == 'O' && s[i][1] == 'O') {
            flag = 1;
            s[i][0] = '+'; s[i][1] = '+';
            break;
        }
        if (s[i][3] == 'O' && s[i][4] == 'O') {
            flag = 1;
            s[i][3] = '+'; s[i][4] = '+';
            break;
        }
    }
    if (flag) {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= 4; ++j)
                cout << s[i][j];
            cout << '\n';
        }
    } else cout << "NO\n";
    return 0;
}