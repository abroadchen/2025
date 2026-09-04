//
// Created by Psy.C on 2026/9/4.
//
/**
k[4]：长度为 4 的数组，k[0..3] 分别统计四种颜色槽位上 !（缺失）的个数，最后按 R、B、Y、G 顺序输出。
s：读入的字符串。
mp：map<int,int>，把"位置模 4 的余数"映射到"颜色编号"。即 mp[i%4] = 位置
i
i 对应的颜色代号
遍历每个位置
i
i。
条件 s[i] != '!' && s[i] == 'R' 意思是：该位置不是缺失的 !，而且确实是字母 R（这个 s[i] != '!' 其实是冗余的，因为 s[i]=='R' 本身就不是 !，写作习惯）。
若该位置是 R，则 mp[i%4] = 0，即"所有位置模 4 等于 i%4 的槽位都属于 R"，颜色编号 0。
同理 B→1、Y→2、G→3
再次遍历所有位置。
只有 s[i] == '!'（该位置缺失）时才计数。
这个缺失位置所属的槽位余数是 i%4，它在 mp 里对应的颜色编号是 mp[i%4]，于是 k[mp[i%4]]++ 就是"该颜色对应的缺失数量 +1"。
循环结束后，k[0..3] 分别统计了 R、B、Y、G 四种颜色各自缺失的 ! 个数
前三个数每个后面跟一个空格：k[0] k[1] k[2] 。
最后一个 k[3] 后跟换行 '\n'，避免行尾多余空格
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int k[4];
string s;
map<int, int> mp;
int main() {
    fast;
    cin >> s;
    int len = s.size();
    memset(k, 0, sizeof(k));
    for (int i = 0; i < len; ++i) {
        if (s[i] != '!' && s[i] == 'R') mp[i%4] = 0;
        if (s[i] != '!' && s[i] == 'B') mp[i%4] = 1;
        if (s[i] != '!' && s[i] == 'Y') mp[i%4] = 2;
        if (s[i] != '!' && s[i] == 'G') mp[i%4] = 3;
    }
    for (int i = 0; i < len; ++i)
        if (s[i] == '!') k[mp[i%4]]++;
    for (int i = 0; i < 3; ++i) cout << k[i] << ' ';
    cout << k[3] << '\n';
    return 0;
}