//
// Created by Psy.C on 2026/2/4.
//
/**
* 时间复杂度：O(n)，最多遍历一次字符串
空间复杂度：O(n)，存储字符串
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    char s[205]; cin >> s;
    int a = 0, b = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'x') a++;//统计小写'x'的数量
        else b++;
    }
    int ans = 0;
    if (a == b) {
        cout << "0\n";//不需要修改
        cout << s << '\n';//原字符串
    } else if (a > b) {//'x'比'X'多
        for (int i = 0; i < n && a != b; ++i) {//直到a==b为止
            if (s[i] == 'x') {
                ans++;//操作数增加
                s[i] = 'X';
                a--; b++;//'x'减少 'X'增加
            }
        }
        cout << ans << '\n';
        cout << s << '\n';
    } else {
        for (int i = 0; i < n && a != b; ++i) {
            if (s[i] == 'X') {
                ans++;
                s[i] = 'x';
                a++; b--;
            }
        }
        cout << ans << '\n';
        cout << s << '\n';
    }
    return 0;
}