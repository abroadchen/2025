//
// Created by Psy.C on 2026/10/7.
//
/***
每个 node 代表一个 k 维"盒子"：mn[i] 和 mx[i] 分别是第 i 维的最小值和最大值；sz 是该盒合并的元素个数
(*this) < o 成立当且仅当 this 的每一维最大值都不超过 o 的该维最小值，即 this 的每个维区间都完全"在 o 的左/下方（不重叠或刚好相邻）。若任何一维 this.mx[i] > o.mn[i]`（有重叠可能），则返回 false。
这是个非严格弱序，对 set 的标准用法是危险的（破坏红黑树不变量），但在这里配合合并逻辑被"有意利用"。
读入一个 k 维新点，初始为单点盒子（mn=mx=x），sz=1。
关键 while：只要 set 中存在与当前 cur "冲突/可合并"的节点（st.contains(cur) 为真，即存在某节点 o 使 cur < o 成立——意味着 cur 完全在其左/下，即它们可被排序为 cur 在前），就：
找到该节点 it，
把 it.sz 并入 cur.sz，
扩维合并：cur 的 mx 取各维 max，mn 取各维 min（即把 it 的盒子扩张进 cur 的盒子，取包围盒），
从 set 中删掉 it。
循环直到没有可合并节点，然后插入 cur。
输出 st.rbegin()->sz，即 set 中"最大盒子"的元素个数

a < b 和 b < a 可能同时成立（因为只要重叠就都返回……不，签名的逻辑是：this < o 要求 this 完全在 o 左边。若两个盒子互相重叠，则 a<b 和 b<a 都可能……让我看：a<b：要求 a 每维 mx<=o.mn；b<a：要求 b 每维 mx<=a.mn。若 a 在 b 左边（a.mx<=b.mn），则 a<b 真、b<a：需 b.mx<=a.mn，一般假。若重叠，则 a<b：需 a.mx<=b.mn，若 a 不都在 b 左则假；b<a 同理假，此时既非 a<b 也非 b<a，违反三分律 → 破坏严格弱序）。
因为 c++ set 的 contains/find/insert 都依赖这个 operator< 做等价类判定，这种破坏性比较会让 STL 行为不确定（可能 UB）。所以这个代码在严格意义上是依赖特定 STL 实现的 hack，不能保证在所有平台正确。但作为竞赛题的期望解法，它通常能过题
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 12;

int k;
struct node {
    int sz, mx[N], mn[N];
    bool operator<(const node& o) const {
        for (int i = 1; i <= k; ++i)
            if (mx[i] > o.mn[i]) return false;
        return true;
    }
};
set<node> st;
int n;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        node cur{};
        for (int j = 1, x; j <= k; ++j) {
            cin >> x;
            cur.mx[j] = cur.mn[j] = x;
        }
        cur.sz = 1;
        while (st.contains(cur)) {
            auto it = st.find(cur); cur.sz += it->sz;
            for (int j = 1; j <= k; ++j) {
                cur.mx[j] = max(cur.mx[j], it->mx[j]);
                cur.mn[j] = min(cur.mn[j], it->mn[j]);
            }
            st.erase(it);
        }
        st.insert(cur);
        cout << st.rbegin()->sz << '\n';
    }
    return 0;
}