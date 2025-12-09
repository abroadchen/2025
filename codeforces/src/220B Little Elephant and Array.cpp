//
// Created by Psy.C on 2025/12/8.
//
/*
*n：数组长度
m：查询数量
cnt[N]：计数数组，记录每个数值的出现次数
a[N]：原始数组
tot：当前满足条件的数值个数
ans[N]：答案数组
 *
*将位置x的元素加入当前区间
x：数组下标
如果元素值大于n则忽略
如果该元素的计数刚好等于其值，则满足条件的数目减1
计数加1
如果计数等于元素值，则满足条件的数目加1
 *
*按照左端点所在的块进行排序
同一块内按照右端点排序
这样可以最小化指针移动次数
 *
*通过add/del操作调整当前区间[l, r]到查询区间[q[i].l, q[i].r]
记录当前满足条件的数目到对应查询的答案中
 *
 *时间复杂度：O(n√n)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

constexpr int k = 512;
struct node { int l, r, id; } q[N];
int n, m, cnt[N];
ll a[N], tot, ans[N];
void add(int x) {//函数参数传入的是位置，但实际要统计的是值的出现次数，所以需要通过x = a[x]将位置转换为值
    x = static_cast<int>(a[x]);
    if (x > n) return;
    if (cnt[x] == x) tot--;
    cnt[x]++;
    if (cnt[x] == x) tot++;
}

void del(int x) {
    x = static_cast<int>(a[x]);//a[x]的值来更新x变量
    if (x > n) return;
    if (cnt[x] == x) tot--;//原来满足条件就减1
    cnt[x]--;
    if (cnt[x] == x) tot++;//现在满足条件就加1
}

int l = 0, r = -1;//初始化为空区间[0, -1]
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) {
        cin >> q[i].l >> q[i].r;
        q[i].l--; q[i].r--;//转换为0基索引（减1）
        q[i].id = i;//记录原始查询编号
    }
    sort(q, q + m, [](const node a, const node b) {
        const int ba = a.l / k, bb = b.l / k;
        if (ba == bb) return a.r < b.r;
        return a.l < b.l;
    });
    for (int i = 0; i < m; ++i) {
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        ans[q[i].id] = tot;
    }
    for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
    return 0;
}