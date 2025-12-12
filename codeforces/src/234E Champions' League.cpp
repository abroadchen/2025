//
// Created by Psy.C on 2025/12/12.
//
/*
 *
 *n(队伍总数)、x(随机种子)、q1,q2,q3(线性同余生成器参数)
 *node，包含整型x(分数，默认初始化为0)和字符串y(队名)
 *
*循环处理小组内的4个队伍
j是当前抽取的第几个队伍(1-4)
k是当前已找到的未被选中队伍计数器(初始化为0)
s和m是临时变量
 *
*循环查找第m+1个未被选中的队伍
边界检查：确保s不超过数组范围
如果f[s]为0(未被选中)，k计数器加1
当k等于m+1时，找到目标队伍，跳出循环
否则s递增继续查找
 *
*如果s在有效范围内：
标记队伍s已被选中(f[s] = 1)
输出选中队伍的名称
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n, x, q1, q2, q3; cin >> n >> x >> q1 >> q2 >> q3;
    struct node { int x{}; string y; } a[N];
    for (int i = 1; i <= n; ++i) cin >> a[i].y >> a[i].x;
    sort(a + 1, a + 1 + n, [](const auto& l, const auto& r) {
        return l.x > r.x;
    });
    int f[N] = {};
    for (int i = 1; i <= n / 4; ++i) {//每4个队伍一组
        cout << "Group " << static_cast<char>('A' + i - 1) << ':' << '\n';
        for (int j = 1, k = 0, s, m; j <= 4; ++j) {
            x = static_cast<int>((1ll * x * q1 + q2) % q3);//生成下一个随机数
            s = (j - 1) * n / 4 + 1;//计算起始搜索位置，指向当前小组的第一个队伍
            m = x % (n / 4 - i + 1);//当前轮次要选取第几个未被选中的队伍
            k = 0;//重置计数器k为0，重新开始计数
            while (s <= n) {
                if (!f[s]) { k++; if (k == m + 1) break; }
                s++;
            }
            if (s <= n) {
                f[s] = 1;
                cout << a[s].y << '\n';
            }
        }
    }
    return 0;
}