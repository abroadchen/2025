//
// Created by Psy.C on 2025/11/26.
//
/*
*n: 第一类元素数量
m: 第二类元素数量
tot: 离散化后的时间点数量
mx[N<<2]: 线段树节点存储的最大值（N<<2 = N*4）
id[N<<2]: 线段树节点存储的ID
ans[N>>1]: 答案数组（N>>1 = N/2）
 *
*st: 开始时间
ed: 结束时间
t: 时间戳（类型）
id: 节点编号
*rt: 当前节点编号
l,r: 当前区间范围
pos: 要更新的位置
val: 要更新的值
ID: 对应的ID
在叶子节点设置值，向上更新最大值
 *
*查询区间[x,y]中值≥val的最大元素的ID
优先查找左子树，再查找右子树

 *记录时间戳用于离散化
*对时间戳排序并去重
计算离散化后的时间点数量
 *将时间戳离散化为1到tot的整数
*如果是前n个节点：更新线段树
如果是后m个节点：在线段树中查询答案
 *
*1 - rt: 线段树的根节点编号（从1开始）
1 - l: 当前线段树覆盖区间的左边界（时间范围的最小值）
tot - r: 当前线段树覆盖区间的右边界（时间范围的最大值）
a[i].t - pos: 要更新的位置（时间戳的离散化值）
a[i].ed - val: 要更新的值（结束时间）
a[i].id - ID: 对应的标识符（元素ID）
 *
 *
*1 - rt: 线段树的根节点编号（从1开始）
1 - l: 当前查询区间的左边界（时间范围的最小值）
tot - r: 当前查询区间的右边界（时间范围的最大值）
a[i].t - x: 查询区间的左端点（从当前位置开始）
tot - y: 查询区间的右端点（到最大位置结束）
a[i].ed - val: 查询条件的阈值（查找结束时间≥此值的元素）
 *
 *时间复杂度：O((n+m)log(n+m))
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 2e5+7;

int n, m, tot, mx[N<<2], id[N<<2], ans[N>>1];
struct node {
    int st, ed, t, id;
    bool friend operator<(const node a, const node b) {
        return a.st == b.st ? a.id < b.id : a.st < b.st;
    }
} a[N];
vector<int> v;

void update(const int rt, const int l, const int r, const int pos, const int val, const int ID) {
    if (l == r) { mx[rt] = val; id[rt] = ID; return; }
    const int mid = (l + r) >> 1;
    if (pos <= mid) update(rt<<1, l, mid, pos, val, ID);
    else update(rt<<1|1, mid+1, r, pos, val, ID);
    mx[rt] = max(mx[rt<<1], mx[rt<<1|1]);
}

int query(const int rt, const int l, const int r, const int x, const int y, const int val) {
    if (l == r) return id[rt];
    const int mid = (l + r) >> 1; int ret = -1;
    if (y <= mid) { if (mx[rt<<1] >= val) ret = query(rt<<1, l, mid, x, y, val); }
    else if (x > mid) { if (mx[rt<<1|1] >= val) ret = query(rt<<1|1, mid+1, r, x, y, val); }
    else {
        if (mx[rt<<1] >= val) ret = query(rt<<1, l, mid, x, mid, val);
        if (ret == -1 && mx[rt<<1|1] >= val) ret = query(rt<<1|1, mid+1, r, mid + 1, y, val);
    }
    return ret;
}

int main() {
    fast;
    cin >> n >> m;
    rep(i,n+m) {
        cin >> a[i].st >> a[i].ed >> a[i].t;
        a[i].id = i;
        v.push_back(a[i].t);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    tot = static_cast<int>(v.size());
    sort(a + 1, a + n + m + 1);
    rep(i,n+m) a[i].t = static_cast<int>(lower_bound(v.begin(), v.end(), a[i].t) - v.begin() + 1);
    rep(i,n+m) {
        if (a[i].id <= n) update(1, 1, tot, a[i].t, a[i].ed, a[i].id);
        else ans[a[i].id - n] = query(1, 1, tot, a[i].t, tot, a[i].ed);
    }
    rep(i,m) cout << ans[i] << " ";
    return 0;
}