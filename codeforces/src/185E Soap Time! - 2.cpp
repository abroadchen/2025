//
// Created by Psy.C on 2025/12/1.
//
/*
*px, py: 第一类点变换后的坐标（px[i]=x+y, py[i]=x-y）
sx, sy: 第二类点变换后的坐标
X: 排序后的sx坐标
o: X数组中唯一元素的数量
fa: 线段树根节点数组
 *s[i]: 存储x坐标为X[i]的所有第二类点的索引
 *a[i]: 存储第一类点的最小覆盖半径和索引
 *
*定义线段树结构：
node结构体：lc左子节点，rc右子节点，sum节点计数
tr: 线段树节点数组（可持久化线段树）
tot: 节点计数器
 *在线段树中插入值d，p是当前节点引用，[l,r]是区间范围
 *可持久化操作：创建新节点并复制原节点信息
 *递归插入到左右子树
 *查询区间[u,v]中在版本p中的元素个数
 *空节点返回0，完全包含返回计数
 *分别查询左右子树并合并结果
 *
 *判断矩形区域[x1,x2]×[y1,y2]内是否有第二类点
 *找到x坐标范围内的边界索引
 *查询该区域内点的个数（利用可持久化线段树的版本差）
 *
*读取第一类点并进行坐标变换（切比雪夫距离转曼哈顿距离）
维护坐标范围
 *计算初始答案上界
 *读取第二类点并进行坐标变换
 *对X数组排序并去重
 *将第二类点按x坐标分组存储
 *构建可持久化线段树，fa[i]表示前i个x坐标版本的线段树根
 *二分查找每个第一类点到最近第二类点的距离
 *
 *时间复杂度约为O((n+k)log²(max_coordinate))，空间复杂度O(k log(max_coordinate))
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 2e5+5, inf = 2e8;
int n, k;
int px[N], py[N], sx[N], sy[N],
X[N], o, fa[N];
vector<int> s[N];
pair<int, int> a[N];

struct sgt {
    struct node { int lc, rc, sum; } tr[N*60];
    int tot;
    void insert(const int d, int& p, const int l=-inf, const int r=inf) {
        if (!p) p = ++tot, tr[p].sum = 1;
        else tr[++tot] = tr[p], p = tot, tr[p].sum++;
        if (l == r) return;
        const int mid = (l + r) >> 1;
        if (d <= mid) insert(d, tr[p].lc, l, mid);
        else insert(d, tr[p].rc, mid+1, r);
    }
    int query(const int u, const int v, const int p, const int l=-inf, const int r=inf) {
        if (!p) return 0;
        if (u <= l && r <= v) return tr[p].sum;
        const int mid = (l + r) >> 1;
        if (v <= mid) return query(u, v, tr[p].lc, l, mid);
        if (u > mid) return query(u, v, tr[p].rc, mid+1, r);
        return query(u, v, tr[p].lc, l, mid) + query(u, v, tr[p].rc, mid+1, r);
    }
} st;

bool ok(const int x1, const int x2, const int y1, const int y2) {
    const int l = static_cast<int>(lower_bound(X + 1, X + 1 + o, x1) - X),
    r = static_cast<int>(upper_bound(X + 1, X + 1 + o, x2) - X - 1);
    return st.query(y1, y2, fa[r]) - st.query(y1, y2, fa[l - 1]);
}


int main() {
    fast;
    cin >> n >> k;
    int mnx = inf, mxx = -inf, mny = inf, mxy = -inf;
    rep(i,n) {
        int x, y; cin >> x >> y;
        px[i] = x + y, py[i] = x - y;
        mnx = min(mnx, px[i]), mny = min(mny, py[i]);//维护坐标范围
        mxx = max(mxx, px[i]), mxy = max(mxy, py[i]);
    }
    const int ans = (max(mxx - mnx, mxy - mny) + 1) / 2;//上界
    rep(i,k) {
        int x, y; cin >> x >> y;
        sx[i] = x + y, sy[i] = x - y; X[i] = sx[i];
    }
    sort(X + 1, X + 1 + k);
    o = static_cast<int>(unique(X + 1, X + 1 + k) - X - 1);
    rep(i,k) {//将第二类点按x坐标分组存储
        const int j = static_cast<int>(lower_bound(X + 1, X + 1 + o, sx[i]) - X);
        s[j].push_back(i);
    }
    rep(i,o) {//构建可持久化线段树
        fa[i] = fa[i - 1];
        for (const int j : s[i]) st.insert(sy[j], fa[i]);
    }
    rep(i,n) {//二分查找每个第一类点到最近第二类点的距离
        int l = 0, r = inf;
        while (l < r) {
            const int mid = (l + r) >> 1;
            if (ok(px[i] - mid, px[i] + mid,
                py[i] - mid, py[i] + mid)) r = mid;
            else l = mid + 1;
        }
        a[i] = {l, i};
    }
    sort(a + 1, a + 1 + n, greater<>());//按距离降序排序第一类点
    int l = 0, r = ans;
    while (l < r) {
        const int mid = (l + r) >> 1;
        mnx = inf, mxx = -inf, mny = inf, mxy = -inf;
        bool flag = false;
        rep(i,n) {
            if (mid < a[i].first) {
                mnx = min(mnx, px[a[i].second] + mid),
                mxx = max(mxx, px[a[i].second] - mid);
                mny = min(mny, py[a[i].second] + mid),
                mxy = max(mxy, py[a[i].second] - mid);
                if (mxx > mnx || mxy > mny) break;
            } else {
                if (mxx <= mnx && mxy <= mny) {
                    const int w = mid - a[i].first;
                    if (ok(mxx - w, mnx + w, mxy - w, mny + w)) {
                        flag = true; break;
                    }
                }
                mnx = min(mnx, px[a[i].second] + mid),
                mxx = max(mxx, px[a[i].second] - mid);
                mny = min(mny, py[a[i].second] + mid),
                mxy = max(mxy, py[a[i].second] - mid);
            }
        }
        if (flag) r = mid; else l = mid + 1;
    }
    cout << l << '\n';
    return 0;
}