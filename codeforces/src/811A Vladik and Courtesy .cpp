//
// Created by Psy.C on 2026/9/20.
//
/**
a：第一个人（Vladik）的"石子/糖果"数量
b：第二个人（Valera）的"石子/糖果"数量
i：Vladik 本轮要取的数量，初始 1
j：Valera 本轮要取的数量，初始 2
规律：两人轮流取，Vladik 每次取 1, 3, 5, 7, ...（奇数递增），Valera 每次取 2, 4, 6, 8, ...（偶数递增
每一轮：

Vladik 先取：a -= i（从 a 里扣掉 i 个）。
判断 a 是否还 ≥ 0：
若 a < 0，说明 Vladik 这轮不够取（本轮取完就成负数）→ 他 "输了"。
若 a >= 0，Vladik 取出成功，轮到 Valera 取：b -= j。
（若 Vladik 已经取不成，Valera 就不取，循环也随即退出。）
更新下一轮的取数：i += 2, j += 2（各自下次多取 2）。
注意：Valera 取完后不检查 b 是否 < 0（下一轮 while 条件才检查 b>=0）。取 b -= j 后，如果 b 变成负数，下一轮 while 的 b >= 0 不成立，循环退出，此时输家是 Valera（a >= 0 成立，输出 Valera）
若 a < 0：Vladik 在某轮取石时不够取，Vladik 输。
否则（a ≥ 0 但 b < 0，即 Valera 取石时不够）：Valera 输
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll a, b, i(1), j(2); cin >> a >> b;
    while (a >= 0 && b >= 0) {
        a -= i;
        if (a >= 0) b -= j;
        i += 2; j += 2;
    }
    if (a < 0) cout << "Vladik\n";
    else cout << "Valera\n";
    return 0;
}