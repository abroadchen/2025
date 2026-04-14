//
// Created by Psy.C on 2026/4/13.
//
/**
树状数组
b: 辅助数组
k: 限制值
mxb: 区间最大值
mx_b: 带标记的最大值
tag: 懒惰标记
mxd: 特殊维护的值

add: 给节点加标记
pushdown: 下传懒惰标记
查找第一个大于等于v的位置
计算特定条件下的最大差值
push_up: 更新父节点
build: 构建线段树
update: 区间更新
query: 区间查询
同时更新线段树和树状数组

使用单调栈处理序列
动态维护相关信息
二分查找满足条件的右边界
计算最长满足条件的区间长度
读入权重数组w和收益数组g
计算前缀差值数组a和b


stk: 单调栈，用于维护序列中的关键位置
st.build(1, 1, n): 构建线段树
st.update(1, 1, n, 1, n, -inf): 将整个区间初始化为负无穷
b[0] = -inf: 设置边界条件
top = 0: 栈顶指针
ans = 0: 最长合法区间长度
从右到左遍历每个位置i
维护a数组的单调递减栈
当a[stk[top]] <= a[i]时弹栈：
如果栈中至少有2个元素，更新区间信息
update(stk[top-1]-1, -(a[stk[top-1]]-a[stk[top]]))：撤销之前的增量
将当前位置i压入栈
如果栈中有多于1个元素，更新区间信息
update(stk[top-1]-1, a[stk[top-1]]-a[stk[top]])：在[stk[top-1], i-1]区间添加差值
st.update(1, 1, n, i, i, inf): 将位置i设为无穷大（标记起始位置）
使用二分查找找到满足条件的最远右边界
bt.query(mid-1) <= k: 检查区间[i, mid-1]的权值和是否不超过k
mxr: 最远可达的右边界
st.update(1, 1, n, mxr, n, inf): 将[mxr, n]区间设为无穷大
st.query(1, 1, n, -inf): 查询从-inf开始满足条件的最远位置
ans = max(ans, ...): 更新最长区间长度
st.update(1, 1, n, mxr, n, -inf): 恢复区间状态（设为负无穷）


情况1: 当mx >= mx_b[x<<1]时：
mx_b[x<<1]是左子树的最大值（带标记）
如果参考值mx大于等于左子树最大值，说明：
mx - b[i]（i在左子树）的最大值是 mx - mx_b[x<<1] 的相反数
实际上是 mxb[x<<1] - mx（因为我们要找的是正的最大差值）
返回 max(mxb[x<<1]-mx, 右子树递归结果)
左子树中的最大值与参考值mx的差值，和右子树的递归结果取最大值
情况2: 当mx < mx_b[x<<1]时：
参考值mx小于左子树最大值
返回 max(mxd[x], get2(x<<1, l, mid, mx))
mxd[x]是预计算好的跨中点最大差值
get2(x<<1, l, mid, mx)是在左子树中继续寻找
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e5+5, inf = 1e18;
int n;
struct bit {
    int c[N];
    void update(int x, int v) {
        for (; x <= n; x += x&-x) c[x] += v;
    }
    int query(int x) {
        int ret = 0;
        for (; x; x -= x&-x) ret += c[x];
        return ret;
    }
} bt;

int b[N], k;
struct sgt {
    int mxb[N<<2], mx_b[N<<2], tag[N<<2], mxd[N<<2];
    void add(int x, int l, int r, int v) {
        mx_b[x] += v, tag[x] += v, mxd[x] -= v;
    }
    void pushdown(int x, int l, int r) {
        if (tag[x]) {
            int mid = (l+r)>>1;
            add(x<<1, l, mid, tag[x]), add(x<<1|1, mid+1, r, tag[x]);
            tag[x] = 0;
        }
    }
    int get(int x, int l, int r, int v) {
        if (mxb[x] < v) return 0;
        if (l == r) return l;
        int mid = (l+r)>>1;
        if (mxb[x<<1|1] >= v) return get(x<<1|1, mid+1, r, v);
        return get(x<<1, l, mid, v);
    }
    int get2(int x, int l, int r, int mx=-inf) {
        if (l == r) return b[l] - mx;
        pushdown(x, l, r);
        int mid = (l+r)>>1;
        if (mx >= mx_b[x<<1])
            return max(mxb[x<<1]-mx, get2(x<<1|1, mid+1, r, mx));
        return max(mxd[x], get2(x<<1, l, mid, mx));
    }
    void push_up(int x, int l, int r) {
        mxb[x] = max(mxb[x<<1], mxb[x<<1|1]);
        mx_b[x] = max(mx_b[x<<1], mx_b[x<<1|1]);
        if (l != r) {
            int mid = (l+r)>>1;
            mxd[x] = get2(x<<1|1, mid+1, r, mx_b[x<<1]);
        }
    }
    void build(int x, int l, int r) {
        if (l == r) return void(mxb[x] = mx_b[x] = b[l]);
        int mid = (l+r)>>1;
        build(x<<1, l, mid), build(x<<1|1, mid+1, r);
        push_up(x, l, r);
    }
    void update(int x, int l, int r, int ql, int qr, int v) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) return add(x, l, r, v);
        pushdown(x, l, r);
        int mid = (l+r)>>1;
        update(x<<1, l, mid, ql, qr, v), update(x<<1|1, mid+1, r, ql, qr, v);
        push_up(x, l, r);
    }
    int query(int x, int l, int r, int mx) {
        if (l == r) return mx - b[l] <= k ? l : 0;
        pushdown(x, l, r);
        int mid = (l+r)>>1;
        if (mx >= mx_b[x<<1])
            return max(get(x<<1, l, mid, mx-k), query(x<<1|1, mid+1, r, mx));
        if (mxd[x] >= -k) return query(x<<1|1, mid+1, r, mx_b[x<<1]);
        return query(x<<1, l, mid, mx);
    }
} st;

void update(int x, int v) {
    st.update(1, 1, n, x, n, v);
    bt.update(x, v);
}

int a[N];
void out() {
    static int stk[N];
    st.build(1, 1, n); st.update(1, 1, n, 1, n, -inf); b[0] = -inf;
    int top = 0, ans = 0;
    for (int i = n; i; --i) {
        for (; top && a[stk[top]] <= a[i]; --top)
            if (top > 1)
                update(stk[top-1]-1, -(a[stk[top-1]]-a[stk[top]]));
        stk[++top] = i;
        if (top > 1) update(stk[top-1]-1, a[stk[top-1]]-a[stk[top]]);
        st.update(1, 1, n, i, i, inf);
        int L = i - 1, R = n + 1, mxr = i - 1;
        while (L + 1 < R) {
            int mid = (L + R)>>1;
            if (bt.query(mid-1) <= k) L = mxr = mid; else R = mid;
        }
        st.update(1, 1, n, mxr, n, inf);
        ans = max(ans, st.query(1, 1, n, -inf) - i + 1);
        st.update(1, 1, n, mxr, n, -inf);
    }
    cout << ans << '\n';
}

int w[N], g[N];
signed main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i < n; ++i) cin >> w[i];
    for (int i = 1; i <= n; ++i) cin >> g[i];
    for (int i = 1; i <= n; ++i) {
        a[i] = a[i-1] + w[i-1] - g[i-1];
        b[i] = b[i-1] + g[i] - w[i-1];
    }
    out();
    return 0;
}