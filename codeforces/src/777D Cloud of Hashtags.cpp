//
// Created by Psy.C on 2026/9/11.
//
/**
读入 n 个字符串，s[1..n]。
s[i] 是原始字符串
base case：ans[n] = s[n]（最后一个直接用原串，因为后面没约束）。
对 i 从 n-1 到 1（从后往前）：
若 s[i] <= ans[i+1]：直接 ans[i] = s[i]。
否则（s[i] > ans[i+1]，字典序比后一个更大）：找到第一个使 s[i][j] > ans[i+1][j] 的位置 p，然后 ans[i] = s[i] 的前 p 个字符（即截断做前缀，去掉从 p 开始的后缀）
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5+1;
char c[N];
string s[N], ans[N];
int n;
int main() {
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++) {
        scanf("%s",c);
        s[i].assign(c);
    }
    ans[n]=s[n];
    for (i=n-1;i>=1;i--) {
        if (s[i]<=ans[i+1]) {
            ans[i]=s[i];
            continue;
        }
        int j,p;
        for (j=0;j<s[i].size();j++)
            if (s[i][j]>ans[i+1][j]) {
                p=j;
                break;
            }
        ans[i]="";
        for (int k=0;k<p;k++) ans[i]+=s[i][k];
    }
    for (i=1;i<=n;i++) printf("%s\n",ans[i].c_str());
    return 0;
}