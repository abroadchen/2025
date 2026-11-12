//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
枚举所有连续子串：固定长度 i（1..len），起始 j（0..len-i），用 str 临时拷贝、str[k]='\0' 收尾，再转成 ss（string）。

双重计数去重：mp 是"当前字符串专用"的标记表。每开始一个字符串就 mp.clear()。

if (mp[ss]) continue; → 同一字符串里同一个子串只统计一次（避免 s=“aaa” 这类，多个位置出现同样的 "a" 被重复计数）；若未标记，则打标记、m1[ss]++、m2[ss]=x。
m1[ss] 的含义 = 包含子串 ss 的字符串个数（因为每个字符串里同子串只计一次，跨字符串才累加）。

m2[ss] = x：记录"遇到这个子串时，当前字符串下标 x"。由于 x 从小到大遍历，m2 保存的是第一个包含该子串的字符串下标（只赋值一次，之后即便其他串也含它，m2 仍保留最早那次）
每个查询直接查 m1（数量）和 m2（最早出现字符串下标），O(1) 回答
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
using namespace std;

constexpr int N = 1e4+5;

int n, len, k, m;
char s[N][10], str[10];
map<string,int> mp, m1, m2;
string ss;
int main() {
    fast;
    cin >> n;
    rep(x,1,n) {//枚举每个字符串
        cin >> s[x]; len = strlen(s[x]);
        mp.clear();//每处理一个字符串就清一次 mp
        //i = 子串长度
        rep(i,1,len) rep(j,0,len-i) {//j = 子串起始位置
            for (k = 0; k < i; k++) str[k] = s[x][j+k];//拷贝出该子串
            str[k] = '\0';
            ss = str;
            if (mp[ss]) continue;//当前串内已统计过这个子串 → 跳过
            //在本串中标记 全局：包含该子串的字符串数 +1 记录：第一次（最小 x）出现的字符串
            mp[ss]++; m1[ss]++; m2[ss] = x;
        }
    }
    cin >> m;
    while (m--) {
        cin >> ss;
        cout << m1[ss] << ' ';
        if (m1[ss] == 0) cout << "-\n";
        else cout << s[m2[ss]] << '\n';
    }
    return 0;
}