//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
nxt[i] = 前缀 b[0..i] 中最长的既是前缀又是后缀（真前缀）‍的长度。
经典写法：nxt[0]=-1，i 从 0 扫，nxt[i] 存 b[0..i-1] 的最长相同前后缀长度（即失配后跳转位置）
cnt[0] = a 中 '0' 的个数，cnt[1] = a 中 '1' 的个数。
构造出的答案 ans 与 a 等长，且使用的 0/1 总数必须恰好等于 a 中个数

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 5e5+10;

int nxt[N];
char b[N];
void get() {
    nxt[0] = -1;
    int i = 0, j = -1, len = strlen(b);
    while (i < len) {
        if (j == -1 || b[j] == b[i]) nxt[++i] = ++j;
        else j = nxt[j];
    }
}

char a[N], ans[N];
int cnt[2];
int main() {
    fast;
    cin >> a >> b;
    int la = strlen(a), lb = strlen(b);
    rep(i,la) cnt[a[i]-'0']++;
    get();
    for (int i = 0, j = 0; i < la; i++, j++) {
        if (j == lb) j = nxt[j];//已匹配满一整个 b, 跳回 nxt (重叠复用)
        //若该字符在待用中还够
        if (cnt[b[j]-'0']) { ans[i] = b[j]; cnt[b[j]-'0']--; }//就用 b 期望的字符
        //该字符用完了
        else { ans[i] = '0'+(b[j]-'0')^1; cnt[(b[j]-'0')^1]--; }//用另一个字符(翻转)
    }
    cout << ans << "\n";
    return 0;
}