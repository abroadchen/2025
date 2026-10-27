//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
对每个区间 [l, r]：
mp[l]++：在 l 处覆盖数 +1。
mp[r+1]--：在 r+1 处覆盖数 −1（半开区间 [l, r+1)）。
用 map（有序）存所有关键坐标点及其差分。注意 r+1 是关键点，因为区间是闭的 [l,r]，覆盖到 r，从 r+1 起不再覆盖该区间
pre 记录上一个关键坐标，初始 -1。
sum 是当前"同时覆盖的区间数"（从差分累加得出）。
遍历有序 map：
ans[sum] += fst - pre：上一坐标 pre 到当前坐标 fst 这一整段连续区域，被 sum 个区间覆盖，把这段长度 fst - pre 计入"恰好被 sum 个区间覆盖"的总长 ans[sum]。
sum += snd：在这点应用差分（进入/离开区间），更新当前覆盖数。
pre = fst：更新上一坐标。
关键：先累加当前段（用旧的 sum），再更新 sum，保证同一段内覆盖数一致
输出被恰好 1..n 个区间覆盖的长度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int n;
ll l, r, ans[N];
map<ll,int> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> l >> r, mp[l]++, mp[r+1]--;
    ll pre = -1, sum = 0;
    for (auto &[fst, snd] : mp) {
        ans[sum] += fst - pre;
        sum += snd;
        pre = fst;
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << (i==n?'\n':' ');
    return 0;
}