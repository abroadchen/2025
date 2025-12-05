//
// Created by Psy.C on 2025/12/6.
//
/*
*N = 1000000：最大数组大小
M = 600000：中间数组大小
K = 30：用于稀疏表的最大指数范围
*g[N]：预计算log2的整数部分
a[M]：存储处理后的数组元素
st[M][K]：稀疏表(Sparse Table)，用于区间最值查询
 *
*预计算每个数字的log2整数部分：
g[0]和g[1]设置为0
对于其他数字i，g[i] = g[i/2] + 1，这实际上是floor(log2(i))
 *
*第一层(j=0)：st[i][0] = i，表示位置i本身
对于更高层：st[i][j]存储区间[i, i+2^j-1]中使得a值最小的位置
比较两个子区间的结果：[i, i+2^(j-1)-1] 和 [i+2^(j-1), i+2^j-1]
选择a值较小的那个区间的最优位置
 *
*t = floor(log2(r-l+1))，确定查询所需的稀疏表层级
比较两个可能重叠的区间：[l, l+2^t-1] 和 [r-2^t+1, r]
返回其中a值较小的位置索引
 *
*l：当前可到达的最左位置
r：当前所在位置
cnt：跳跃次数，初始为1
 *
*在区间[l, r-1]中找到使a值最小的位置t
更新l为从位置t能跳转到的最左位置
更新r为当前位置t
跳跃次数加1
 *
 *
*区间 [i, i + 2^j - 1] 长度为 2^j
可以分成两个长度为 2^(j-1) 的子区间：
├── 左半区间: [i, i + 2^(j-1) - 1] 长度为 2^(j-1)
└── 右半区间: [i + 2^(j-1), i + 2^j - 1] 长度为 2^(j-1)
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6, M = 6e5, K = 30;
int g[N], a[M], st[M][K];

void init(const int n) {
    g[0] = g[1] = 0;
    for (int i = 2; i <= n; ++i) g[i] = g[i/2] + 1;
}

void build(const int n) {
    for (int i = 0; i <= n; ++i) st[i][0] = i;
    for (int j = 1; j <= g[n] + 1; ++j) for (int i = 0; i <= n; ++i) {
        st[i][j] = a[st[i][j-1]] <= a[st[i+(1<<(j-1))][j-1]] ?
            st[i][j-1] : st[i+(1<<(j-1))][j-1];
    }
}
int query(const int l, const int r) {
    const int t = g[r - l + 1];
    return a[st[l][t]] <= a[st[r-(1<<t)+1][t]] ?
        st[l][t] : st[r-(1<<t)+1][t];
}

int main() {
    fast;
    int n; cin>>n; init(2 * n);
    for (int i = 1; i <= n; ++i) cin>>a[i], a[i+n] = a[i];//复制一份到后n个位置，形成循环数组
    for (int i = 1; i <= n + n; ++i) a[i] = max(i-a[i], 1);//从位置i能跳转到的最远左边界
    build(2 * n); int ans = 0;
    for (int i = 1; i <= n; ++i) {//对每个起始位置进行计算
        int l = a[i + n - 1], r = i + n - 1, cnt = 1;
        while (i < l) {//还没到达目标位置i时继续跳跃
            const int t = query(l, r - 1);
            l = a[t], r = t;
            cnt++;
        }
        ans += cnt;//将本次计算的跳跃次数加到总答案中
    }
    cout << ans;
    return 0;
}