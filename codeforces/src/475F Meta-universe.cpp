//
// Created by Psy.C on 2026/2/15.
//
/**
ibuf[RL]: 缓冲区数组
*ib: 输入缓冲区指针
*ob: 输出缓冲区指针
*ob==ib: 检查缓冲区是否已用完
fread(ibuf, 1, RL, stdin): 从stdin读取RL字节到ibuf
(ib=ibuf)+fread(...): 设置ib指向buf开头，ob指向读取结束位置
&& 短路运算：只有当缓冲区用完时才执行读取
如果ob==ib（缓冲区空），返回EOF
否则返回当前字符并移动指针

(res + (res<<2))<<1: res + res4 = 5res, 然后乘2 = 10*res

lx: st1中X坐标最小的点
ly: st2中Y坐标最小的点
rx: st1中X坐标最大的点（反向迭代器）
ry: st2中Y坐标最大的点（反向迭代器）

遍历st1中的相邻X坐标
pre: 当前X坐标
now: 下一个X坐标
如果相邻X坐标差>1，说明存在间隙
创建新集合st3, st4
将X坐标≤pre的所有点移到新集合中
同时更新两个set
递归计算两部分的连通分量数

检查X轴最大→最小方向
检查Y轴最小→最大方向
检查Y轴最大→最小方向
 */
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;

constexpr int RL = 1<<20|1;
inline char gc() {
    static char ibuf[RL], *ib, *ob;
    ob==ib && (ob=(ib=ibuf)+fread(ibuf, 1, RL, stdin));
    return ob == ib ? EOF : *ib++;
}
inline int read() {
    char ch = gc();
    int res = 0, f = 1;
    while (!isdigit(ch)) f ^= ch == '-', ch = gc();
    while (isdigit(ch)) res = ((res + (res<<2))<<1) + (ch&15), ch = gc();
    return f ? res : -res;
}

///用于坐标轴转换（X↔Y）
inline ii swp(const ii& x) { return {x.second, x.first}; }

inline int dfs(set<ii>& st1, set<ii>& st2) {
    if (st1.size() == 1) return 1;//只有一个点，返回1（一个连通分量）
    auto lx = st1.begin(), ly = st2.begin();
    auto rx = st1.rbegin(), ry = st2.rbegin();
    auto ed = st1.end(); --ed;//获取st1的最后一个元素
    while (lx != ed) {
        int pre = lx->first;
        int now; ++lx, now = lx->first;
        if (now - pre > 1) {
            set<ii> st3, st4;
            while (st1.begin()->first <= pre) {
                ii xx = *st1.begin();
                st3.insert(xx), st4.insert(swp(xx));
                st1.erase(xx), st2.erase(swp(xx));
            }
            return dfs(st3, st4) + dfs(st1, st2);
        }
        pre = rx->first; ++rx, now = rx->first;
        if (pre - now > 1) {
            set<ii> st3, st4;
            while (st1.rbegin()->first >= pre) {
                ii xx = *st1.rbegin();
                st3.insert(xx), st4.insert(swp(xx));
                st1.erase(xx), st2.erase(swp(xx));
            }
            return dfs(st3, st4) + dfs(st1, st2);
        }
        pre = ly->first; ++ly, now = ly->first;
        if (now - pre > 1) {
            set<ii> st3, st4;
            while (st2.begin()->first <= pre) {
                ii xx = *st2.begin();
                st3.insert(swp(xx)), st4.insert(xx);
                st1.erase(swp(xx)), st2.erase(xx);
            }
            return dfs(st3, st4) + dfs(st1, st2);
        }
        pre = ry->first; ++ry, now = ry->first;
        if (pre - now > 1) {
            set<ii> st3, st4;
            while (st2.rbegin()->first >= pre) {
                ii xx = *st2.rbegin();
                st3.insert(swp(xx)), st4.insert(xx);
                st1.erase(swp(xx)), st2.erase(xx);
            }
            return dfs(st3, st4) + dfs(st1, st2);
        }
    }
    return 1;//连通的
}
constexpr int N = 100005;
set<ii> st1, st2;
int n;//点的数量
ii p[N];//存储原始点
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        p[i].first = read(), p[i].second = read();
        st1.insert(p[i]);
        st2.insert(swp(p[i]));
    }
    cout << dfs(st1, st2) << '\n';
    return 0;
}