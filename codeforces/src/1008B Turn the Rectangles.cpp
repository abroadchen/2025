//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
n：对数。
mx：上一步选中的值（也是后续可选的上限）。
初始化为 1e9+9（极大值）‍，含义是：第一步没有任何约束，任何 x,y 都小于等于这个"上一步"值，所以第一步总能选一个
读 n，然后每轮读一对候选 x, y（每个 i 都重新声明 x, y）
这一对的两个数都大于上一轮选的值 mx。
因为规则要求"当前选的值 ≤ 上一轮值"（不上升序列），此时无论选 x 还是 y 都会超过 mx，无法满足 → 输出 NO 并结束。
这是唯一的"失败"出口
若 x > mx 但 y <= mx：只有 y 可选（x 超过上限），把上限更新为 y。
若 y > mx 但 x <= mx：只有 x 可选，把上限更新为 x。
这两种情况是"二选一被迫"，选那个合法的（≤mx 的）
若 x<=mx 且 y<=mx：两个都可行候选。
贪心策略：选较大的那个 max(x,y) 作为新的 mx。
为什么选大的：因为后续每步只要求"≤ 当前 mx"，mx 越大，对后续候选的约束越宽松，越容易全部成功。所以尽量把"较大值"留到前面用（先花掉大的），让小值留在后面
所有 n 对都成功选出了一个 ≤ 上一轮的合法值 → 输出 YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, mx = 1e9+9;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if (x > mx && y > mx) { cout << "NO\n"; return 0; }
        if (x > mx) mx = y;
        else if (y > mx) mx = x;
        else mx = max(x, y);
    }
    cout << "YES\n";
    return 0;
}