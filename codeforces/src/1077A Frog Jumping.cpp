//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
情况一：k 为偶数

当 k 是偶数时，k 次操作恰好可以分成 k/2 组完整的 (+a, -b) 对：

每组净效果：a - b
总效果：(a - b) * (k/2)
即输出 (a-b)*k/2。✅

情况二：k 为奇数

当 k 是奇数时，k 次操作 = (k/2) 组完整的 (+a, -b) 加上最后多出的一次 +a（因为序列交替以 +a 开头，奇数位时最后落在 +a）：

完整对的效果：(a - b) * (k/2)
额外的一次：+ a
即输出 (a-b)*(k/2) + a。✅

注意这里 k/2 是整数除法（向下取整），当 k 为奇数时正好等于 (k-1)/2，正是完整配对的组数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll T, a, b, k;
int main() {
    fast;
    cin >> T;
    while (T--) {
        cin >> a >> b >> k;
        if (k%2 == 0) cout << (a-b)*k/2 << '\n';
        else cout << (a-b)*(k/2)+a << '\n';
    }
    return 0;
}