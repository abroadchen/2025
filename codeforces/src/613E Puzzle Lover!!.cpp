//
// Created by Psy.C on 2026/3/24.
//
/**
has1[], has2[]: 存储双哈希值
init(): 初始化字符串哈希
query(l,r): 查询子串哈希值
S: 目标字符串哈希
pre[2], suf[2]: 两个输入字符串的前缀和后缀哈希
f[2][N][N]: DP状态数组
n, m: 两个输入串长度和目标串长度
a[2][N]: 两个输入字符串
f[0][i][j]: 表示在位置i，当前匹配了s的前j个字符，且当前位置在第一个字符串上的方案数
f[1][i][j]: 类似，但当前位置在第二个字符串上

k*2<=m: 确保k+k不超过目标串长度
k<=i: 确保有足够的字符
!dir||k*2!=m: 特殊条件下避免重复计算
检查：后缀k个字符是否匹配s[1..k]，前缀k个字符是否匹配s[k+1..2k]
这部分处理的是在位置i处完成了一个长度为2k的匹配

匹配长度为0的状态总是可达的（表示尚未开始匹配）
检查中间段是否完成了目标串的后半部分匹配
将已完成的方案数加到结果中

单字符转移：当前位置的字符与目标串下一字符匹配
双字符转移：当前位置的两个字符（交叉）与目标串下两个字符匹配
将在位置i完成完整匹配的方案数加到结果中

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int mod = 1e9+7;
void add(int &a, int b) {
    (a += b) >= mod ? a -= mod : 0;
}
void sub(int &a, int b) {
    (a -= b) < 0 ? a += mod : 0;
}
constexpr int N = 2005, bas1 = 1331, mod1 = 1920643713, bas2 = 233, mod2 = 771939933;
int pw1[N], pw2[N];
void init() {
    pw1[0] = pw2[0] = 1;
    for(int i=1;i<N;i++)
        pw1[i]=1ll*pw1[i-1]*bas1%mod1,pw2[i]=1ll*pw2[i-1]*bas2%mod2;
}
struct Hash {
    int has1[N],has2[N];

    void init(char *s){
        for(int i=1,len=strlen(s+1);i<=len;i++)
            has1[i]=(1ll*has1[i-1]*bas1+s[i]-'a'+1)%mod1,
            has2[i]=(1ll*has2[i-1]*bas2+s[i]-'a'+1)%mod2;
    }

    ii query(int l,int r){
        return {((has1[r]-1ll*has1[l-1]*pw1[r-l+1])%mod1+mod1)%mod1,
            ((has2[r]-1ll*has2[l-1]*pw2[r-l+1])%mod2+mod2)%mod2};
    }
} S, pre[2], suf[2];

bool operator==(const ii& a, const ii& b) {
    return a.first == b.first && a.second == b.second;
}

int f[2][N][N], n, m;
char a[2][N];
int get(const char *s, int dir) {
    memset(f, 0, sizeof f);
    int res = 0;
    for (int i = 0; i <= n; i++) {
        for(int k=2;k*2<=m&&k<=i;k++)if(!dir||k*2!=m){
            if(suf[0].query(n-i+1,n-i+k)==S.query(1,k)&&
                pre[1].query(i-k+1,i)==S.query(k+1,2*k))add(f[1][i][2*k],1);
            if(suf[1].query(n-i+1,n-i+k)==S.query(1,k)&&
                pre[0].query(i-k+1,i)==S.query(k+1,2*k))add(f[0][i][2*k],1);
        }
        f[0][i][0]=1,f[1][i][0]=1;
        for(int k=2;2*k<=m&&i+k<=n;k++)if(!dir||k*2!=m){
            if(pre[0].query(i+1,i+k)==S.query(m-2*k+1,m-k)&&
                suf[1].query(n-i-k+1,n-i)==S.query(m-k+1,m))add(res,f[0][i][m-2*k]);
            if(pre[1].query(i+1,i+k)==S.query(m-2*k+1,m-k)&&
                suf[0].query(n-i-k+1,n-i)==S.query(m-k+1,m))add(res,f[1][i][m-2*k]);
        }
        for(int j=0;j<m;j++){
            if(a[0][i+1]==s[j+1])add(f[0][i+1][j+1],f[0][i][j]);
            if(a[1][i+1]==s[j+1])add(f[1][i+1][j+1],f[1][i][j]);
            if(j+2<=m){
                if(a[1][i+1]==s[j+1]&&a[0][i+1]==s[j+2])add(f[0][i+1][j+2],f[1][i][j]);
                if(a[0][i+1]==s[j+1]&&a[1][i+1]==s[j+2])add(f[1][i+1][j+2],f[0][i][j]);
            }
        }
        add(res, f[0][i][m]), add(res, f[1][i][m]);
    }
    return res;
}

char s[N];
int ans;
int main() {
    fast; init();
    scanf("%s",a[0]+1); scanf("%s",a[1]+1); n=strlen(a[0]+1);
    pre[0].init(a[0]); reverse(a[0]+1,a[0]+n+1);
    suf[0].init(a[0]); reverse(a[0]+1,a[0]+n+1);
    pre[1].init(a[1]); reverse(a[1]+1,a[1]+n+1);
    suf[1].init(a[1]); reverse(a[1]+1,a[1]+n+1);
    scanf("%s",s+1); m=strlen(s+1); S.init(s);
    add(ans,get(s,0));
    if(m==1){cout<<ans;return 0;} reverse(s+1,s+m+1); S.init(s);
    add(ans,get(s,1));
    if (m == 2) {
        for (int i = 1; i <= n; i++) {
            if (a[0][i] == s[1] && a[1][i] == s[2]) sub(ans, 1);
            if (a[1][i] == s[1] && a[0][i] == s[2]) sub(ans, 1);
        }
    }
    cout << ans << '\n';
    return 0;
}