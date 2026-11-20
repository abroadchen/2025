//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
读入 n、字符串 s，前面加个 ' ' 使下标从 1 开始；
cnt['0'/'1'/'2'] 统计当前每种字符的出现次数
第一段：处理 '2' 过多（从左到右，把 2 换成 0 或 1）
当 '2' 数量超过 m：从左到右扫描，把靠前（高位）的 '2' 换掉。
优先换成还缺的 '0'（更小、使字典序更小）；
若 0 够了再换成 '1'。
更新计数
第二段：处理 '0' 过多（从右到左，把 0 换成 2 或 1）
当 '0' 数量超过 m：从右往左（末尾）把 '0' 换掉——把靠后（低位）的换走对字典序影响最小。
优先换成缺的 '2'（因为 2 靠后放更好，不破坏前段 dic 序）；
否则换 '1'。
第三段：处理 '1' 过多（左右夹击）
当 '1' 数量超过 m：左指针 l 从前往后、右指针 r 从后往前同时扫。
前面（靠左）多出的 '1' 优先换成缺的 '0'（更小，字典序更小）；
后面（靠右）多出的 '1' 优先换成缺的 '2'（更大，放在末尾不影响字典序优先位）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 105;

int n, m, cnt[N];
string s;
int main() {
    fast;
    cin >> n; m = n/3;
    cin >> s; s = ' ' + s;
    for (int i = 1; i <= n; ++i) ++cnt[(int)s[i]];
    for (int i = 1; cnt['2'] > m && i <= n; ++i) if (s[i] == '2') {
        if (cnt['0'] < m) s[i] = '0', ++cnt['0'], --cnt['2'];
        else if (cnt['1'] < m) s[i] = '1', ++cnt['1'], --cnt['2'];
    }
    for (int i = n; cnt['0'] > m && i; --i) if (s[i] == '0') {
        if (cnt['2'] < m) s[i] = '2', ++cnt['2'], --cnt['0'];
        else if (cnt['1'] < m) s[i] = '1', ++cnt['1'], --cnt['0'];
    }
    for (int l = 1, r = n; cnt['1'] > m && r; ++l, --r) {
        if (s[l] == '1' && cnt['0'] < m) s[l] = '0', ++cnt['0'], --cnt['1'];
        if (s[r] == '1' && cnt['2'] < m) s[r] = '2', ++cnt['2'], --cnt['1'];
    }
    cout << s << '\n';
    return 0;
}