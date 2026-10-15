//
// Created by Psy.C on 2026/10/15.
//
/**
inf：一个很大的 64 位上限值（0x3f...f），用作初始"最小值"哨兵。
get(x)：返回 x 的二进制最高位（最高有效位索引）‍
逐次右移计数，结束时 res-1 即为最高位所在位下标（如 x=8(1000) → res=4 → 返回 3）。结果范围 0-62 左右。

b[N]：原始输入数组。
ans[N]：构造出的合法顺序结果。
queue<int> q[N]：按最高位索引分桶的队列，q[k] 存所有最高位为 k 的数
遍历找出数值最小的元素 b[p]，记为 now，p 是它的位置
除最小元素外，其余每个数按最高位 get(b[i]) 放入对应队列。
第一个输出元素取全局最小数（最高位最低），ans[1]=now，当前前缀异或 now，其最高位为 x。
把最高位最低的数放首位是合理策略：它不会与后面数"进位冲突"得太多
对第 2～n 个位置循环，目标是：每次选择下一个数，使得新的前缀异或 now ^= 某个数 的最高位更高（保持线性无关）‍，具体分两步找候选：

第 1 步：找当前 now 中"从低位起第一个为 0 的位" pos
pos 从 0 递增扫描到 x-1（即比当前最高位 x 低的位置）。
条件是 pos 这一位要么没有对应分桶的数（q[pos].empty()），要么 当前 now 的这一位已经是 1。
翻译：要在 now 中找一个当前为 0 的空位 pos，且该位有可用的数（q[pos] 非空），把那个数异或进来就能把 now 的这一位从 0 变 1，从而抬高前缀异或的最高位，保证线性无关。
找到的 pos 满足 pos <= x-1 且有候选。
第 2 步：低位找不到合适空位，就尝试"跳更高位"
如果低位（0-x-1）都没有"可用且当前位为 0"的候选，说明无法在低位增量。
于是跳到比当前最高位 x 更高的位 p2=x+1 往上找第一个非空的分桶 q[p2]。
若一路找到 >60 都没有（超出合理位数），则无解，输出 No。
否则取 q[p2] 队首元素异或进 now，记录到 ans[i]，弹出，并更新最高位 x=p2（因为选了更高位的数，最高位抬高了）。
否则（低位找到合法 pos）：取该桶队首
低位找到了合适的 pos，取 q[pos] 队首元素异或进 now，记录并弹出（最高位 x 不变或视情况）
若能完整填满 n 个位置都没触发 No，输出 Yes 并按构造顺序打印 ans[1..n]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define int long long
using namespace std;

constexpr int N = 1e5+10, inf = 0x3f3f3f3f3f3f3f3f;

int get(int x) {
    int res = 0;
    while (x > 0) { res++; x>>=1; }
    return res-1;
}

int n, b[N], ans[N];
queue<int> q[N];
signed main() {
    fast;
    cin >> n;
    int now = inf, p = 0;
    rep(i,1,n) {
        cin >> b[i];
        if (b[i] < now) { now = b[i]; p = i;}
    }
    rep(i,1,n) if (i != p) q[get(b[i])].push(b[i]);
    ans[1] = now;
    int x = get(now);
    rep(i,2,n) {
        int pos = 0;
        while ((q[pos].empty() || now>>pos&1) && pos <= x-1) pos++;
        if (pos > x-1) {
            int p2 = x + 1;
            while (q[p2].empty() && pos <= 60) p2++;
            if (p2 > 60) { cout << "No"; return 0; }
            now ^= q[p2].front();
            ans[i] = q[p2].front();
            q[p2].pop();
            x = p2;
        } else {
            now ^= q[pos].front();
            ans[i] = q[pos].front();
            q[pos].pop();
        }
    }
    cout << "Yes\n";
    rep(i,1,n) cout << ans[i] << ' ';
    return 0;
}