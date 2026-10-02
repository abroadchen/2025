//
// Created by Psy.C on 2026/10/2.
//
/**
ask(s)：向交互器发送一个长度为 n 的 01 串 s，返回匹配某规则的特殊节点个数（"? " 是交互标记）。
query(l,r)：构造一个串，在 [l,r] 区间全为 '1'、其余全为 '0'，然后调用 ask。
关键公式 ( (r-l+1) + cnt - ask() ) / 2：
设两个特殊节点位置为整形参数。cnt = 全 '0' 串的 ask 结果（即初始特殊节点个数）。
通过区间置 1 的增量差，二分求出 [l,r] 内含特殊节点个数。
这是交互题的常见套路：用"把区间置 1 后返回值相对全 0 的变化"折算出区间内特殊点个数
用二分在数组上找两个特殊节点的位置 p 和 p1。
每次查左半 [l, mid] 里特殊节点的个数 x：
若 x>0 且 x != len（不是整个区间全为特殊点）→ 特殊点在左半，收缩 r=mid；
否则（x==0 或 x==满格）走另一分支，更新 l=mid+1。
p / p1 分别记录两个找到的特殊节点下标；p 存 x 为 1 那边，p1 存另一情况。
循环到 l==mid（单点）时直接判定特殊点归属并 break。
最后兜底：若漏掉，补 p=l、p1=l，然后输出 ! p p1（交互答案）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,a,b) for (int i=a;i<=b;++i)
using namespace std;

inline int ask(const string& s) {
    cout << "? " << s << endl;
    int res; cin >> res;
    return res;
}

int n, cnt;
inline int query(int l, int r) {
    string s;
    rep(i,1,l-1) s.push_back('0');
    rep(i,l,r) s.push_back('1');
    rep(i,r+1,n) s.push_back('0');
    return (r-l+1+cnt-ask(s))/2;
}

inline void out(int x, int y) {
    cout << "! " << x << ' ' << y << '\n';
}

void solve() {
    string s;
    rep(i,1,n) s.push_back('0'); cnt = ask(s);
    int l = 1, r = n, p = 0, p1 = 0;
    while (l < r) {
        int mid = (l+r)>>1, x = query(l, mid);
        if (l == mid) {
            if (x) {
                if (!p1) p1 = l;
                if (!p) p = r;
            } else {
                if (!p1) p1 = r;
                if (!p) p = l;
            }
            break;
        }
        if (x && x != mid-l+1) r = mid;
        else {
            if (!x) p = l; else p1 = l;
            l = mid+1;
        }
    }
    if (!p) p = l;
    if (!p1) p1 = l;
    out(p, p1);
}


int main() {
    fast;
    cin >> n; solve();
    return 0;
}