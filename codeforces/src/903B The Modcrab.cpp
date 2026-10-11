//
// Created by Psy.C on 2026/10/11.
//
/**
我方（勇者）：生命 h1，攻击 a1，还有一次行动可以花费 c 回血（HEAL）或攻击（STRIKE）。
敌方（怪物）：生命 h2，攻击 a2。
关键规则：每个回合我方可选择攻击或回血；怪物每回合结束后攻击我一次，造成 a2 伤害（除非怪物已被击败，则战斗结束）。
目标是活下来并击败怪物，求最少回合数，并输出每回合动作（HEAL=回血，STRIKE=攻击）
num = 击杀怪物所需的攻击次数（向上取整）：用我方攻击 a1 打掉怪物 h2 血需要的 STRIKE 次数
sum = 在纯输出（不回血）‍期间，怪物能打掉我方的总伤害。
推理：如果我连续 num 次 STRIKE 击杀怪物，那么在前 num-1 个回合怪物会各攻击我一次（最后一次 STRIKE 已先手杀死怪物，怪物不再反击），所以怪物总伤害 = a2 * (num-1)
h = 需要多回血几次的计数。
考虑：我方初始生命 h1，每次回血需花费 c 点"行动价值"。
条件 h*c + h1 <= sum 表示：当前可用生命（h1 加上 h 次回血能多抗的健康）还不足以扛住怪物总伤害 sum，那就：
多算一次怪物的攻击伤害 sum += a2（因为每多回血一个回合，战斗会延长一回合，怪物就多一次出手，多造成 a2 伤害）；
h++（多回一次血）。
结束条件：直到 h*c + h1 > sum，即回血 h 次后总可用血量能扛住（含延长回合的）全部怪物伤害
总回合数 = h + num（回血次数 + 攻击次数）。
先输出 h 个 HEAL，再输出 num 个 STRIKE，作为每回合动作。
策略是先把血回够、再连续攻击：因为回血和攻击谁先谁后在这个模型下（只要最后能扛住）不影响最终击杀所需回合，代码选择"先回后打"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
int h1, a1, c, h2, a2;
int main() {
    fast;
    while (cin >> h1 >> a1 >> c >> h2 >> a2) {
        int num = h2/a1;
        if (h2%a1 != 0) num++;
        int sum = a2*(num-1), h = 0;
        while (h*c+h1 <= sum) {
            sum += a2;
            h++;
        }
        cout << h+num << '\n';
        while (h--) cout << "HEAL\n";
        while (num--) cout << "STRIKE\n";
    }
    return 0;
}