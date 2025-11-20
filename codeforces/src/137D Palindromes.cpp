//
// Created by Psy.C on 2025/11/20.
//
/*
*常量N=512，表示数组大小
string s：存储输入字符串
int n：分割段数限制
int l：字符串长度
int y[N][N]：预处理数组，存储回文代价
int f[N][N]：DP状态数组，f[k][i]表示用k段覆盖前i个字符的最小代价
int g[N][N]：路径记录数组，用于重构解
int x：记录最优解的段数
 *
 *k表示段数，x表示当前处理到的位置
*如果段数大于1：
递归处理前一段：dfs(k-1, g[k][x])
输出分隔符"+"
 *计算当前段的长度t = x - g[k][x]
*输出当前段的内容：
遍历0到t-1
如果i*2<t（前半部分），输出s[g[k][x] + i]
否则（后半部分），输出s[g[k][x] + t - i - 1]
这实际上是在输出一个回文结构
 *
*预处理计算回文代价：
i：起始位置
j：段长度（从0开始）
k：比较位置
j+1>>1：段长度的一半（右移1位相当于除以2）
如果s[i+k] != s[i+j-k]，说明不是回文，代价加1
y[i][j]存储从位置i开始长度为j+1的子串变成回文需要修改的字符数
 *
*k：当前使用的段数
i：当前覆盖的位置
j：新增段的长度（从0开始）
如果从状态f[k][i]转移到f[k+1][i+j+1]更优：
更新f[k+1][i+j+1] = f[k][i] + y[i][j]
记录路径g[k+1][i+j+1] = i
 *
*找到覆盖全部字符的最优段数：
遍历所有可能的段数1到n
选择f[i+1][l]最小的作为最优解
 *
 *O(n × l³)，其中l是字符串长度，n是段数上限
 */
#include <iostream>
#define rep(i,n) for(int i=0;i<n;++i)
#define sz(n) ((int)(n).size())
using namespace std;

const int N = 512;
string s;
int n, l, y[N][N], f[N][N], g[N][N], x;

void dfs(int k, int x) {
    if (k > 1) { dfs(k - 1, g[k][x]); cout << "+"; }
    int t = x - g[k][x];//g[k][x]：当前段的起始位置
    rep(i,t) cout << ((i*2<t) ? s[g[k][x] + i] : s[g[k][x] + t - i - 1]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>s>>n; l = sz(s);
    rep(i,l) rep(j,l-i) rep(k,j+1>>1) {
        if (s[i+k] - s[i+j-k]) ++y[i][j];
    }
    rep(k,n+1) rep(i,l+1) f[k][i] = 999;
    f[0][0] = 0;
    rep(k,n) rep(i,l) rep(j,l-i) if (f[k][i]+y[i][j] < f[k+1][i+j+1]) {
        f[k+1][i+j+1] = f[k][i] + y[i][j];
        g[k+1][i+j+1] = i;
    }
    x = 0;
    rep(i,n) if (f[i+1][l] < f[x][l]) x = i + 1;
    cout << f[x][l] << '\n';
    dfs(x, l); cout << '\n';
    return 0;
}