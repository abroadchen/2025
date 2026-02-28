//
// Created by Psy.C on 2026/2/28.
//
/**
MAX = 6e5 + 5：最大字符串长度
mod, mod2：两个不同的模数（大质数），用于双哈希降低冲突概率
seed, seed2：两个不同的基数，用于字符串哈希
n, m：输入的两个数量
s[MAX]：临时存储字符串的缓冲区
P[MAX], P2[MAX]：预计算的种子幂次（用于哈希计算）
ss, ss2：存储哈希值的集合

初始化P[0]和P2[0]为1
预计算P[i] = seed^i % mod 和 P2[i] = seed2^i % mod2
读入n和m
循环处理n个字符串：
读入字符串s（从索引1开始存储）
计算双哈希值：
Hash：使用seed和mod计算的哈希值
Hash2：使用seed2和mod2计算的哈希值
将哈希值插入对应的集合中
循环处理m个查询字符串
计算当前字符串的双哈希值

遍历可能的目标字符'a'到'c'
遍历当前字符串的每个位置j
如果当前位置已经是目标字符ch，则跳过
否则尝试将位置j的字符改为ch：
(Hash+10*mod + (ch - s[j]) * P[len-j])%mod：计算修改后的哈希值
10*mod是为了避免负数（相当于加若干个mod）
(ch - s[j]) * P[len-j]：计算字符差异对哈希值的影响
P[len-j]：对应位置的幂次（预计算的权重）
检查修改后的哈希值是否存在于已有的哈希集合中
同时检查双哈希确保准确性

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
typedef unsigned ll ull;
const int MAX = 6e5 + 5;
const ll mod = 2000004199, mod2 = 1111111111111;
const ll seed = 131, seed2 = 13331;
int n,m;
char s[MAX];
ull P[MAX],P2[MAX];
set<ull> ss,ss2;
int main() {
    P[0]=P2[0]=1;
    for(int i = 1; i<MAX; i++) P[i] = P[i-1] * seed % mod,P2[i] = P2[i-1] * seed2 % mod2;
    cin>>n>>m;
    for(int i = 1; i<=n; i++) {
        scanf("%s",s+1);
        ull Hash = 0,Hash2 = 0;
        int len = strlen(s+1);
        for(int j = 1; j<=len; j++) Hash = (Hash*seed + s[j]-'a'+1)%mod,Hash2 = (Hash2*seed2+s[j]-'a'+1)%mod2;
        ss.insert(Hash);
        ss2.insert(Hash2);
    }
    for(int i = 1; i<=m; i++) {
        scanf("%s",s+1);
        ull Hash=0,Hash2 = 0;
        int len = strlen(s+1),flag = 0;
        for(int j = 1; j<=len; j++) Hash = (Hash*seed + s[j]-'a'+1)%mod,Hash2 = (Hash2*seed2+s[j]-'a'+1)%mod2;
        for(char ch = 'a'; ch<='c'; ch++) {
            for(int j = 1; j<=len; j++) {
                if(s[j] == ch) continue;
                if(ss.contains((Hash+10*mod + (ch - s[j]) * P[len-j])%mod) &&
                    ss2.contains((Hash2+10*mod2+(ch-s[j])*P2[len-j])%mod2)) {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 1) puts("YES");
        else puts("NO");
    }
    return 0;
}