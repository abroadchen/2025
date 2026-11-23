//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
a = 原始数组（保序），b = 排序副本（降序）。
目的：找出值最大的 m*k 个数
取降序前 m*k 个（全局最大的 m*k 个）加入 ans。
mp（map）记录这 m*k 个数各出现了几次（值→次数）。
注意并列去重问题：用值计数而不是下标，之后划分时按值匹配
从左往右扫原数组：
当前数 a[i] 若在选中集合 mp 里（次数>0），就消耗一个名额，cnt++。
当 cnt 攒到 m（本段已有 m 个选中数），就在位置 i 记下分隔点 p[++tot]=i，重置 cnt=0。
直到凑出 k-1 个分隔点为止（此时已划好前 k-1 段）。
这保证了前 k-1 段每段恰好含 m 个被选中的数
从右往左扫，收集最后一段（第 k 段）需要的 m 个选中数，直到 cnt==m。
分隔点设为 i-1——即第 k 段的起点（第 k-1 段与第 k 段的分界）
第一行：m*k 个最大数的和 ans。
第二行：k-1 个分隔点位置
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;
bool cmp(int a, int b) { return a > b; }

int n, m, k, a[N], b[N], p[N];
map<int,int> mp;
ll ans;
int main() {
    fast;
    cin >> n >> m >> k;
    rep(i,n) cin >> a[i], b[i] = a[i];
    sort(b+1,b+1+n,cmp);
    for (int i = 1, j = 1; i <= n && j <= m*k; i++, j++)
        ans += b[i], mp[b[i]]++;
    int cnt = 0, tot = 0, i;
    for (i = 1; i <= n; i++) {
        if (cnt < m) { if (mp[a[i]]) mp[a[i]]--, cnt++; }
        if (cnt == m) p[++tot] = i, cnt = 0;
        if (tot == k-1) break;
    }
    cnt = 0;
    for (i = n; ; i--) {
        if (mp[a[i]]) mp[a[i]]--, cnt++;
        if (cnt == m) break;
    }
    p[k-1] = i-1;
    cout << ans << '\n';
    for (i = 1; i < k; i++) cout << p[i] << ' ';
    return 0;
}