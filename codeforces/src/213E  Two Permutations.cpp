//
// Created by Psy.C on 2025/12/6.
//
/*
*N = 2e5+10：最大数组大小
B = 13331：字符串哈希的基数
P = 999998639：哈希模数（大质数）
sg：线段树节点结构
pre：该区间的哈希前缀值
tot：该区间元素总数
l, r：区间左右端点
pw[N]：预处理的幂次数组
 *
 *哈希值合并，左子区间的哈希值乘以B^(右子区间长度)再加上右子区间的哈希值
 *
*线段树单点更新：
val = 0：删除元素
val ≠ 0：添加元素（值为位置）
 *
 *读取模式串a，计算其哈希值sum和辅助值add
 *读取文本串b，记录每个值在b中的位置
 *
*维护长度为n的滑动窗口
update(1, pos[i], i)：将新元素加入窗口
if (i > n) update(1, pos[i-n], 0)：移除窗口外的旧元素
比较当前窗口哈希值与模式串哈希值
 *
 *时间复杂度：O((n+m) log m) 空间复杂度：O(m)
 *
 *
*tr[1].pre：当前窗口序列的哈希值
(sum + d * add)：期望的目标哈希值
 *i-n：滑动窗口的起始位置
 *
 *sum = a[1] * B^(n-1) + a[2] * B^(n-2) + ... + a[n] * B^0
*add = pw[0] + pw[1] + pw[2] + ... + pw[n-1]
    = B^0 + B^1 + B^2 + ... + B^(n-1)
    = (B^n - 1) / (B - 1)  // 几何级数求和公式  权重系数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ull unsigned long long
using namespace std;

constexpr
int N = 2e5+10, B = 13331, P = 999998639, M = 2e5;
struct sg { ull pre, tot; int l, r; } tr[N<<2];
ull pw[N];

void push_up(const int id) {
    tr[id].tot = tr[id<<1].tot + tr[id<<1|1].tot;
    tr[id].pre = (tr[id<<1].pre * pw[tr[id<<1|1].tot] + tr[id<<1|1].pre) % P;
}

void build(const int l, const int r, const int id) {
    tr[id].l = l, tr[id].r = r, tr[id].pre = 0;
    if (l == r) return;
    const int mid = (l + r) >> 1;
    build(l, mid, id<<1);
    build(mid+1, r, id<<1|1);
    push_up(id);
}

void update(const int id, const int pos, const int val) {
    if (tr[id].l == tr[id].r) {
        if (!val) tr[id].tot -= 1;
        else tr[id].tot += 1;
        tr[id].pre = val;
        return;
    }
    const int mid = (tr[id].l + tr[id].r) >> 1;
    if (pos <= mid) update(id<<1, pos, val);
    if (pos > mid) update(id<<1|1, pos, val);
    push_up(id);
}

int a[N], b[N], pos[N];
signed main() {
    fast;
    pw[0] = 1;
    for (int i = 1; i <= M; ++i) pw[i] = pw[i-1]*B%P;
    int n, m, ans = 0;
    cin >> n >> m; build(1, m, 1);
    ull sum = 0, add = 0;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], sum = (sum * B + a[i]) % P,
            add += pw[i-1], add %= P;
    for (int i = 1; i <= m; ++i)
        cin >> b[i], pos[b[i]] = i;
    for (int i = 1; i <= m; ++i) {
        if (i > n) update(1, pos[i-n], 0);
        update(1, pos[i], i);
        const int d = i - n;
        if (d >= 0 && tr[1].pre % P == (sum + d * add) % P)
            ans++;
    }
    cout << ans << '\n';
    return 0;
}