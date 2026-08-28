//
// Created by Psy.C on 2026/8/28.
//
/**
纵向轨道的长度上限 （轨道的有效纵向位置范围是 0 ≤ num ≤ N ）。 constexpr 保证常量在 编译期确定 ，比 #define 更安全（有类型检查、不占用运行时内存）
读入 指令的总条数 n （后续会处理 n 条移动指令）
t 未初始化（循环中读入） 当前指令的 移动距离 （正整数） flag 1 当前移动的「参考方向标记」 ：
 • flag=1 ：此时 向南（South）移动会让纵向位置 num 增加 （向南是「正方向」，指向轨道端点 N ）
 • flag=-1 ：此时 向北（North）移动会让纵向位置 num 增加 （向北是「正方向」，指向轨道起点 0 ，处于「反向移动」状态）
 num 0 当前的 纵向位置 （轨道上的位置，范围强制要求 0 ≤ num ≤ N ，起点在 0 ）
 ans 1 合法性标记 ： 1 =全程合法， 0 =不合法（一旦置 0 就无法变回 1 ）
 s 空字符串（循环中读入） 当前指令的 方向字符串 （合法取值： "South" 、 "North" 、其他如 "East" / "West" / "Stay" 等）

循环处理 n 条指令，每处理一条， n 减 1，直到 n=0 时退出循环
读入当前指令的 移动距离 t 和 方向字符串 s
- 当 flag == 1 （当前正方向是南）：向南走让位置增加 → num += t 。
- 当 flag == -1 （当前正方向是北，处于反向移动）：向南走让位置减少 → num -= t

- 当 flag == -1 （当前正方向是北）：向北走让位置增加 → num += t 。
- 当 flag == 1 （当前正方向是南）：向北走让位置减少 → num -= t
- 当指令 不是南北方向 （比如东西横向移动、原地不动等）， 不改变纵向位置 num 。
- 但有一个特殊约束： 如果此时 num == 0 （物体在起点位置），则直接判定为不合法（ ans=0 ）
当纵向位置**刚好到达轨道的右端点 N **时：
1. 反转参考方向 flag ： flag = -flag （比如从 1 变成 -1 ，表示接下来正方向从南变成北，要往回走了）。
2. 重置位置 num 为 0 ：把「到达 N 」等价为「从 0 开始反向移动」（类似碰撞反弹，把 0 和 N 视为同一个端点的不同表示，简化往返计算）
只有 没到达端点 N 时，才检查是否越界：
- 若 num > N ：物体跑到端点 N 外面，非法。
- 若 num < 0 ：物体跑到起点 0 外面，非法。
- 越界则把 ans 置为 0 （标记不合法，后续无法恢复）
最终要同时满足 三个独立条件 才输出 YES ：
1. ans == 1 ： 全程没有非法操作 （没越界、没触发特殊约束）。
2. flag == 1 ： 方向回到初始状态 （初始 flag=1 ，要求结束时 flag 也为 1 ，不能停在反向状态）。
3. num == 0 ： 纵向位置回到起点 0 （必须回到出发点，不能停在轨道中间）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e4;

int main() {
    fast;
    int n; cin >> n;
    int t, flag = 1, num = 0, ans = 1; string s;
    while (n--) {
        cin >> t >> s;
        if (s == "South") {
            if (flag == 1) num += t;
            else if (flag == -1) num -= t;
        } else if (s == "North") {
            if (flag == -1) num += t;
            else if (flag == 1) num -= t;
        } else {
            if (num == 0) ans = 0;
        }
        if (num == N) { flag = -flag; num = 0; }
        else if (num > N || num < 0) ans = 0;
    }
    if (ans && flag == 1 && num == 0) cout << "YES" << '\n';
    else cout << "NO" << '\n';
    return 0;
}