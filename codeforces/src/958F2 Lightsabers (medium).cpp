//
// Created by Psy.C on 2026/10/20.
//
/**
cnt[a[i]]：值 a[i] 在完整数组中的出现次数（初始）。
k[i]：目标——值 i 应达到的数量。
t[i]：临时暂存数组，用来保存 cnt 的"完整状态"
check(x) 尝试寻找一个可行方案：删除"前一段"与"后一段"总共恰好 x+? 个元素（使得剩余部分每种值都不少于 k[i]）。

第一阶段：假设删除最前面的 x 个元素。维护 flg = "当前有多少个值比目标 k 少 1"（即差一点达标的值个数）。如果删完前 x 个后 flg==0（所有值都不少于 k），说明可行。
第二阶段：如果不行，则逐步把"前段删除"替换为"后段删除"——每次恢复一个前段元素（cnt[a[x-i+1]]++），同时删掉一个末尾元素（cnt[a[n-i+1]]--），并同步更新 flg。这个滑动过程考察"前删 i 个 + 后删 (x-i) 个"的所有组合，一旦某时刻 flg==0 即可行。
本质是一个双窗口滑动：前段删的越少，后段删的越多，扫描所有拆分点，看是否存在一个合法配置

读入数组，统计每种值在完整数组中的总数 cnt[]，并把 ans 也初始化为总数。
读入目标 k[]。
可行性预检：如果某个目标 k[i] 超过其完整总数 cnt[i]，则无论怎么删都不够，直接输出 -1
二分查找可删除的最大数量。check(mid) 可行说明"删除到剩余 mid+? 个"仍能满足，于是尝试更大的 mid（删得更少？），否则缩小。
注意 check 内部会修改 cnt，所以每次调用后统一恢复 cnt 为完整状态（用 t[]）。真正要保留的"最佳可行频数"被存进 ans[]。
ans[a[i]] = cnt[a[i]] 记录在当前二分可行解下各值的频数（即"最终要保留每种值多少个"的最优方案）
对每种值 i，计算 ans[i] - k[i]（保留下来的数量减去达标所需数量），累加到 res；用 -1 标记已处理避免重复计数。res 表示"在所有值都达标的前提下，最多还能额外保留/删除的量"——具体语义取决于题目，但可理解为"满足条件后剩余可自由处理的元素个数"或"最小删 k 后能节省的操作数"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+10;

int n, t[N], a[N], cnt[N], k[N];
int check(int x) {
    int flg = 0;
    rep(i,n) t[a[i]] = cnt[a[i]];//保存当前 cnt 完整状态
    rep(i,x) {//模拟"删掉前 x 个元素"
        cnt[a[i]]--;//前 x 个元素被删除，频数-1
        if (cnt[a[i]] == k[a[i]]-1) flg++;//若某个值降到"差一点达标"，计入 flg
    }
    if (flg == 0) return 1;//前 x 个删除后所有值都>=k => 可行
    rep(i,x) {//再删末尾的若干元素，同时"恢复"被误删的前段
        cnt[a[x-i+1]]++;//恢复前面第 i 个被删元素
        if (cnt[a[x-i+1]] == k[a[x-i+1]]) flg--;
        cnt[a[n-i+1]]--;//删除末尾第 i 个元素
        if (cnt[a[n-i+1]] == k[a[n-i+1]] - 1) flg++;
        if (flg == 0) return 1;//达标即可行
    }
    return 0;
}

int m, ans[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i], cnt[a[i]]++, ans[a[i]]++;
    rep(i,m) cin >> k[i];
    rep(i,m) if (k[i] > cnt[i]) { cout << -1; return 0; }
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid)) {
            l = mid+1;
            rep(i,n) ans[a[i]] = cnt[a[i]];
            rep(i,n) cnt[a[i]] = t[a[i]];
        } else {
            r = mid-1;
            rep(i,n) cnt[a[i]] = t[a[i]];
        }
    }
    int res = 0;
    rep(i,n) if (ans[a[i]] != -1) {
        res += ans[a[i]] - k[a[i]];
        ans[a[i]] = -1;
    }
    cout << res;
    return 0;
}