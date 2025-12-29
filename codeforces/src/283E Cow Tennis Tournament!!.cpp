#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
#define N 100005
#define ls o<<1
#define rs (o<<1|1)
#define mid ((l+r)>>1)
using namespace std;

int sum[N<<2];//节点o的值为左右子节点之和
void maintain(const int o) { sum[o] = sum[ls] + sum[rs]; }

int len[N<<2];//存储每个节点对应区间的长度
void build(const int o, const int l, const int r) {
    len[o] = r - l + 1;//当前节点对应区间的长度
    if (l == r) { sum[o] = 1; return; }
    build(ls, l, mid); build(rs, mid+1, r);//递归构建左右子树
    maintain(o);//维护当前节点
}

int tag[N<<2];//用于区间更新
void work(const int o) { tag[o] ^= 1, sum[o] = len[o] - sum[o]; }
void pushdown(const int o) {
    if (tag[o]) {//如果当前节点有标记
        tag[o] = 0;
        work(ls), work(rs);//对左右子节点执行翻转操作
    }
}

int le, ri;//更新或查询的左右边界
void update(const int o, const int l, const int r) {
    if (l >= le && r <= ri) { work(o); return; }
    pushdown(o);
    if (le <= mid) update(ls, l, mid);//目标区间与左半部分有交集，更新左子树
    if (ri > mid) update(rs, mid+1, r);
    maintain(o);
}

int w;//存储查询结果
void query(const int o, const int l, const int r) {
    if (l >= le && r <= ri) { w += sum[o]; return; }
    pushdown(o);
    if (le <= mid) query(ls, l, mid);
    if (ri > mid) query(rs, mid+1, r);
}

int n, win[N];//n为元素个数，win数组记录每个位置的获胜次数
vector<int> l[N], r[N];//存储区间关系，l[y]存储所有在y区间左端点的x值
ll ans = 0;
void f() {
    build(1, 1, n);//根节点为1，区间为[1,n]
    for (int i = n; i; --i) {
        ri = i;
        for (int j = l[i].size() - 1; j >= 0; --j) {
            le = l[i][j], update(1, 1, n);//设置左边界，更新线段树
        }
        w = 0, le = 1, ri = i - 1;//重置w，设置查询区间为[1, i-1]
        if (le <= ri) query(1, 1, n);//如果区间有效，查询结果累加到w
        win[i] += w;//更新win[i]
    }
    memset(sum, 0, sizeof(sum));//重置sum数组
    memset(tag, 0, sizeof(tag));
    for (int i = 1; i <= n; ++i) {
        le = i;
        for (int j = r[i].size() - 1; j >= 0; --j) {//遍历r[i]中的所有元素
            ri = r[i][j], update(1, 1, n);
        }
        w = 0, le = i + 1, ri = n;
        if (le <= ri) query(1, 1, n);
        win[i] += w;
    }//减去所有win[i]中选2个的组合数
    for (int i = 1; i <= n; ++i) ans -= win[i] * 1ll * (win[i] - 1)>>1;
}


int main() {
    fast;
    int k, a[N], num[N]; cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i], num[i] = a[i];
    sort(num + 1, num + n + 1);//对num数组排序，用于离散化
    //将a[i]替换为其在排序后数组中的位置（离散化）
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(num + 1, num + n + 1, a[i]) - num;
    int x, y;
    while (k--) {
        cin >> x >> y;//读入区间[x,y]
        x = lower_bound(num + 1, num + n + 1, x) - num;//离散化x
        y = upper_bound(num + 1, num + n + 1, y) - num - 1;//离散化y（upper_bound返回第一个大于y的位置，所以要减1）
        if (!x || !y) continue;//如果x或y为0
        l[y].push_back(x), r[x].push_back(y);
    }
    ans = n * 1ll * (n - 1) * 1ll * (n - 2) / 6ll, f();
    cout << ans << '\n';
    return 0;
}
