//
// Created by Psy.C on 2026/9/17.
//
/**
区间更新：把区间 [l,r] 内的每个元素都执行 t[k]=min(t[k],x)
从根往下走到叶子，沿途把经过的每个节点的 t[k]（该区间被限制的最小值）取 min，就是点 x 的实际最小值约束。
因为前面 dfs 只是标记在覆盖节点上，所以查询需要"沿路径收集所有标记并取 min"
标准——但这里初始 t2 全为 -1（main 里 t2[i]=-1），所以 query 在没有任何更新时返回 -1。
作用是在处理操作 1 时，检查区间 [l,r] 内当前已设置的最大值 now
lim[i]：位置 i 的最终取值。
tag：标记某个 x 是否"在区间操作中以 min 身份出现过"（需要被实现）。
c：值→出现次数的计数表。
ans：用来做位运算构造
操作 1 语义：题目大概是"区间 [l,r] 内所有数都必须 ≤ x"（或类似）。query 拿区间最大值 now：

若 now > x：已设置的值超过新上限，矛盾 → NO。
若 now < x：区间还需要有元素等于 x（tag 记录）。
用 dfs 把区间取 min 记录上限。
操作 2 语义：把位置 x 设为 y。首次给某点设值时，若它还没最终值，先通过 ask 取出它的约束（min 下限）存入 lim[x]，再单点更新树2。
对从未被操作 2 设过值的点，用树 1 的 ask 取该点最小约束存入 lim[i]。
c[v] = 值 v 在 lim 中出现的次数。
tag 记录所有"需要在序列中出现"的 x；若某个 x 在最终 lim 中没出现（c 为 0），则无法实现 → NO。
到这里所有约束都满足，输出 YES。接下来是构造满足"每个 x 至少出现一次且 bitwise AND 最大"的序列
若有两个以上无约束点（inf），可以在其中一个放一个很大的数 (1<<29)-1（全 1 的 29 位），其余放 INF。这样能保证 bitwise AND 高位有 1。
(1<<29)-1 = 2^29-1，即低 29 位全 1。这样它贡献的 AND 结果会有 29 个高位置 1
遍历每个限制值 lim[i]。
c[lim[i]]--：用掉一个该值的名额。
若该值还有剩余名额（c[lim[i]] 仍 >0），说明这个位置不必保持 lim[i] 恰好，可以把它改成一个更有利 AND 的值：while(t<=lim[i]) t = t<<1|1 是找到大于 lim[i] 的最小形如 2^k-1 的数（全 1），再右移一位得 t>>1 = 2^(k-1)-1（比 lim[i] 小）。这大概是为了在高位置 1 的同时最小化对其它约束的影响。
ans |= lim[i]：记录所有已确定位置的 OR 值（推断后续作为 AND 的上界调整依据）
从高位到低位，把 tt 中 ans 缺失的位尽量置 1（但不能超过 INF），构造一个尽可能大的 tt。
无约束点（lim==inf，即上面 continue 跳过的那些）最后填上 tt。
这样构造出的序列每个 tag 要求的 x 都出现，且 bitwise AND 尽量大
 */
#include <ranges>
#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 3e5+5, inf = 2e9, INF = 1e9;

int t[N<<2];
void dfs(int k, int L, int R, int l, int r, int x) {//区间更新：把区间[l,r]与x取min
    if (L == l && R == r) { t[k] = min(t[k], x); return; }
    int mid = (L+R)>>1;
    if (r <= mid) dfs(k<<1, L, mid, l, r, x);
    else if (l > mid) dfs(k<<1|1, mid+1, R, l, r, x);
    else {//跨中点，拆两半
        dfs(k<<1, L, mid, l, mid, x);
        dfs(k<<1|1, mid+1, R, mid+1, r, x);
    }
}
//单点查询：返回点 x 的最终值（路径上所有 min 标记）
int ask(int k, int l, int r, int x) {
    int ret = t[k];
    while (l < r) {
        int mid = (l+r)>>1;
        if (x <= mid) r = mid, k = k<<1;
        else l = mid+1, k = k<<1|1;
        ret = min(ret, t[k]);
    }
    return ret;
}

