//
// Created by Psy.C on 2025/12/16.
//
/*
 *
*
字符	pos	mx	mn	说明
(开始)	0	0	0	初始状态
+	1	1	0	向上移动，更新最大值
-	0	1	0	向下移动
+	1	1	0	向上移动
-	0	1	0	向下移动
+	1	1	0
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    int p = 0, mx = 0, mn = 0;
    for (const char ch : s) {
        if (ch == '+') p++; else p--;
        mx = max(mx, p);
        mn = min(mn, p);
    }
    cout << mx - mn;
    return 0;
}