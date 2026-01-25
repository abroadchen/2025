//
// Created by Psy.C on 2026/1/23.
//
/**
* n: 物品数量
m: 轮数
s[N]: 物品价值（按降序排序）
wa[state], wb[state]: 当前和下一状态的DP数组
a[i]: 动作类型('b'或其他)
t[i]: 目标(1或其他值)
nb, b: 指向当前和下一个DP数组的指针
 *
*从最后一轮向第一轮迭代
fill_n(nb, state, ...): 用适当的无穷值初始化下一个状态数组
对于恰好有i个位设置的每个状态st：
尝试添加每个未使用的物品j(其中位j为0)
基于动作类型更新DP表：
如果a[i][0] == 'b': 直接传递值
否则: 加/减物品价值s[j]
基于目标类型使用min/max进行最佳策略
 *
 *输出当没有选择任何物品时(状态0)的最终结果
 *
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100
#define inf 2147483647
using namespace std;

constexpr int state = 1<<20;

int get(int n) {
    int ans = 0;
    for (; n; ans++) n &= n - 1;//移除最低的设置位
    return ans;
}

int main() {
    fast;
    int n, m, i; cin >> n;
    int s[N], wa[state], wb[state];
    for (i = 0; i < n; ++i) cin >> s[i];
    sort(s, s + n, greater<>());
    cin >> m;
    char a[20][2]; int t[20], *nb = wb, *b = wa;//滚动数组优化
    for (i = 0; i < m; ++i) cin >> a[i] >> t[i];
    for (i = m - 1; i >= 0; --i) {
        fill_n(nb, state, t[i] == 1 ? -inf : inf);//填充数组nb的前state个元素
        for (int st = 0; st < state; ++st) {
            if (get(st) != i) continue;//状态st中1的个数不等于轮数i
            for (int j = 0; j < m; ++j) {//遍历所有物品j
                if ((st & (1<<j)) == 0) {//状态st的第j位是否为0（物品j未被选）
                    const int x = st | (1<<j);//将第j位置为1
                    if (a[i][0] == 'b') {//当前轮的动作类型是'b'
                        if (t[i] == 1) nb[st] = max(nb[st], b[x]);
                        else nb[st] = min(nb[st], b[x]);
                    } else {
                        if (t[i] == 1) nb[st] = max(nb[st], b[x] + s[j]);
                        else nb[st] = min(nb[st], b[x] - s[j]);
                    }
                }
            }
        }
        swap(b, nb);//滚动数组优化技巧，节省空间
    }
    cout << b[0];//初始状态（无物品被选）的最终得分
    return 0;
}