int t2[N<<2];
void modify(int k, int l, int r, int x, int y) {//单点更新：把位置 x 的值设为 y
    if (l == r) { t2[k] = y; return; }
    int mid = (l+r)>>1;
    if (x <= mid) modify(k<<1, l, mid, x, y);
    else modify(k<<1|1, mid+1, r, x, y);
    t2[k] = max(t2[k<<1], t2[k<<1|1]);
}
//区间查询最大值
int query(int k, int L, int R, int l, int r) {
    if (L == l && R == r) return t2[k];
    int mid = (L+R)>>1;
    if (r <= mid) return query(k<<1, L, mid, l, r);
    if (l > mid) return query(k<<1|1, mid+1, R, l, r);
    return max(query(k<<1, L, mid, l, mid), query(k<<1|1, mid+1, R, mid+1, r));
}

int lim[N], opt, l, r, x, y, ans;
map<int, int> tag, c;
int main() {
    fast;
    int n, m; cin>>n>>m;
    for (int i = 1; i <= 4*n; ++i) t[i] = inf, t2[i] = -1;
    for (int i = 1; i <= n; ++i) lim[i] = inf+1;//lim初值inf+1表示"未定"
    while (m--) {
        cin>>opt;
        if (opt == 1) {//类型1：对区间加"上限约束 x"
            cin>>l>>r>>x;
            int now = query(1, 1, n, l, r);//区间内当前最大值
            if (now > x) { cout << "NO\n"; return 0; }//已设置的值超过新上限 → 无解
            if (now < x) tag[x] = 1;//还没达到 x，需标记 x 需被实现
            dfs(1, 1, n, l, r, x);//区间取 min 记录约束
        } else {//类型2：把位置 x 设为 y
            cin>>x>>y;
            if (lim[x] == inf+1) lim[x] = ask(1, 1, n, x);//若未定，先取该点约束
            modify(1, 1, n, x, y);//单点更新
        }
    }
    //处理结束后，把没"显式设值"过的点补上约束值
    for (int i = 1; i <= n; ++i)
        if (lim[i] == inf+1) lim[i] = ask(1, 1, n, i);
    for (int i = 1; i <= n; ++i) c[lim[i]]++;//统计每个 lim 值出现次数
    for (const auto key: tag | views::keys)//每个 tag 里的 x 都必须至少出现一次
        if (!c[key]) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    if (c[inf] >= 2) {//若至少有 2 个位置的 lim 是 inf（无穷/无约束）
        for (int i = 1; i <= n; ++i) {
            if (lim[i] == inf) { lim[i] = (1<<29)-1; break; }//把第一个 inf 设为 (2^29)-1
        }
        for (int i = 1; i <= n; ++i) {
            if (lim[i] == inf) lim[i] = INF;//其余 inf 设为 1e9
            cout << lim[i] << ' ';
        }
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        if (lim[i] == inf || lim[i] == 0) continue;//跳过无约束和 0 值点
        c[lim[i]]--;
        if (c[lim[i]]) {//若该值还有其他位置占用，则本点可以改小
            int t = 1;
            while (t <= lim[i]) t = t<<1|1;//求出 > lim[i] 的最小全1数…… 实际上求出最高位全1掩码
            lim[i] = t>>1;//取 t>>1（比 lim[i] 小但高位多的值）
        }
        ans |= lim[i];//累加 OR，用于后续 AND 优化
    }
    int tt = 0;
    for (int w = 29; w >= 0; w--) {
        if (ans&(1<<w)) continue;//若某位已经有了，跳过
        if (tt+(1<<w) <= INF) tt += 1<<w;//否则尝试把该位置 1（不超过 INF）
    }
    for (int i = 1; i <= n; i++) {
        if (lim[i] == inf) lim[i] = tt;//无约束点填 tt
        cout << lim[i] << ' ';
    }
    return 0;
}