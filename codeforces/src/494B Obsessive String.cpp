//
// Created by Psy.C on 2026/2/19.
//
/**
dp[i]：以位置i结尾的匹配方案数
sum[i]：dp[0]到dp[i]的前缀和
tag[i]：以位置i结尾的匹配的起始位置（如果没有匹配则为0）
dp[i-1]：不考虑以位置i结尾的匹配
sum[tag[i]-1]：在当前位置匹配之前的所有方案数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+1, mod = 1e9+7;


void get(char p[], int nxt[]) {
    ///i: 当前处理位置
    ///k: 最长相等前后缀长度
    int i = 0, k = -1;
    const int len = strlen(p);//模式串p的长度
    nxt[0] = -1;
    while (i < len) {
        //没有相等前后缀 找到更长的相等前后缀
        if (k == -1 || p[i] == p[k])//当前字符匹配
            i++, k++, nxt[i] = k;//前进并更新
        else k = nxt[k];//回退到nxt[k]位置
    }
}

int tag[N];//以位置i结尾的模式串匹配的起始位置
void match(char s[], char p[]) {
    int nxt[N]; get(p, nxt);
    //文本串长度 模式串长度
    const int l1 = strlen(s), l2 = strlen(p);
    int i = 0, j = 0;//文本串指针 模式串指针
    while (i < l1) {//文本串中查找模式串
        //匹配成功或j回退到-1
        if (j == -1 || s[i] == p[j]) i++, j++;
        else j = nxt[j];//回退
        //模式串完全匹配：记录匹配的起始位置
        if (j == l2) tag[i] = i - l2 + 1;
    }
}

char s[N], t[N];
int sum[N], dp[N];
int main() {
    fast;
    cin >> s >> t; match(s, t);
    sum[0] = dp[0] = 0;
    const int n = strlen(s);
    for (int i = 1; i <= n; ++i) if (!tag[i])//位置i没有匹配
        tag[i] = tag[i-1];//延续前一个位置的匹配起始位置
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i-1];
        const int l = tag[i];//获取匹配起始位置
        if (!l) continue;
        // l位置之前的方案数  l: 起始位置的贡献
        dp[i] += (sum[l-1] + l) % mod; dp[i] %= mod;
        sum[i] = sum[i-1] + dp[i]; sum[i] %= mod;
    }
    cout << dp[n] << '\n';
    return 0;
}