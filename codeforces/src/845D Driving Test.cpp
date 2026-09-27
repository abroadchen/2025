//
// Created by Psy.C on 2026/9/27.
//
/**
ans：累计的违规计数（最终输出）。
cnt：一段连续"禁止超车"等状态下的计数。
v：当前车速。
lim：当前限速，初值 inf（无穷大，表示无限制）。
s：栈，用来保存历史车速/限速设置，用于判断是否违规
逐条读入指令类型 t，下面分别处理。

指令 1：设定新速度
读入新的当前车速 v。
若这个新速度 v 大于栈顶（曾经设置的限速 s.top()），说明超速了，累加违规 ans++，并把栈顶弹出。循环检查直到不再超速。
含义：车速一旦超过先前某个限速，就算一次违规，并把那条限速从栈里清除
指令 2：结束某个状态
此时把累计的 cnt 全部计入违规 ans，再清零 cnt。
含义：某段"被禁止/超车"状态结束，把期间累计的违规数一次性结算。
指令 3：设置限速
读入新限速 lim。
若当前车速 v 已经大于该限速 → 直接违规 ans++；
否则把该限速 lim 压入栈 s（后续超速时由指令 1 弹出并计数）。
指令 4：清除违规计数
把 cnt 清零（重置某段累计计数，例如"超车完成"）。
指令 5：清除所有限速
重置限速为无限制 inf，并清空整个栈（撤销所有之前设置的限速）。
指令 6：累加计数
cnt++：累计一段违规（如"禁止超车路段里每次超车"）。
最终输出总的违规次数 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int inf = 0x3f3f3f3f;

int ans, cnt, v, lim(inf);
stack<int> s;
int main() {
    fast;
    int n, t; cin >> n;
    while (n--) {
        cin >> t;
        if (t == 2) { ans += cnt; cnt = 0; }
        else if (t == 4) cnt = 0;
        else if (t == 6) cnt++;
        else if (t == 1) {
            cin >> v;
            while (!s.empty() && v > s.top()) { s.pop(); ans++; }
        }
        else if (t == 5) {
            lim = inf;
            while (!s.empty()) s.pop();
        }
        else if (t == 3) {
            cin >> lim;
            if (v > lim) ans++;
            else s.push(lim);
        }
    }
    cout << ans << '\n';
    return 0;
}