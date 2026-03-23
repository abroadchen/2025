//
// Created by Psy.C on 2026/3/23.
//
/**
n：物品数量
a, b, c：三个背包的容量
mx：最大物品体积
ans：答案（浪费的空间）
s：存储物品体积的有序集合
读入三个背包容量，并按降序排列（a ≥ b ≥ c）
读入所有物品体积，同时记录最大体积
如果最大物品体积超过三个背包容量之和，则无解
处理体积大于a+b的物品：只能单独放在容量最大的a包中，一定会浪费空间
处理体积大于a+c但不超过a+b的物品：必须用a包，然后尝试用c包装一个小物品
处理体积大于max(a, b+c)的物品：用a包装，尝试用b包装一个小物品
如果b+c > a，处理体积大于a但不超过max(a, b+c)的物品

a1：体积大于b的物品数量
b1：体积大于c但不超过b的物品数量
c1：体积不超过c的物品数量
计算可以用bc组合装下的a类物品数量
如果c类物品过多，尝试将部分c类和b类物品组合
根据b1和a1的关系选择最优策略

平衡c类和b类物品
c1：体积≤c的小物品数量
b1：体积在(c,b]的中等物品数量
如果c类物品太多，可以将两个c类物品放入一个容量为b的背包中
d = (c1 - b1)/2 表示最多可以配对 (c1 - b1)/2 对c类物品
这样可以减少c类物品数量，同时增加等效的b类物品数量
处理a类物品较多的情况
策略1：(b1+a1+1)/2
将a类物品和b类物品配对，用a容量背包装（因为a≥b）
每个背包最多装2个物品，所以需要 (b1+a1+1)/2 个背包
策略2：(b1+c1+a1+2)/3
将a类、b类、c类物品三三配对，用a容量背包装
每个背包最多装3个物品，所以需要 (b1+c1+a1+2)/3 个背包
选择最大值：因为我们要计算浪费的空间，所以选择需要更多背包的策略
处理a类物品较少的情况
步骤1：优化物品配对
d = min((a1-b1)/2, k)：最多能配对多少个a类物品
k 是之前计算的可以使用bc组合来装的a类物品数量
d 取两者最小值
a1 -= d, b1 += d：将d个a类物品转换为等效的b类物品
步骤2：计算背包需求
max(a1, b1)：a类和b类物品各自需要的最少背包数
因为a类物品只能用a容量背包，b类物品也只能用a或b容量背包
所以两者独立计算，取较大值


时间复杂度：
O(n log n)，主要是multiset操作的开销。
空间复杂度：
O(n)，用于存储物品体积

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a, b, c, mx, ans;
multiset<int> s;
int main() {
    fast;
    cin >> n >> a >> b >> c;
    if (c > b) swap(c, b);
    if (b > a) swap(b, a);
    if (c > b) swap(c, b);
    for (int i = 1, t; i <= n; ++i) {
        cin >> t; mx = max(mx, t);
        s.insert(t);
    }
    if (mx > a + b + c) cout << -1, exit(0);
    while (s.size() && *--s.end() > a + b) ans++, s.erase(--s.end());
    while (s.size() && *--s.end() > a + c) {
        ans++, s.erase(--s.end());
        if (s.size() && s.upper_bound(c) != s.begin())
            s.erase(--s.upper_bound(c));
    }
    while (s.size() && *--s.end() > max(a, b+c)) {
        ans++, s.erase(--s.end());
        if (s.size() && s.upper_bound(b) != s.begin())
            s.erase(--s.upper_bound(b));
    }
    if (b + c > a) {
        while (s.size() && *--s.end() > a) {
            ans++, s.erase(--s.end());
            if (s.size() && s.upper_bound(a) != s.begin())
                s.erase(--s.upper_bound(a));
        }
    }
    int a1 = 0, b1 = 0, c1 = 0, k = 0;
    for (auto x : s) {
        if (x > b) a1++;
        else if (x > c) b1++;
        else c1++;
    }
    if (b + c > a) k = a1;
    else {
        for (auto x : s)
            if (x > b && x <= b + c) k++;
    }
    if (c1 > b1) {
        int d = (c1 - b1)/2;
        c1 -= d; b1 += d;
    }
    if (b1 >= a1) ans += max((b1+a1+1)/2, (b1+c1+a1+2)/3);
    else {
        int d = min((a1-b1)/2, k);
        a1 -= d, b1 += d;
        ans += max(a1, b1);
    }
    cout << ans;
    return 0;
}