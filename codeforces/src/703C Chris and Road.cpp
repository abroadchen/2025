//
// Created by Psy.C on 2026/4/18.
//
/**
n: 障碍物或检查点数量
w: 总距离或总高度
vb: 速度B（可能是步行速度或其他）
vp: 速度P（可能是传送或特殊通道速度）
ans: 存储最优答案
x, y: 当前检查点的坐标
f1 = 1, f2 = 1: 两个标志位，初始都为1
x/vb: 从起点到x位置的速度B的耗时
y/vp: 从起点到y位置的速度P的耗时
如果B方式更慢(f2=0)，说明B永远不是最优选择
如果B方式更快(f1=0)，说明P永远不是最优选择
x/vb: 用速度B走到x位置的时间
(w-y)/vp: 从y位置用速度P走到终点的时间
这表示一种混合策略：先用B走到某个检查点，再用P完成剩余路程
f1 + f2 > 0: 如果f1和f2不全为0
说明存在某种情况下某一种方式总是最优的
直接输出w/vp（全程用P方式）
f1 + f2 == 0: 如果f1和f2都为0
说明两种方式各有优势，需要考虑混合策略
输出ans（最优混合策略）
O(n): 遍历所有检查点一次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
double w, vb, vp, ans, x, y;
int main() {
    fast;
    cin >> n >> w >> vb >> vp;
    int f1 = 1, f2 = 1;
    while (n--) {
        cin >> x >> y;
        if (x/vb > y/vp) f2 = 0;
        if (x/vb < y/vp) f1 = 0;
        ans = max(ans, x/vb+(w-y)/vp);
    }
    if (f1 + f2 > 0) printf("%.8lf\n", w/vp);
    else printf("%.8lf\n", ans);
    return 0;
}