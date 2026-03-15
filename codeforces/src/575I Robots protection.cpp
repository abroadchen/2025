//
// Created by Psy.C on 2026/3/15.
//
/**
N = 1e5+5：查询数量上限
M = 1e4+5：树状数组维度上限
n, m：树状数组的实际尺寸
c[M][M]：存储树状数组数据
clear()：清空数组，全部置为0
resize()：设置数组尺寸
在位置(x,y)添加值v（差分操作）
i += i&-i：找到下一个需要更新的位置（lowbit操作）
实现区间更新的差分思想
查询从(1,1)到(x,y)的矩形区域内所有值的和
i -= i&-i：向上查找贡献值
返回前缀和

n：网格大小
q：查询数量
dir[i]：操作类型（1-4表示添加矩形，5表示查询）
x[i], y[i]：坐标
len[i]：长度参数
ans[i]：存储查询结果
op=1：添加操作，读入方向dir和参数
op!=1：查询操作，设置dir[i]=5

类型1：在(x,y)到(x,y+len)的水平线段增加1
类型2：在(x,y-len)到(x,y)的水平线段增加1
类型3：在(x+1,y)到(x+1,y+len)的水平线段增加1
类型4：在(x+1,y-len)到(x+1,y+len)的水平线段增加1
类型5：查询点(x,y)的累积值

应用坐标变换：将斜向操作转换为直角坐标系
x-y 作为新的x坐标，保留y作为新y坐标
处理类型2和3的斜向覆盖操作

应用另一种坐标变换：x+y 作为新的x坐标
n-y+1 作为新的y坐标
处理类型1和4的斜向覆盖操作

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 1e4+5;

struct node {
    int n, m, c[M][M];
    void clear() { memset(c, 0, sizeof(c)); }
    void resize(int x, int y) { n = x; m = y; }
    void update(int x, int y, int v) {
        for (int i = x; i <= n; i += i&-i)
            for (int j = y; j <= m; j += j&-j)
                c[i][j] += v;
    }
    int query(int x, int y) const {
        int res = 0;
        for (int i = x; i >= 1; i -= i&-i)
            for (int j = y; j >= 1; j -= j&-j)
                res += c[i][j];
        return res;
    }
} bit;

int n, q, dir[N], x[N], y[N], len[N], ans[N];
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1, op; i <= q; ++i) {
        cin >> op;
        if (op == 1) cin >> dir[i] >> x[i] >> y[i] >> len[i];
        else cin >> x[i] >> y[i], dir[i] = 5;
    }
    bit.resize(n, n);
    for (int i = 1; i <= q; ++i) {
        if (dir[i] == 1) {
            bit.update(x[i], y[i], 1);
            bit.update(x[i], y[i]+len[i]+1, -1);
        } else if (dir[i] == 2) {
            bit.update(x[i], y[i]-len[i], 1);
            bit.update(x[i], y[i]+1, -1);
        } else if (dir[i] == 3) {
            bit.update(x[i]+1, y[i]+len[i]+1, 1);
            bit.update(x[i]+1, y[i], -1);
        } else if (dir[i] == 4) {
            bit.update(x[i]+1, y[i]+1, 1);
            bit.update(x[i]+1, y[i]-len[i], -1);
        } else if (dir[i] == 5) ans[i] += bit.query(x[i], y[i]);
    }
    bit.clear(); bit.resize(n+n, n);
    for (int i = 1; i <= q; ++i) {
        if (dir[i] == 2) {
            bit.update(x[i]-y[i]+len[i]+n+2, y[i]+1, 1);
            bit.update(x[i]-y[i]+len[i]+n+2, y[i]-len[i], -1);
        } else if (dir[i] == 3) {
            bit.update(x[i]-y[i]-len[i]+n+1, y[i], 1);
            bit.update(x[i]-y[i]-len[i]+n+1, y[i]+len[i]+1, -1);
        } else if (dir[i] == 5) ans[i] += bit.query(x[i]-y[i]+n+1, y[i]);
    }
    bit.clear(); bit.resize(n+n, n);
    for (int i = 1; i <= q; ++i) {
        if (dir[i] == 1) {
            bit.update(x[i]+y[i]+len[i]+1, n-y[i]+2, 1);
            bit.update(x[i]+y[i]+len[i]+1, n-y[i]-len[i]+1, -1);
        } else if (dir[i] == 4) {
            bit.update(x[i]+y[i]-len[i], n-y[i]+1, 1);
            bit.update(x[i]+y[i]-len[i], n-y[i]+len[i]+2, -1);
        } else if (dir[i] == 5) ans[i] += bit.query(x[i]+y[i], n-y[i]+1);
    }
    for (int i = 1; i <= q; ++i)
        if (dir[i] == 5) cout << ans[i] << '\n';
    return 0;
}