//
// Created by Psy.C on 2026/2/5.
//
/**
 *全局向量a，存储所有可能的数值并进行离散化
 *
 * 找到数组a中第一个大于x的元素的位置索引
 *返回该位置相对于数组开始的偏移量
 *
*cnt数组：线段树节点记录每个值出现的次数
sum数组：线段树节点记录每个区间内数值的总和
 *
*线段树单点更新函数：在位置p执行op操作(op为1表示添加，-1表示删除)
当l==r时到达叶子节点，更新该位置的计数和总和
根据p与mid的关系决定递归到左子树或右子树
更新完成后回溯，合并左右子树的统计信息
*线段树区间查询函数：查询[L,R]区间内的总和和元素个数
边界情况：区间无效或无交集时返回{0,0}
完全包含当前区间时直接返回当前节点的值
否则递归查询左右子树并合并结果
 *
*检查阈值t是否满足条件：小于等于t的所有元素调整后超过v
查询小于等于t的所有元素的总和和数量
计算将这些元素全部提升到t所需的操作次数是否大于v
 *
 *读取数组长度n和询问次数q
 *定义原数组h和操作数组Q
*读取初始数组，并将所有可能出现的值加入数组a
读取所有操作，如果是修改操作(1)，还需读取新值并加入数组a
 *对数组a排序并去重，完成离散化处理
 *将原始数组中的所有值加入线段树
 *
*修改操作(1)：先删除旧值，更新数组，再插入新值
查询操作(2)：使用二分搜索找到最小的阈值，使调整代价不超过v
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200007
#define li pair<ll, int>
using namespace std;

vector<ll> a;
int get(const double x) {
    return static_cast<int>(ranges::upper_bound(a, x) - a.begin());
}

int cnt[N<<2]; ll sum[N<<2];
void update(const int p, const int op, const int l, const int r, const int rt) {
    if (l == r) {
        cnt[rt] += op;
        sum[rt] += op * a[p-1];
        return;
    }
    if (const int mid = (l+r)>>1; p <= mid) update(p, op, l, mid, rt<<1);
    else update(p, op, mid+1, r, rt<<1|1);
    cnt[rt] = cnt[rt<<1] + cnt[rt<<1|1];
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

li query(const int L, const int R, const int l, const int r, const int rt) {
    if (L > R) return {0, 0};
    if (R < l || r < L) return {0, 0};
    if (L <= l && r <= R) return {sum[rt], cnt[rt]};
    const int mid = (l+r)>>1;
    const li tl = query(L, R, l, mid, rt<<1), tr = query(L, R, mid+1, r, rt<<1|1);
    return {tl.first + tr.first, tl.second + tr.second};
}

bool ok(const double t, const ll v) {
    auto [fst, snd] = query(1, get(t), 1, static_cast<int>(a.size()), 1);
    return snd * t - static_cast<double>(fst) > static_cast<double>(v);
}

int main() {
    fast;
    int n, q; cin >> n >> q;
    ll h[N], Q[N][3];
    for (int i = 1; i <= n; ++i) {
        cin >> h[i]; a.push_back(h[i]);
    }
    for (int i = 1; i <= q; ++i) {
        cin >> Q[i][0];
        if (Q[i][0] == 1) {
            cin >> Q[i][1] >> Q[i][2];
            a.push_back(Q[i][2]);
        } else cin >> Q[i][1];
    }
    ranges::sort(a);
    a.erase(ranges::unique(a).begin(), a.end());
    for (int i = 1; i <= n; ++i) update(get(static_cast<double>(h[i])), 1, 1, static_cast<int>(a.size()), 1);
    for (int i = 1; i <= q; ++i) {
        if (Q[i][0] == 1) {
            const int p = static_cast<int>(Q[i][1]), x = static_cast<int>(Q[i][2]);
            update(get(static_cast<double>(h[p])), -1, 1, static_cast<int>(a.size()), 1);
            h[p] = x;
            update(get(static_cast<double>(h[p])), 1, 1, static_cast<int>(a.size()), 1);
        } else {
            const ll v = Q[i][1];
            double le = 0, hi = 1e9 + static_cast<double>(v) + 1;
            for (int j = 0; j < 100; ++j) {
                if (const double mid = (le + hi) / 2; ok(mid, v)) hi = mid;
                else le = mid;
            }
            cout << fixed << setprecision(15) << (le+hi)/2 << '\n';
        }
    }
    return 0;
}