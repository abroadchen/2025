//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
n：人数；
pos：目标选手的编号（我们关心的主角）；
s[i]：第 i 人的技能分（某分项）；
p[i]：第 i 人的潜能分（另一分项）
mx：目标选手的最高可能总分 = 自己的技能分 + 潜能最高分 p[1]。
ans：初始名次 = 目标选手的编号（因为 1 到 n 一般按排名/实力降序，前面有 pos-1 个人本来排在他前面）。ans 初始化为 pos，表示最差情况下假设排在 pos 名，后面能被"打败"的人会把它往前挪。
从 pos 前面一位、一直遍历到下标 1（即所有原本排在目标前面的选手 i）。
cur = 2：一个指针，指向当前可用来"配对"的潜能分（从 p[2] 开始，因为 p[1] 已留给目标选手本人）。
循环体逻辑：对于每个排在目标前面的选手 i，在剩余潜能分中找一个最小值，使 s[i] + p[cur] > mx，即"压过目标选手"，从而把选手 i 从"排在我前面"的队伍中消掉
双指针左扫：只要 s[i] + p[cur] 还大于 mx，就继续把 cur 往后移（即尝试用更小的潜能分）。
目的：找能让 s[i]+p[cur] > mx 成立的最小可用潜能下标，同时保证 cur 不越界。
找到后停下来的 cur 就是能"压过"选手 i 的潜能分
若 cur 已越界（潜能分全用完都凑不出能压过 i 的人），说明后面的人无法再消掉任何"排在前面的选手"，直接跳出，无需继续
ans--：成功"消掉"一个排在目标前面的人，目标名次前进一位（往前挪）。
cur++：这个潜能分已被使用，指针移向下一个
输出目标选手最终能排到的最好名次（数字越小越靠前）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); ++i)
using namespace std;

constexpr int N = 2e5+5;

int n, pos, s[N], p[N];
int main() {
    fast;
    cin >> n >> pos;
    rep(i,n) cin >> s[i];
    rep(i,n) cin >> p[i];
    int mx = s[pos] + p[1], ans = pos;
    for (int i = pos-1, cur = 2; i >= 1; i--) {
        while (s[i]+p[cur] > mx && cur <= n) cur++;
        if (cur > n) break;
        ans--, cur++;
    }
    cout << ans << '\n';
    return 0;
}