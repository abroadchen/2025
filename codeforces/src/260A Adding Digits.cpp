//
// Created by Psy.C on 2025/12/19.
//
/*
* 时间复杂度：O(1)（最多枚举10次）
空间复杂度：O(n)（构造输出字符串）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b, n; cin>>a>>b>>n;
    bool ok = false;
    for (int i = 0; i < 10; ++i) {
        if ((a * 10 + i) % b == 0) {//两位数能否被b整除
            cout << a * 10 + i;
            const string s(n - 1, '0');//构造剩余部分
            cout << s << '\n';
            ok = true;
            break;
        }
    }
    if (!ok) cout << -1 << '\n';
    return 0;
}