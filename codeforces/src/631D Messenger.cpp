//
// Created by Psy.C on 2026/3/29.
//
/**
构建KMP算法的next数组
同时考虑字符和计数两个维度
在主串中查找模式串的匹配位置
同时匹配字符和计数

 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e6+5;

int nxt[N];
int get(char *s, ll *c, int n) {
    nxt[1] = 0;
    for (int i = 2, j; i <= n; ++i) {
        j = nxt[i-1];
        while (j && (s[i] != s[j+1] || c[i] != c[j+1]))
            j = nxt[j];
        if (s[i] == s[j+1] && c[i] == c[j+1]) j++;
        nxt[i] = j;
    }
    return 0;
}
int pos[N];
int kmp(char *s, ll *c1, char *t, ll *c2, int n, int m) {
    int c = 0;
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j && (s[i] != t[j+1] || c1[i] != c2[j+1]))
            j = nxt[j];
        if (s[i] == t[j+1] && c1[i] == c2[j+1]) j++;
        if (j == m) pos[++c] = i - m + 1, j = nxt[j];
    }
    return c;
}

///将输入的 "字符数量" 序列解析为字符和计数数组
///自动合并连续相同的字符
int Get(char *s, ll *c, int m) {
    int n = 0;
    while (m--) {
        n++;
        scanf("%lld-%c", &c[n], &s[n]);
        if (n > 1 && s[n] == s[n-1])
            c[n-1] += c[n], n--;
    }
    return n;
}

int n, m;
ll cs[N], ct[N];
char s[N], t[N];
int main() {
    scanf("%d%d", &n, &m);
    n = Get(s, cs, n), m = Get(t, ct, m);
    if (n < m) return !printf("0\n");//主串太短
    if (m == 1) {//模式串长度为1
        ll ans = 0;
        for (int i = 1; i <= n; ++i)
            if (s[i] == t[1])
                ans += max(0ll, cs[i]-ct[1]+1);
        printf("%lld\n", ans);
        return 0;
    }
    if (m == 2) {//模式串长度为2
        int ans = 0;
        for (int i = 1; i < n; ++i)
            if (s[i] == t[1] && s[i+1] == t[2])
                ans += (cs[i] >= ct[1] && cs[i+1] >= ct[2]);
        printf("%d\n", ans);
        return 0;
    }
    //模式串长度≥3
    get(t + 1, ct + 1, m - 2);//对模式串的中间部分构建next数组
    int c = kmp(s, cs, t + 1, ct + 1, n, m-2), ans = 0;//在主串中匹配模式串的中间部分
    for (int i = 1; i <= c; ++i) {
        int x = pos[i] - 1, y = pos[i] - 1 + m - 1;//计算首尾位置
        if (!x || y > n) continue;//边界检查
        if (s[x] != t[1] || s[y] != t[m]) continue;//首尾字符匹配
        if (cs[x] >= ct[1] && cs[y] >= ct[m]) ans++;//首尾计数足够
    }
    printf("%d\n", ans);
    return 0;
}