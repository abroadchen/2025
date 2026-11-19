//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
合并左右子节点（求和）
第 t 个离散点增加 x（插入 +值，删除 -值）
查询 [L,R] 内的权值和，标准线段树区间查询，左右都不越界时剪枝返回节点和
把实际值 x 映射成线段树里的离散下标。
注意 b 是原样（可重复）排序后的，所以 find 返回的是右侧边界，用于把"小于等于 x 的所有值"整体定位（线段树范围 1..find(x) 即所有 ≤ x 的元素所处位置区间）
读入 Q 个操作（+=插入, -=删除），x 存入数组，排序 b 作为坐标轴
cnt：当前总元素个数。
st：multiset（存实际值，方便取最小/最大/二分）。
插入：权值树在 find(x) 位置累加 x；删除同理减去。
少于 2 个元素时，无法分组，输出 0。
初始 ans = cnt-1：假设最坏情况每个元素自成组，组数 = 元素数 - 1（因为分组定义上要减 1）。
z 当前分组的"最小元素"，从全局最小开始。
内层 while 的条件：quan = tr.qry(1,1,n,1,find(z)) 表示"所有值 ≤ z 的元素总和"。只要 2×quan < 全局最大值，说明当前小组的上限还能容纳更大元素，继续分组。
取第一个 > 阈值的元素 x（用 upper_bound），y 是它前一个、即“刚好 ≤ 阈值”的最后元素。若前一个元素的累积和 2×qry(...find(*y)) < x，说明 y 这层能并进去因而总组数可减 1（ans--）。
更新 z = *x 继续下一层。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); i++)
#define mid ((l+r)>>1)
#define int long long
using namespace std;

constexpr int N = 5e5+5;

struct sgt {
    int tr[N<<2];
    void push_up(int x) { tr[x] = tr[x<<1] + tr[x<<1|1]; }
    void upd(int u, int l, int r, int t, int x) {
        if (l == r) { tr[u] += x; return; }
        if (t <= mid) upd(u<<1,l,mid,t,x);
        else upd(u<<1|1,mid+1,r,t,x);
        push_up(u);
    }
    int qry(int u, int l, int r, int L, int R) {
        if (L <= l && r <= R) return tr[u];
        int ans = 0;
        if (mid >= L) ans += qry(u<<1,l,mid,L,R);
        if (mid < R) ans += qry(u<<1|1,mid+1,r,L,R);
        return ans;
    }
} tr;

struct node { char c; int x; } q[N];

int Q, b[N];
int find(int x) {
    int l = 1, r = Q;
    while (l < r) {
        if (x < b[mid]) r = mid; else l = mid+1;
    }
    return r;
}

multiset<int> st;
signed main() {
    fast;
    int n = N-5, cnt = 0; cin >> Q;
    rep(i,Q) { cin >> q[i].c >> q[i].x; b[i] = q[i].x; }
    sort(b+1,b+1+Q);
    rep(i,Q) {
        if (q[i].c == '+') {
            cnt++; st.insert(q[i].x);
            tr.upd(1,1,n,find(q[i].x), q[i].x);
        } else {
            cnt--; st.erase(st.lower_bound(q[i].x));
            tr.upd(1,1,n,find(q[i].x),-q[i].x);
        }
        if (st.size() < 2) { cout << "0\n"; continue; }
        int ans = cnt-1, z = *st.begin();
        while (tr.qry(1,1,n,1,find(z))*2 < *st.rbegin()) {
            auto x = st.upper_bound(tr.qry(1,1,n,1,find(z))*2);
            auto y = x; --y;
            if (tr.qry(1,1,n,1,find(*y))*2 < *x) ans--;
            z = *x;
        }
        cout << ans << '\n';
    }
    return 0;
}