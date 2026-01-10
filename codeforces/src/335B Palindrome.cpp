//
// Created by Psy.C on 2026/1/10.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 500005
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int M = 3005, K = 50, L = 100, inf = 2600;
int cnt, f[M][M];//最长回文子序列长度
char b[N], s[N];
void dfs(const int l, const int r) {
    if (l > r) return;
    if (l == r) b[++cnt] = s[l]; else {//单个字符，直接添加
        if (s[l] == s[r]) {//两端字符相同
            b[++cnt] = s[l];//添加左端字符
            dfs(l + 1, r - 1);//递归处理中间部分
            b[++cnt] = s[r];//添加右端字符
        } else {
            if (f[l+1][r] > f[l][r-1]) dfs(l + 1, r);//选择能产生更长回文的分支
            else dfs(l, r - 1);
        }
    }
}


int main() {
    fast;
    scanf("%s", s + 1);
    const int n = static_cast<int>(strlen(s + 1));
    if (n >= inf) {
        int ans[K];//统计每个字母的出现次数
        for (int i = 1; i <= n; ++i) {
            ans[s[i] - 'a']++;//对应字母计数器++
            if (ans[s[i] - 'a'] >= L) {
                for (int j = 1; j <= L; ++j) cout << s[i];//输出L个该字母
                return 0;
            }
        }
    }
    rep(i,n) rep(j,n) f[i][j] = 0;
    rep(i,n) f[i][i] = 1;//单个字符的回文长度为1
    for (int len = 2; len <= n; ++len) for (int i = 1; i + len - 1 <= n; ++i) {//枚举起始位置
        if (const int j = i + len - 1; s[i] == s[j]) f[i][j] = max(f[i][j], f[i+1][j-1]+2); else {
            f[i][j] = max(f[i][j], max(f[i+1][j], f[i][j-1]));
        }
    }
    dfs(1, n);
    if (cnt <= L) { rep(i,cnt) cout << b[i]; } else {
        rep(i,K) cout << b[i];
        for (int i = K; i >= 1; --i) cout << b[i];
    }
    return 0;
}