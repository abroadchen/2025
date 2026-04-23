//
// Created by Psy.C on 2026/4/23.
//
/**
l：长度限制
n：操作次数
p：周期参数
t：时间间隔
st, ed：队列的起始和结束指针
ans：答案
初始化队列，q[0] = {0, -inf}
st ? --st : 1：如果st不为0则减1，否则设为1
在单调队列中寻找最优解
q[st].g + p + t > y：检查是否满足条件
计算新的f值和g值：
ff：新f值 = 原f值 + (y - max(原g+t, x)) / p
gg：新g值 = y - (y - max(原g+t, x)) % p
更新最优解（f值更大或f值相等但g值更小）
移动队列指针
如果当前结果更优，更新答案
将当前结果加入队列尾部
!printf(...) 利用printf返回值（输出字符数）取反来返回0
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5+7, inf = 0x3f3f3f3f;

struct node { int f, g; } q[N];//单调队列数组
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
int l, n, p, t, st, ed, ans;
int main() {
    l = rd(), n = rd(), p = rd(), t = rd();
    q[0] = {0, -inf};
    while (n--) {
        int x = rd(), y = rd(), res = 0, ng = 0;
        st ? --st : 1;
        while (st <= ed) {
            if (q[st].g + p + t > y) break;
            int ff = q[st].f + (y - max(q[st].g + t, x)) / p,
            gg = y - (y - max(q[st].g + t, x)) % p;
            if (ff > res || ff == res && gg < ng)
                res = ff, ng = gg;
            ++st;
        }
        if (ans < res) {
            ans = res;
            q[++ed] = {res, ng};
        }
    }
    return !printf("%d\n", ans);
}