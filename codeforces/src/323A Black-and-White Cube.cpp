//
// Created by Psy.C on 2026/1/8.
//
/**
* draw(i-1, i-1, n-((i-1)<<1), str1[i%2], a);：
起始位置：(i-1, i-1)，从对角线开始
边长：n-((i-1)<<1)，即n-2*(i-1)，随i增大而减小
填充字符：str1[i%2]，根据i的奇偶性选择'w'或'b'
目标数组：a
 *
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000
using namespace std;

char a[N][N], b[N][N];
void draw(const int x, const int y, const int c, const char str, char (&t)[N][N]) {
    for (int i = x; i <= x + c - 1; ++i) {
        for (int j = y; j <= y + c - 1; ++j)
            t[i][j] = str;
    }
}


int main() {
    fast;
    int n; cin >> n;
    if (n % 2 == 1) { cout << -1; return 0; }
    constexpr char str1[] = {'w', 'b'}, str2[] = {'b', 'w'};
    for (int i = 1; i <= n>>1; ++i) draw(i-1, i-1, n-((i-1)<<1), str1[i%2], a);
    for (int i = 1; i <= n>>1; ++i) draw(i-1, i-1, n-((i-1)<<1), str2[i%2], b);
    for (int z = 0; z < n; ++z) {
        if (z % 2 == 0) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) cout << a[i][j];
                cout << '\n';
            }
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) cout << b[i][j];
                cout << '\n';
            }
        }
        cout << '\n';
    }
    return 0;
}