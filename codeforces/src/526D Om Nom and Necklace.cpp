//
// Created by Psy.C on 2026/3/2.
//
/**
j = nxt[i]：获取前一个位置的最长公共前后缀长度
while (j && s[i] != s[j]) j = nxt[j]：失配时回退
if (s[i] == s[j]) j++; else j = 0：匹配时前进，失配时重置
nxt[i+1] = j：更新next数组

计算最小周期：siz = i+1-nxt[i+1]是最小重复单元的长度
判断是否整除：(i+1)%siz == 0判断字符串长度是否能被周期整除
计算重复次数：r = (i+1)/siz是重复单元的个数
条件判断：
如果整除：if (r/k >= r%k)（商≥余数）
如果不整除：if (r/k > r%k)（商>余数）
更新结果：满足条件时ans[i] = 1

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+1;
int n, k, len, nxt[N], j, ans[N];
char s[N];
int main() {
    fast;
    cin >> n >> k >> s; len = strlen(s);
    nxt[0] = 0; j = 0;
    if (k == 1) ans[0] = 1;
    for (int i = 1; i < len; ++i) {
        j = nxt[i];
        while (j && s[i] != s[j]) j = nxt[j];
        if (s[i] == s[j]) j++; else j = 0;
        nxt[i+1] = j;
        int siz = i+1-nxt[i+1];
        if ((i+1)%siz == 0) {
            int r = (i+1)/siz;
            if (r/k >= r%k) ans[i] = 1;
        } else {
            int r = (i+1)/siz;
            if (r/k > r%k) ans[i] = 1;
        }
    }
    for (int i = 0; i < len; ++i) cout << ans[i];
    cout << '\n';
    return 0;
}