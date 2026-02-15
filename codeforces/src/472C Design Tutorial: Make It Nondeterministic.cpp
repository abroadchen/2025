//
// Created by Psy.C on 2026/2/14.
//
/**
int t = rk[i]：获取当前处理的节点编号
a = strcmp(na[t].f, now)：比较f串与当前串
b = strcmp(na[t].s, now)：比较s串与当前串
strcmp返回值：
0：第一个字符串字典序大于第二个
= 0：两字符串相等
< 0：第一个字符串字典序小于第二个

a > 0 && b > 0：两个字符串都大于当前串
if (strcmp(na[t].f, na[t].s) > 0)：f串字典序大于s串
选择字典序较小的字符串（贪心策略）
else if (a > 0)：只有f串大于当前串，选择f串
else if (b > 0)：只有s串大于当前串，选择s串
else ok = 0：都不大于当前串，标记为无效

时间复杂度：O(n*M)，其中M是字符串长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define M 60
using namespace std;

struct node { char f[M], s[M]; } na[N];

int n, rk[N];
void init() {
    for (int i = 1; i <= n; ++i) cin >> na[i].f >> na[i].s;
    for (int i = 1; i <= n; ++i) cin >> rk[i];
}

char now[M];//当前选择的字符串
void out() {
    int ok = 1; now[0] = 0;//初始化为空字符串
    for (int i = 1; i <= n && ok; ++i) {
        if (int t = rk[i], a = strcmp(na[t].f, now), b = strcmp(na[t].s, now); a > 0 && b > 0) {
            if (strcmp(na[t].f, na[t].s) > 0) strcpy(now, na[t].s);
            else strcpy(now, na[t].f);
        }
        else if (a > 0) strcpy(now, na[t].f);
        else if (b > 0) strcpy(now, na[t].s);
        else ok = 0;
    }
    if (ok) cout << "YES\n"; else cout << "NO\n";
}

int main() {
    fast;
    cin >> n; init(); out();
    return 0;
}