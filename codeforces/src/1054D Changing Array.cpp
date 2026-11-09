//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
n：数据个数；用 while(n-- > 0) 迭代时会被递减到 0。
k：二进制位数（决定掩码 m）。
mp：统计"归并后键"的出现次数，键值升序自动排列。
每个前缀异或 s 与它的"翻转版 s^m"属于同一个等价类，用二者中较小者当键，即可把"互补"的两类合并计数。
这就是分组的核心——把能相互配对的异或值归为一类
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int c2(int n) { return n*(n-1)/2; }

int n, k;
map<int,int> mp;
signed main() {
    fast;
    cin >> n >> k;
    //全部 n+1 个前缀和的总组合数初值 掩码：低 k 位全 1
    int ans = c2(n+1), m = (1<<k)-1, v, s = 0; mp[0] = 1;//前缀异或为 0 的"初始状态"，出现 1 次
    while (n-- > 0) {
        cin >> v; s ^= v;//当前前缀异或
        mp[min(s,s^m)]++;//归并到等价类并计数
    }
    for (auto &p : mp) {//遍历每个等价类
        int c = p.second;//该类出现次数
        ans -= c2(c/2) + c2(c-c/2);//扣掉该类的"非最优成对差"
    }
    cout << ans << '\n';
    return 0;
}