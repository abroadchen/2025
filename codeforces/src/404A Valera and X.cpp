//
// Created by Psy.C on 2026/1/31.
//
/**
 *
 *n=2的情况，(0,1)在副对角线上
 *
*对于n ≥ 3：

(0,1)位置：i=0, j=1
主对角线检查：0 ≠ 1 → 不在主对角线
副对角线检查：1 ≠ n-1 (当n≥3时) → 不在副对角线
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 500
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    char s[N][N];
    for (int i = 0; i < n; ++i) cin >> s[i];
    const char c = s[0][0]; bool f = true;//主对角线和副对角线的公共字符
    for (int i = 0; i < n; ++i) {
        if (s[i][i] != c || s[i][n-i-1] != c) {//两条对角线是否都是字符c
            cout << "NO\n";
            f = false;
            break;
        }
    }
    if (f == false) return 0;//如果条件不满足，直接返回
    const char h = s[0][1];//非对角线区域的字符
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j || j == n - i - 1) continue;//跳过对角线位置
            if (h != s[i][j] || s[i][j] == c) {//非对角线位置是否都是字符h 并且不能等于对角线字符c
                cout << "NO\n";
                f = false;
                break;
            }
        }
        if (f == false) break;
    }
    if (f) cout << "YES\n";
    return 0;
}