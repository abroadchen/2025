//
// Created by Psy.C on 2026/10/15.
//
/**
ch 存原字符串（后面会自我拼接翻倍）。
p[c]：对每个字母 c，记录它在原串中出现的所有位置下标。
n 是原串长度
传入 x（某个字符）、d（偏移量）。
遍历字符 x 在原串中出现的每个位置 i，取 ch[i+d]（即偏移 d 后的字符），统计各字符出现次数到 b[]。
最后 ans = 出现次数恰为 1 的字符种数
对该字符 x，枚举偏移 i = 1 .. n-1，取 get(x,i) 的最大值。
t1/t2 = 最大匹配的字符种数 / 字符 x 的出现总次数，这是一个"占比/得分"。
用 bs[x]（字符 x 的相对出现频率）作权重，累加进全局结果 res
先把每个字符位置记录进去，同时统计出现次数 bs[]。
ch[i+n] = ch[i]：把原串复制一份接到后面，长度翻倍到 2n。这样当 get(x,d) 用 ch[i+d] 时，对于 i+d ≥ n 的偏移会绕回到串前部，实现循环移位的效果。
bs[i] /= n：把次数变成占比（频率），和为 1。
对每个出现过的字符跑 solve，把贡献加权累加进 res。
最终输出 res（double，12 位小数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ld long double
using namespace std;

constexpr int N = 1e5+10, M = 26;

int b[30];
vector<int> p[M];
char ch[N];
int get(int x, int d) {
    int ans = 0;
    memset(b, 0, sizeof b);
    for (int i : p[x]) {
        int cur = ch[i+d] - 'a';
        b[cur]++;
    }
    rep(i,M) if (b[i] == 1) ans++;
    return ans;
}

int n;
ld res, bs[N];
void solve(int x) {
    int ans = 0;
    for (int i = 1; i < n; ++i) ans = max(ans, get(x, i));
    ld t1 = ans*1.0, t2 = (ld)p[x].size()*1.0;
    res = res + t1/t2*bs[x];
}

int main() {
    fast;
    cin >> ch; n = strlen(ch);
    rep(i,n) p[ch[i]-'a'].push_back(i), bs[ch[i]-'a']++;
    rep(i,n) ch[i+n] = ch[i];
    rep(i,M) bs[i] = bs[i]/(ld)(n*1.0);
    rep(i,M) if (bs[i] != 0.0) solve(i);
    double ans = res;
    printf("%.12lf\n", ans);
    return 0;
}