//
// Created by Psy.C on 2026/1/21.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


char c[2005][2005];
//检查矩形内部（不含边界）是否包含'w'字符
int ok(const int t, const int b, const int l, const int r) {
    int flag = 1;
    for (int i = t + 1; i <= b - 1; ++i) for (int j = l + 1; j <= r - 1; ++j) {
        if (c[i][j] == 'w') { flag = 0; break; }
    }
    return flag;//1表示内部没有'w'，返回0表示内部有'w'
}



int main() {
    fast;
    int n, m; cin >> n >> m;
    int t = 2001, b = -1, l = 2001, r = -1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        cin >> c[i][j];
        if (c[i][j] == 'w') {
            t = t > i ? i : t;//最小行号
            b = b < i ? i : b;//最大行号
            l = l > j ? j : l;//最小列号
            r = r < j ? j : r;//最大列号
        }
    }
    int f1 = 0;
    if (int th = r - l + 1, tv = b - t + 1; th == tv) {//当前矩形已经是正方形
        for (int i = t + 1; i <= b - 1; ++i) for (int j = l + 1; j <= r - 1; ++j) {
            if (c[i][j] == 'w') { f1 = 1; break; }
        }
    } else {
        int f2 = 1;
        if (th > tv) {//水平长度大于垂直长度，需要向下扩展
            const int d = th - tv;
            for (int i = t - d; i <= t; ++i) {
                if (i < 1) continue;
                if (i + th - 1 > n) break;
                if (ok(i, i + th - 1, l, r)) {
                    t = i;
                    b = i + th - 1;
                    f2 = 0;
                    break;
                }
            }
            f1 = f2;
        } else if (th < tv) {//垂直长度大于水平长度，需要向右扩展
            const int d = tv - th;
            for (int i = l - d; i <= l; ++i) {
                if (i < 1) continue;
                if (i + tv - 1 > m) break;
                if (ok(t, b, i, i + tv - 1)) {
                    l = i;
                    r = i + tv - 1;
                    f2 = 0;
                    break;
                }
            }
            f1 = f2;
        }
    }
    if (f1 == 1) cout << "-1\n"; else {
        for (int i = t; i <= b; ++i) {
            if (c[i][l] != 'w') c[i][l] = '+';//将新矩形的边界标记为'+'
            if (c[i][r] != 'w') c[i][r] = '+';
        }
        for (int i = l; i <= r; ++i) {
            if (c[t][i] != 'w') c[t][i] = '+';
            if (c[b][i] != 'w') c[b][i] = '+';
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) cout << c[i][j];
            cout << '\n';
        }
    }
    return 0;
}