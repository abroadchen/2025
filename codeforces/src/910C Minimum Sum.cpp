//
// Created by Psy.C on 2026/10/12.
//
/**
w[c] = 字母 c 出现在所有字符串中的加权位数和。n0[c] 标记 c 是否出现在某个字符串开头
权重：每位累加 10^(位权)
记录首字母（不能为 0）
把所有权重非 0 的字母排成 (权重, 字母)，注意排序升序是权重从小到大
只扫描 a-j 这 10 个字母（假定题目输入里只出现这 10 个字母）。
把出现过的字母连同权重放进 s，按权重升序排序
从权重最大的字母开始（per 反向遍历），
把第一个不出现在任何字符串开头的字母分配成 0（这样 0 用在了权重尽量大的非首字母上，最划算，且不会造成前导 0），
其余字母从 1 开始递增分配。
效果：权重越大的字母拿到越小的数字，从而让总和最小（大权重×小数字）
把每个字符串中的字母逐个替换成映射后的数字字符，再用 stoi 转成整数，累加得到 sum 并输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
using namespace std;

constexpr int N = 1e3+5;

int n;
map<char, int> w, n0, r;
string a[N];
vector<pair<int, char>> s;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> a[i];
        rep(j,a[i].size()) w[a[i][j]] += pow(10, a[i].size()-j-1);
        n0[a[i][0]] = 1;
    }
    rep(i,10) if (w['a'+i] != 0) s.emplace_back(w['a'+i], 'a'+i);
    ranges::sort(s);
    bool sz = 1; int num = 1;
    per(i,s.size()-1,0) {
        if (n0[s[i].second] == 0 && sz == 1) {
            r[s[i].second] = 0; sz = 0;
            continue;
        }
        r[s[i].second] = num;
        num++;
    }
    int sum = 0;
    rep(i,n) {
        for (char& j : a[i]) j = '0' + r[j];
        sum += stoi(a[i]);
    }
    cout << sum << '\n';
    return 0;
}