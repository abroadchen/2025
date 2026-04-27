//
// Created by Psy.C on 2026/4/26.
//
/**
树状数组更新操作
在位置x添加值y并将变化向上层传播
使用low_bit(x)高效地导航到父节点
实现区间更新操作[x, y]
使用差分数组技巧，使区间[x, y]内的值增加1
首先从x到末尾增加，然后从y+1到末尾减少
标准的树状数组前缀和查询
返回索引1到x元素的总和

n: 序列数量
m: 可能值的范围
num[2][N]: 存储两个交替使用的序列元素数组
cn: 当前数组索引(0或1)，用于在数组间切换
t: 存储前一个序列的元素数量
读取输入：n个序列，m作为最大值范围
读取第一个序列并初始化变量
cn ^= 1 在0和1之间切换以交替使用数组
flag 跟踪问题是否仍可解
处理剩余的n-1个序列
对于每个序列，逐个元素与前一个序列进行比较
情况1：当前元素 > 前一元素
如果num[cn][i] > num[cn^1][i]，我们要确保答案不在有问题的范围内
更新树状数组以反映满足条件的有效范围
情况2：当前元素 < 前一元素
处理当前元素小于前一元素的情况
相应地更新树状数组
情况3：元素相等
当所有被比较的元素都相等时
如果当前序列更短，将flag设为false（无解）
否则，将整个范围[1,m]添加为有效
如果flag仍为true（问题可解）：
检查每个可能的值，看它是否出现在所有约束中（在树状数组中出现n-1次）
输出最小的有效值(i-1)，如果没有解则输出-1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define low_bit(x) (x&-x)
using namespace std;
constexpr int N = 1e6+7, mod = 1e9+7;

int c[N];
void update(int x, int y, int n) {
    while (x <= n) { c[x] += y; x += low_bit(x); }
}

void modify(int x, int y, int n) {
    update(x, 1, n); update(y+1, -1, n);
}
int query(int x) {
    int ans = 0;
    while (x) { ans += c[x]; x -= low_bit(x); }
    return ans;
}

int n, m, num[2][N], cn, t;
int main() {
    fast;
    cin >> n >> m;
    int cnt; cin >> cnt;
    for (int i = 0; i < cnt; ++i) cin >> num[cn][i];
    t = cnt; cn ^= 1;
    bool flag = true;
    for (int k = 1; k <= n-1; ++k) {
        cin >> cnt;
        for (int i = 0; i < cnt; ++i) cin >> num[cn][i];
        if (flag) {
            bool tag = false;
            for (int i = 0; i < min(cnt, t); ++i) {
                if (num[cn][i] > num[cn^1][i]) {
                    tag = true;
                    modify(1, m-num[cn][i]+1, m+5);
                    modify(m-num[cn^1][i]+2, m, m+5);
                    break;
                }
                if (num[cn][i] < num[cn^1][i]) {
                    tag = true;
                    modify(m-num[cn^1][i]+2, m-num[cn][i]+1, m+5);
                    break;
                }
            }
            if (!tag) {
                if (t > cnt) flag = false;
                else modify(1, m, m+5);
            }
            t = cnt; cn ^= 1;
        }
    }
    int ans = -1;
    if (flag) {
        for (int i = 1; i <= m; ++i)
            if (query(i) == n-1) { ans = i-1; break; }
    }
    cout << ans << '\n';
    return 0;
}