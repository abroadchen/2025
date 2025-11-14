//
// Created by Psy.C on 2025/11/14.
//
/*
*z：Z数组，z[i]表示从位置i开始的子串与原字符串前缀的最长公共前缀长度
l, r：维护当前最右的匹配区间[left, right)
*从位置1开始遍历（位置0的Z值总是字符串长度，这里省略）
如果当前位置i在已知匹配区间内，则可以利用已有信息：
z[i-l]是从位置0开始的对应位置的Z值
r-i是到区间右边界的距离
取两者较小值作为初始Z值
*暴力扩展匹配：从当前Z值开始继续比较字符
如果字符相等则Z值增加，直到不匹配或到达字符串末尾
*如果当前匹配超过了之前的最右边界，则更新匹配区间
返回计算得到的Z数组
 *
 *主字符串s，模式串a，模式串b
 *对每个位置i，计算从该位置到字符串末尾的子串的Z数组
*ga：标记数组，ga[i]=1表示从位置i开始匹配模式串a
gb：标记数组，gb[i]=1表示从位置i开始匹配模式串b
*sf：后缀和数组，sf[i]表示从位置i到末尾有多少个位置匹配模式串b
从右到左计算后缀和，用于快速查询区间内的匹配数量
 *
*遍历所有在位置i之前的匹配位置j
如果位置j也匹配模式串a，则计算两个匹配之间的最大重叠长度
z[j][i-j]表示从位置j开始的后缀与原字符串前缀在位置i-j处的匹配长度
 *
*计算从位置i开始，考虑重叠后能够放置模式串b的位置数量
mx - sz(b) + 1：考虑重叠后的有效长度
max(0, ...)：确保不为负数
i + ...：计算起始位置
min(n, ...)：确保不超过字符串长度
通过后缀和数组快速查询符合条件的b模式串数量
 *
 */
#include <vector>
#include <iostream>
#include <algorithm>
#define sz(a) ((int)(a).size())
#define rep(i,n) for(int i=0;i<=(n);++i)
using namespace std;


vector<int> f(string s) {
    int n = s.size();
    vector<int> z(n);
    int l(0), r(0);
    for (int i = 1; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, a, b; cin >> s >> a >> b;
    int n = sz(s);
    vector<vector<int>> z(n);
    rep(i,n-1) z[i] = f(s.substr(i, n - i));
    vector<int> ga(n), gb(n);
    rep(i,n-sz(a)) ga[i] = a == s.substr(i, sz(a));
    rep(i,n-sz(b)) gb[i] = b == s.substr(i, sz(b));
    vector<int> sf(n + 1);
    for (int i = n - 1; i >= 0; --i) sf[i] = sf[i + 1] + gb[i];
    int ans = 0;
    rep(i,n-1) {
        if (!ga[i]) continue;//如果位置i不匹配模式串a则跳过
        int mx = sz(a) - 1;
        rep(j,i-1) {
            if (!ga[j]) continue;
            mx = max(mx, z[j][i - j]);
        }
        ans += sf[min(n, i + max(0, mx - sz(b) + 1))];
    }
    cout << ans << '\n';
    return 0;
}