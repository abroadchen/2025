//
// Created by Psy.C on 2026/9/15.
//
/**
v：一个权重/标记值
id：原始编号（1..n）
比较器规则：

先比 v，v 大的排在前面；
v 相同则 id 小的排在前面
初始：n 个人，每个人 v = 1，id = i（编号 1 到 n）。
k 表示进行 k 轮删除
读入步长 x。
sort(a+1, a+n+1)：按 v 降序排。初始时所有人 v=1，排完后按 id 升序（因为 v 相同比 id）。但一旦有人被删（v=0），下一轮排序时 v=0 的那个人会排到最后面。
ans = (ans + x) % t：约瑟夫数数——从当前指向的位置 ans 往后数 x 步，对剩余人数 t 取模。
if (ans==0) ans = t：取模结果为 0 时回到 t。
输出 a[ans].id（被选中删除的人的原始编号）。
a[ans].v = 0：标记这个人已被删。
t--：存活人数减 1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;
namespace {
    struct node {
        int v, id;
        bool operator<(const node& o) const {
            if (v == o.v) return id < o.id;
            return v > o.v;
        }
    } a[N];
}

int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        a[i].v = 1; a[i].id = i;
    }
    int ans = 1, t = n;
    for (int i = 1, x; i <= k; ++i) {
        cin >> x;
        sort(a+1, a+n+1);
        ans = (ans+x)%t;
        if (ans == 0) ans = t;
        cout << a[ans].id << ' ';
        a[ans].v = 0;
        t--;
    }
    return 0;
}