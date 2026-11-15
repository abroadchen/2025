//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
ask(a,b) 在初始 a=b=0 时询问：比较 -A 与 -B。

若结果 <0，说明 -A < -B，即 A > B；f=0 记录"A 比 B 大"这个大小关系。
否则 f=1（默认认为 A <= B）。
f 保存当前 a 与 b 的数值大小关系（哪位更大）
对每一位 i：暂时翻转 a 或 b 的第 i 位各询问一次，得到 x = ask(a^bit, b)、y = ask(a, b^bit)。
利用"只改一位后比较结果的变化"来反推该位
若翻转 a 的该位和翻转 b 的该位比较结果相同，说明现在无法用这两位区分大小——此时把第 i 位赋给"当前更大的那个数"（f 判断），并更新 f：f = (x==1)
若出现 x=-1（翻转 a 后变小）且 y=1（翻转 b 后变大），说明 A、B 的这一位相同（都是 1 或都是 0），此时同时给 a、b 的第 i 位置 1
30 位处理完，a、b 即为还原出的两个未知数，输出 ! a b

若 x == y，则这一位两数相同且能通过 f 决定放到谁身上；
若 x == -1 && y == 1，则这一位也相同（都为 1），直接给两者都置位；
若 x == 1 && y == -1（else 之后未出现），这一位两数不同，当前已由 f 决定大小，无需操作
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int ask(int a, int b, int ret=0) {
    cout << "? " << a << ' ' << b << endl;
    cin >> ret;
    return ret;
}

int a, b;
int main() {
    fast;
    bool f = 1;
    if (ask(a,b) < 0) f = 0;
    for (int i = 29; ~i; i--) {
        //在 a 的第 i 位翻转后比较 在 b 的第 i 位翻转后比较
        int x = ask(a^(1<<i),b), y = ask(a,b^(1<<i));
        if (x == y) {
            if (f) a ^= 1<<i; else b ^= 1<<i;
            f = x == 1;
        }
        else if (x == -1 && y == 1) a ^= 1<<i, b ^= 1<<i;
    }
    cout << "! " << a << ' ' << b << endl;
    return 0;
}