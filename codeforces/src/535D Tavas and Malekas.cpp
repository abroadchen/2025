//
// Created by Psy.C on 2026/3/4.
//
/**
s[N]: 主串
n: 主串长度
w[N]: 位置数组
m: 位置数量
c: 匹配计数
kmp(): KMP匹配函数，统计特定位置的匹配次数

读入n、m和模式串t
计算模式串长度l2
初始化主串s为全'?'（未确定字符）
读入位置数组w，并转换为0基索引
排序并去重位置数组
从左到右填充主串s
lst: 记录上次填充的最后位置
对于每个位置w[i]，如果能继续填充：
计算起始位置st和偏移量d
将模式串t的一部分复制到s中
更新lst为当前填充的最后位置

如果匹配数少于期望数，输出0
时间复杂度为O(n + Σ|模式串| + cnt*log(mod))，空间复杂度为O(n)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+1, mod = 1e9+7;

char t[N];
int l2, nxt[N];
void get() {
    int k = 0;
    for (int i = 1; i < l2; ++i) {
        while (k > 0 && t[k] != t[i]) k = nxt[k-1];
        if (t[k] == t[i]) k++;
        nxt[i] = k;
    }
}

char s[N];
int n, w[N], m, c;
void kmp() {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        while (k > 0 && t[k] != s[i]) k = nxt[k-1];
        if (t[k] == s[i]) k++;
        if (k == l2)
            if (binary_search(w, w+m, i-k+1))
                c++;
    }
}

int main() {
    fast;
    cin >> n >> m >> t; l2 = strlen(t);
    for (int i = 0; i < n; ++i) s[i] = '?';
    s[n] = '\0';
    for (int i = 0; i < m; ++i) cin >> w[i], w[i] -= 1;
    sort(w, w+m); m = unique(w, w+m) - w;
    int lst = -1;
    for (int i = 0; i < m; ++i) if (w[i] + l2 - 1 > lst) {
        int st = w[i], d = 0;
        if (lst + 1 > w[i]) {
            d = lst + 1 - w[i];
            st = lst + 1;
        }
        for (int j = st; j <= w[i]+l2-1; ++j)
            s[j] = t[j-st+d];
        lst = w[i] + l2 - 1;
    }
    get(); kmp();
    if (c < m) {
        cout << "0\n";
        return 0;
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        if (s[i] == '?') cnt++;
    ll ans = 1;
    for (int i = 1; i <= cnt; ++i)
        ans = ans*26%mod;
    cout << ans << '\n';
    return 0;
}