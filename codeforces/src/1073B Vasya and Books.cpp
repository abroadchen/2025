//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
n：元素个数。
st[]：入栈序列（也是辅助的"序列栈"），兼作模拟栈。
top：栈/序列指针。
vis[]：标记元素"是否仍可被弹出（尚未用到/已被访问）"。
b：每次读入的要弹出的目标元素；num：本次弹栈弹出的元素个数。
top 初始为 1，指向栈针位置（序列指针），指向"下一个还没匹配过的入栈元素"。
读入目标 b。
如果 b 还有效（vis[b]）：
从 top 开始往右走，跳过所有不等于 b 的元素（把那些元素标记为已弹出 vis=0 并计数），直到遇到 b。
弹出 b 本身（vis=0），top 后移一位，num +1。
输出的 num 就是"从指针位置走到并弹出 b 所经过/弹出的元素数"。
如果 b 已经被弹出过（vis[b]==0），本次不弹新元素，num=0
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;

constexpr int N = 2e5+1e4;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, st[N], top, b, num;
bool vis[N];
int main() {
    fast;
    n = rd();//读元素个数
    rep(i,n) st[i] = rd(), vis[i] = 1;//读入栈序列，全部标为"可访问"
    top = 1;
    rep(i,n) {
        b = rd(); num = 0;//读当前要弹出的元素 b
        if (vis[b]) {//若 b 还没被弹出过
            // 一直向前走，直到栈顶 == b；沿途把经过的元素标记为"已弹出"并计数
            while (st[top] != b) { vis[st[top++]] = 0; num++; }
            vis[st[top++]] = 0;//弹出 b 本身
            num++;
        }
        cout << num << ' ';
    }
    return 0;
}