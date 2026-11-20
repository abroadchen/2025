//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
发送 ? x y 询问，读一个字符 c：
'x' → 返回 1（表示 x 大于 a）；
'y' → 返回 2（表示 a 大于等于 y）；
其它（如 'e' 之类）→ 返回 3
输出最终答案 ! x。
从 x=1 开始，每次问 (x, 2x)：
若返回 1（'x'，即 x > a），说明 a < x，此时上界是 x，直接返回，它作为二分下界 l。
否则把 x 翻倍继续，直到跨越 a。
结束时 x 满足 a < x（上界），而返回的 x 作为二分左端点 l
外层循环：读入一行开头字符串 s（一般是 "start" 或 "end"）：

若是 'e'（即 "end"），退出。
否则正式处理一个测试用例。
先问 (0,1)：

返回 1（'x'，x=0 > a，说明 a < 0？实际这表示 a=0）…… 代码直接 out(1)，推测问 (0,1) 得 'x' 时答案是 1（边界情况）。这里正确处理了一个特例：当 a=0 时，ask(0,1) 返回 'x'（因为 0 > a 不成立？）
细看：若 a=0，ask(0,1)，0 > 0 为假 → 应返回 'y'。但若 a 使得... 这属于题目的特判分支，代码作者用 (0,1) 判断 a==0 的边界，直接输出 1。

正常情况：

l = get()（倍增确定上界），r = 2*l，区间 [l, r) 包住 a。
二分 while (l+1 < r)：
mid = (l+r)/2；
问 ask(l, mid)：
返回 2（'y'，mid...即 a ≥ l？实际表示 l 不是过大，a ≥ mid）：l = mid（把下界提到 mid，a 在右侧）。
否则（返回 1/'x'，a < mid）：r = mid（收窄上界）。
循环直到 l、r 相邻，输出 r 作为答案。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int ask(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    char c; cin >> c;
    if (c == 'x') return 1;
    if (c == 'y') return 2;
    return 3;
}
void out(int x) { cout << "! " << x << endl; }
int get() {
    int x = 1;
    while (1) {
        int f = ask(x,x*2);
        if (f == 1) return x;
        x *= 2;
    }
}
void solve() {
    while (1) {
        string s; cin >> s;
        if (s[0] == 'e') break;
        int f = ask(0,1);
        if (f == 1) { out(1); continue; }
        int l = get(), r = l*2;
        while (l+1 < r) {
            int mid = (l+r)>>1;
            int g = ask(l,mid);
            if (g == 2) l = mid; else r = mid;
        }
        out(r);
    }
}

signed main() {
    fast;
    solve();
    return 0;
}