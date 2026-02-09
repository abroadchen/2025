//
// Created by Psy.C on 2026/2/9.
//
/**
w[a[i]]：获取字符a[i]的权值
(i+1)：位置权重（从1开始计数）

i = strlen(a)+1：从字符串a之后开始
i <= k + strlen(a)：总共k轮扩展
1ll*i*x：每轮使用最大权值x，位置为i

时间复杂度：O(|a| + k)，其中|a|是字符串a的长度 空间复杂度：O(1)（不考虑输入存储）
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

char a[1005];
int k, w[200];//需要扩展的轮数 各字符的权值
ll ans = 0;

int main() {
    fast;
    cin >> a >> k;
    int x = 0, i, t;
    //将权值存储到对应字母的位置
    for (i = 0; i < 26; ++i) cin >> t, x = max(x, t), w[i+'a']=t;
    for (i = 0; i < strlen(a); ++i) ans += 1ll*w[a[i]]*(i+1);
    for (i = strlen(a)+1; i <= k + strlen(a); ++i) ans += 1ll*i*x;
    cout << ans << '\n';
    return 0;
}