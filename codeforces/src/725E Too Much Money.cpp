//
// Created by Psy.C on 2026/4/25.
//
/**
c: 总金额上限
n: 面额种类数
val[N]: 原始面额数组
v[N]: 去重后的面额数组
sum[N]: 每种面额的数量
s[N]: 预处理结果数组

对面额进行排序
去重并统计每种面额的数量
v[cnt]存储不同面额，sum[cnt]存储对应数量
从大面额开始，贪心地使用尽可能多的大面额
s[i]记录使用完面额v[i]及更大面额后剩余的钱数

pos = 2: 从第2个面额开始（因为循环从v[1]+1开始，所以v[1]是最小面额）
ans = 0: 记录答案（第一个无法凑出的金额）
flag = 0: 标记是否找到了答案
从最小面额+1开始枚举
为什么从v[1]+1开始？因为v[1]是最小面额，一定能用一个v[1]凑出v[1]
找到第一个≥ i的面额位置
pos左侧(pos-1及更小)都是< i的面额
pos及右侧都是≥ i的面额
s[pos]是预处理数组，表示从面额v[pos]开始使用后的剩余金额
如果pos <= cnt，使用预计算的剩余金额；否则使用全部金额c


排序: O(n log n)
预处理: O(cnt)
主循环: O(c × cnt)
总体: O(n log n + c × cnt)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+7;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int c, n, val[N], v[N], sum[N], s[N];
int main() {
    fast;
    c = rd(), n = rd();
    for (int i = 1; i <= n; ++i) val[i] = rd();
    sort(val + 1, val + n + 1);
    int tot = 1, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (val[i] == val[i+1]) ++tot;
        else v[++cnt] = val[i], sum[cnt] = tot, tot = 1;
    }
    int x = c;//从总金额c开始
    for (int i = cnt; i >= 1; --i) {//从最大的面额开始（v[cnt]是最大面额）
        if (v[i] <= x) {//当前面额 ≤ 剩余金额，可以使用
            int k = x/v[i];
            k = min(k, sum[i]);
            x -= k*v[i];
            s[i] = x;//记录使用完面额v[i]后剩余的金额
        } else s[i] = x;//当前面额 > 剩余金额，无法使用，剩余金额不变
    }
    int pos = 2, ans = 0; bool flag = 0;
    for (int i = v[1]+1; i <= c; ++i) {
        while (i > v[pos] && pos <= cnt) ++pos;//找到合适的位置 找到第一个 v[pos] >= i 的位置
        int x = c;
        if (pos <= cnt) x = s[pos]; else x = c;//获取可用金额
        bool tag = 0;
        if (i > x) continue;//金额不够
        x -= i;//使用面额i
        if (x == 0) continue;//用完所有钱
        for (int j = pos-1; j >= 1; --j) {//尝试用剩余面额凑出x 只使用< i的面额
            if (v[j] <= x) {
                int k = x/v[j];//最多能用几个面额为v[j]的硬币
                k = min(k, sum[j]);//不能超过可用数量
                x -= k*v[j];//减去这些硬币的价值
            }
            if (x == 0) { tag = 1; break; }// 剩余金额为0 成功凑出
        }
        if (!tag) { flag = 1; ans = i; break; }//无法凑出，找到答案
    }
    if (!flag) {
        cout << "Greed is good\n";
        return 0;
    }
    cout << ans << '\n';
    return 0;
}