//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
N=505：d 的上界（余数范围 0..d-1，≤500）。
M=5005：s 的上界（数位和，≤5000）。
struct node：一个搜索状态：
mod：当前已构造数字对 d 的余数。
sum：当前数位和。
s：当前已构造的数字字符串（BFS 用的路径记录）
v[N][M]：v[mod][sum] = 该状态已被访问（去重数组）。
s：目标数位和。
d：模数
初始化：起始状态 (mod=0, sum=0, s="") 入队，v[0][0]=1 标记。
BFS 循环：
取队头 now。
if (now.sum > s) continue：数位和已超过目标 s，剪枝，跳过。
if (now.mod==0 && now.sum==s) return now.s：找到余数为 0 且数位和等于 s 的目标状态，返回当前构造的字符串。
枚举下一数字 i=0..9：
nxt.mod = (now.mod*10+i) % d：新余数 = 当前余数左移一位（×10）加上新数字 i，再对 d 取模。
nxt.sum = now.sum + i：新数位和 += i。
若该状态未访问 !v[nxt.mod][nxt.sum]：记录字符串 now.s + char('0'+i)，入队，并标记已访问。
队列空仍未找到 → 返回 "-1"（无解）
读入 d、s。
调用 bfs() 并把返回的字符串输出（结果或 "-1"）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 505, M = 5005;

struct node { int mod, sum; string s; };

int v[N][M], s, d;
string bfs() {
    queue<node> q;
    node now, nxt; now.mod = 0; now.sum = 0; now.s = ""; q.push(now);
    v[0][0] = 1;
    while (!q.empty()) {
        now = q.front(); q.pop();
        if (now.sum > s) continue;
        if (now.mod == 0 && now.sum == s) return now.s;
        for (int i = 0; i <= 9; i++) {
            nxt.mod = (now.mod*10+i)%d; nxt.sum = now.sum + i;
            if (!v[nxt.mod][nxt.sum]) {
                nxt.s = now.s + (char)('0'+i); q.push(nxt);
                v[nxt.mod][nxt.sum] = 1;
            }
        }
    }
    return "-1";
}


int main() {
    fast;
    cin >> d >> s;
    cout << bfs() << '\n';
    return 0;
}