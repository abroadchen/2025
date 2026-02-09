//
// Created by Psy.C on 2026/2/8.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char b[105][105];
int n, m;

int main() {
    fast;
    cin >> n >> m;
    memset(b, 0, sizeof b);
    for (int i = 1; i <= n; ++i) {
        char s[105]; cin >> s;//读取第i行的字符串
        for (int j = 1; j <= m; ++j) {
            //输入的s索引从0开始，而b索引从1开始
            b[i][j] = s[j-1];//输入字符串的第j-1个字符复制到b[i][j]
            if (b[i][j] != '-') {
                if ((i+j)&1) b[i][j] = 'B';
                else b[i][j] = 'W';
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cout << b[i][j];
        cout << '\n';
    }
    return 0;
}