//
// Created by Psy.C on 2026/1/29.
//
/**
 * fa[M], fb[M], fc[M]：存储各种索引
 *
*刚刚 --it 后，it 指向前一个元素
但要删除的是原来那个元素（前一个位置的值）
所以 ++it 把 it 移回原来的位置
 *
*删除当前元素后，it 变成无效
s.lower_bound(e) 重新定位到合适位置
--it 向前移动一位，调整到正确位置
 */
#include <iostream>
#include <algorithm>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
#define M 300010
#define inf 1000000000
#define rep(i,n) for (int i = 1; i <= (n); ++i)
using namespace std;

//值 val、类型 id1、位置 id2
struct node { int val, id1, id2; } f[M];

struct Pair { int b, c; };
bool operator<(const Pair a, const Pair b) { return a.b < b.b; }

set<Pair> s;
multiset<int> v;//整数的多重集合 允许重复元素
void add(const int nb, const int nc) {
    int cb;
    const Pair e = {nb, nc};
    auto it = s.upper_bound(e);//第一个大于 e 的位置
    if (it->c >= e.c) return;//当前 c 值不小于新值 不需要添加
    int cc = it->c; --it;//向前移动迭代器
    const auto it2 = v.find(it->b + cc); v.erase(it2);//删除找到的元素
    while (it->c <= e.c) {
        cb = it->b, cc = it->c; --it;//保存当前 b、c 值
        v.erase(it->b + cc); ++it;//从 v 中删除特定值 迭代器后移
        //从 s 中删除当前元素 找到 e 的下界
        s.erase(it); it = s.lower_bound(e); --it;
    }
    cb = it->b, cc = it->c; v.insert(cb + e.c); ++it;//向 v 中插入新值
    cc = it->c; v.insert(e.b + cc); s.insert(e);//向 v 中插入另一个值 向 s 中插入新 Pair
}

int tot, fa[M], fb[M], fc[M], n, a[N];
void get() {
    Pair e{};
    e.b = 0, e.c = inf + 1; s.insert(e);
    e.b = inf + 1, e.c = 0; s.insert(e); v.insert(0);
    rep(i,tot) if (!fa[i]) add(fb[i] ? fb[i] : inf, fc[i] ? fc[i] : inf);
    int ans = inf; bool flag = true;
    for (int i = n; i >= 1; --i) {
        ans = min(ans, i + *v.begin());
        if (fa[a[i]] == i) {
            if (!fb[a[i]] && !fc[a[i]]) { flag = false; break; }
            add(fb[a[i]] ? fb[a[i]] : inf, fc[a[i]] ? fc[a[i]] : inf);
        }
    }
    if (flag) ans = min(ans, *v.begin());
    cout << ans;
}

int main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> f[++tot].val;
        f[tot].id1 = 1, f[tot].id2 = i;
    }
    rep(i,n) {
        cin >> f[++tot].val;
        f[tot].id1 = 2, f[tot].id2 = i;
    }
    rep(i,n) {
        cin >> f[++tot].val;
        f[tot].id1 = 3, f[tot].id2 = i;
    }
    sort(f + 1, f + 3*n + 1, [](const node a, const node b) {
        return a.val < b.val;
    });
    tot = 0;
    int b[N], c[N];
    rep(i,3*n) {
        if (i == 1 || f[i].val != f[i-1].val) tot++;//对值进行离散化（去重编号）
        //三个数组的值映射到离散化后的索引
        if (f[i].id1 == 1) a[f[i].id2] = tot;
        if (f[i].id1 == 2) b[f[i].id2] = tot;
        if (f[i].id1 == 3) c[f[i].id2] = tot;
    }
    //为每个离散化后的值记录第一次出现的位置
    rep(i,n) if (!fa[a[i]]) fa[a[i]] = i;
    rep(i,n) if (!fb[b[i]]) fb[b[i]] = i;
    rep(i,n) if (!fc[c[i]]) fc[c[i]] = i;
    get();
    return 0;
}