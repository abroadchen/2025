//
// Created by Psy.C on 2026/10/4.
//
/***
vis[x]：数值 x 在数组里出现了几次（计数）。
读完数组后，重复出现的值 vis[x] > 1，缺失的值 vis[x] == 0
c[1..cnt]：把所有缺失的数按升序（1-n 自然升序）存起来。这些就是要拿去填补重复位置的候选值
从左到右扫描，优先保证前面的位置尽量小（字典序最小）。
c[now] 是当前还在犹豫用哪个缺失数填补，c[1] 最小。
判断是否替换当前 a[i]：
条件1：vis[a[i]] > 1 && a[i] > c[now] —— 该值重复，且它比当前可用的最小缺失数还大，那就用更小的 c[now] 替换它（使字典序更小）。
条件2：vis[a[i]] > 1 && b[a[i]] == 1 —— 该值重复，且它已经被标记过"需要保留最后一次出现"（b[x]==1 表示这个重复值要保留一次，前面的重复位置必须替换）。也就是重复值只能保留一个，其余全要换掉。
若满足，就执行替换：vis[a[i]]--（该值计数减1），a[i] = c[now]（换成当前最小缺失数），now++（用掉一个），ans++（改动数+1）。
最后一句：if (vis[a[i]] > 1 && a[i] < c[now]) b[a[i]] = 1 —— 当前重复值比当前缺失数小（保留它是划算的，能维持前面位置小），就标记保留它最后一次出现（b[a[i]]=1），这样后面再遇到它就知道要替换掉、而保留这一处。
第一行输出最小改动次数 ans，第二行输出替换后的数组（已是 1-n 的排列）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int a[N], vis[N], c[N], cnt, b[N], ans;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; vis[a[i]]++;
    }
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 0) c[++cnt] = i;
    int now = 1;
    for (int i = 1; i <= n; ++i) {
        if (vis[a[i]] > 1 && a[i] > c[now] ||
            vis[a[i]] > 1 && b[a[i]] == 1) {
            vis[a[i]]--; a[i] = c[now];
            now++, ans++;
        }
        if (vis[a[i]] > 1 && a[i] < c[now]) b[a[i]] = 1;
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}