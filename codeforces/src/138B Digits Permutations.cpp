//
// Created by Psy.C on 2025/11/20.
//
/*
*u: 最佳起始数字对（初始为0）
t: 临时最小差值计数（初始为5）
m: 当前最小差值计数（初始为5）
p, q: 数字0-9的频率数组（都初始化为0）
 *
*统计输入字符串中每个数字的出现次数并存储在p中
将这些频率复制到q中供后续使用
*对于数字1-5，寻找互补的数字对（相加等于10）
计算这些数字对在最小化差值方面的效果
记录最佳起始数字u
*如果找到了起始数字对，减少它们在频率数组中的计数
处理零的特殊情况：确保第二个数字的前导零不会超过九的数量
*如果存在起始数字对，将其放在开头
优化配对剩余数字以保持两数接近
尽可能使用互补数字（相加等于9）
*放置任何未配对的剩余数字
第一个数字放置较小的数字，第二个数字放置较大的数字
 */
#include <algorithm>
#include <iostream>
#define rep(i,n) for(int i=0;i<n;++i)
#define rep1(i,n) for(int i=1;i<=n;++i)
#define upd(a,b) p[a]--, q[b]--;//将数组p中数字a的计数减1，数组q中数字b的计数减1
using namespace std;

const int N = 1e5+5;
int a[N], b[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s;
    int u(0), t(5), m(5), p[10]={0}, q[10]={0};
    rep(i,s.size()) p[s[i] - '0']++;
    rep(i,10) q[i] = p[i];
    rep1(i,5) {
        if (p[i] && p[10-i]) t = (p[i]==min(p[i],p[9-i])) +
            (p[10-i]==min(p[10-i],p[i-1]));
        if (t < m) { m = t; u = i; }
    }
    if (u) upd(u, 10-u);
    int d = s.size();
    while (q[0] > q[9]) { d--; upd(0, 0); }
    if (u) {
        a[--d] = u, b[d] = 10 - u;
        rep(i,5) {
            while (p[i] && q[9-i]) { a[--d]=i;b[d]=9-i;upd(i, 9-i); }
            while (p[9-i] && q[i]) { a[--d]=9-i;b[d]=i;upd(9-i, i); }
        }
    }
    rep1(i,9) rep(j,p[i]) a[--d] = i;
    rep1(i,9) rep(j,q[i]) b[d++] = i;
    rep(i,s.size()) cout << a[i]; cout << '\n';
    rep(i,s.size()) cout << b[i];
    return 0;
}