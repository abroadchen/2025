//
// Created by Psy.C on 2026/1/30.
//

#include <iostream>
#include <stack>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int m, n; cin >> m >> n;
    char c[4];
    int c00 = 0, c01 = 0, c11 = 0;
    for (int i = 0; i < n*m; ++i) {
        cin >> c;
        switch (c[0] + c[1]) {
            case 96: c00++; break;//'0' + '0' = 48 + 48 = 96
            case 97: c01++; break;
            case 98: c11++; break;
            default: ;
        }
    }
    stack<char> s;
    for (int i = 0; i < m; ++i) {
        if (i&1) for (int j = 0; j < n; ++j) {
            if (c11) {
                s.push(j == 0 ? '\n' : ' ');//每个数字对前压入换行符或空格
                s.push('1'); s.push('1'); c11--;
            } else if (c01) {
                s.push(j == 0 ? '\n' : ' ');
                s.push('0'); s.push('1'); c01--;
            } else {
                s.push(j == 0 ? '\n' : ' ');
                s.push('0'); s.push('0');
            }
        } else {//偶数行处理（直接输出）
            for (int j = 0; j < n; ++j) {
                if (c11) {
                    cout << "11" << (j == n - 1 ? '\n' : ' '); c11--;//每行末尾输出换行符，其他输出空格
                } else if (c01) {
                    cout << (i&1 ? "10" : "01") << (j == n - 1 ? '\n' : ' '); c01--;
                } else cout << "00" << (j == n - 1 ? '\n' : ' ');
            }
        }
        while (!s.empty()) cout << s.top(), s.pop();
    }
    return 0;
}