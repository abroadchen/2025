//
// Created by Psy.C on 2025/11/16.
//
/*
*x计算当前行的数字范围：
前n+1行：x = i（逐渐增加）
后n行：x = 2*n-i（逐渐减少）
sp计算前导空格数量
 */
#include <iostream>
#define rep(i,n) for(int i=0;i<=(n);++i)
#define per(i,n) for(int i=(n);i>=0;--i)
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    rep(i,2*n) {//2n+1次迭代（生成菱形的所有行）
        int x = min(i,2*n-i), sp = 2 * (n - x);
        string ans = "";//构建当前行的数字部分
        rep(j,x) {
            if (j > 0) ans += " ";//数字间用空格分隔
            ans += '0' + j;
        }
        per(j,x-1) {
            ans += " ";
            ans += '0' + j;
        }
        cout << string(sp, ' ') << ans << '\n';
    }
    return 0;
}