//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int a[] = { 0,4,10,20,35,56,83,116,155,198,244,292,341 }, n;
signed main() {
    fast;
    cin >> n;
    if (n <= 12) cout << a[n] << '\n';
    else cout << a[12] + (n-12)*49 << '\n';
    return 0;
}

/**
map<int,int> mp;
int a[] = {1,5,10,50}, n;
void dfs(int cur, int sum) {
    if (cur == n) { mp[sum] = 1; return; }
    rep(i,len) dfs(cur+1,sum+a[i]);
}

int main() {
    for (int i = 1; i <= 20; i++) {
        mp.clear();
        dfs(0,0);
        cout << mp.size() << ',';
    }
}

dfs(cur, sum)：cur 是已经选的张数，sum 是当前累计总额。
当 cur==n（选满 n 张）时，把 sum 记入 mark。
否则递归循环 4 种币值继续加。
本质：枚举 n 张币值的所有排列组合（顺序不同的同多集合会生成相同金额，map 自动去重），共有 4^n 种选择路径。
对每个 n，先清空 mark，执行 DFS，输出 mark.size()（不同金额个数）

 */