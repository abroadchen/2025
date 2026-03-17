//
// Created by Psy.C on 2026/3/16.
//
/**
n:字符串长度，m:查询次数，k:操作次数
字符串（从ch[1]开始存储）
总共m+k个操作
将[l,r]区间全部设为字符c+'0'
比较两段子串 区间[l,r-c]与区间[l+c,r]是否相同

时间复杂度：O((m+k)×n)（最坏情况）
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, m, k;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

char ch[N];
int main() {
    fast;
    rd(n, m, k); scanf("%s", ch + 1);
    for (int i = 1, flag, l, r, c; i <= m+k; ++i) {
        rd(flag, l, r, c);
        if (flag == 1) memset(ch + l, c + 48, r - l + 1);
        else {
            if (memcmp(ch + l, ch + l + c, r - l - c + 1))
                cout << "NO\n";
            else cout << "YES\n";
        }
    }
    return 0;
}