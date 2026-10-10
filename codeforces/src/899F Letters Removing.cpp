//
// Created by Psy.C on 2026/10/10.
//
/**
字符集 = 0-9（0-9）+ a-z（10-35）+ A-Z（36-61），共 62 个字符 → 编号范围 [0, 61]。
即使只有 62 个，代码开的是 M = 63，稍宽裕
bit.update(pos, 1)：标记原下标 pos 已被删除。
bit.query(x)：原下标 1..x 中已删个数 = tr 前缀和
mid - bit.query(mid) = 在 1..mid 中存活的个数。我们需要找到最小的 mid 使存活个数 ≥ now，即第 now 个存活字符所在的原下标。这是在 BIT 上的二分查找，经典 O(log²n)
对每个字符，用一个 set<int> 存它的所有原下标位置。st[62] 个 set
l, r 是当前存活字符串中的区间位置（1-based，动态变化）。
find(l)、find(r) 把它们映射回原数组下标 L、R。
在字符 c（p）所属的 set st[p] 里，用 lower_bound(L) 找到第一个 ≥ L 的位置 it，遍历所有 ≤ R 的位置 t：
标记 del[*t] = true
bit.update(*t, 1)：在 BIT 中登记删除，使后续 find 位置映射正确
最后 st[p].erase(it, t) 批量移除这区间内该字符的所有记录
遍历原串，只输出未被删除的字符

每个字符位置在操作中被删除一次，进入循环一次，每次删除 O(log N)。
find 每次 O(log² N)（二分 × BIT 查询）。
每个位置最多被处理一次（因为它一旦删除就从 set 里移除），所以总删除量 ≤ n。
总体
O
(
n
log
⁡
n
+
m
log
⁡
2
n
)
O(nlogn+mlog
2
 n)，能处理 n,m ≤ 2e5
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5, M = 63;

inline int getid(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
    return ch - 'A' + 10 + 26;
}

struct BIT {
    int tr[N];
#define low_bit(x) (x&-x)

    void update(int x, int k) {
        for (; x < N; x += low_bit(x)) tr[x] += k;
    }
    int query(int x) const {
        int res = 0;
        for (; x; x -= low_bit(x)) res += tr[x];
        return res;
    }
#undef low_bit
} bit;

inline int find(int now) {
    int l = now, r = N-1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (mid - bit.query(mid) < now) l = mid + 1;
        else r = mid;
    }
    return l;
}

char str[N];
set<int> st[M];
bool del[N];
int main() {
    int n, m; scanf("%d%d",&n,&m);
    scanf("%s", str+1);
    for (int i = 1; i <= n; ++i) st[getid(str[i])].insert(i);
    while (m--) {
        int l, r; scanf("%d%d",&l,&r);
        char ch[5]; scanf("%s", ch+1);
        int L = find(l), R = find(r), p = getid(ch[1]);
        auto it = st[p].lower_bound(L), t = it;
        for (; t != st[p].end() && *t <= R; ++t) {
            del[*t] = true;
            bit.update(*t, 1);
        }
        st[p].erase(it, t);
    }
    for (int i = 1; i <= n; ++i)
        if (!del[i]) printf("%c",str[i]);
    return 0;
}