//
// Created by Psy.C on 2026/9/29.
//
/**
假设第一条直线是 斜率 k、经过点 (1, y[1]) 的直线（过第一个点）。
遍历 i=2..n：
若 y[i] - y[1] == k*(i-1)（即点 i 满足 y[i] = y[1] + k*(i-1)），说明点 i 在第一条直线上 → continue。
否则点 i 不在第一条直线上，它必须属于第二条直线。取第一个这样的点 p 作为第二条直线的基准点，flag=true。
之后若再遇到不在第一条直线上的点，检查它与 p 的斜率是否为 k（注意：这里比较的仍是 k，意味着两条直线的斜率必须相同 → 两条平行直线）。若斜率不等于 k → flag=false; break，说明构造失败。
若最后 !flag（即第二条直线没有点到，或中间失败）→ 返回 false；否则返回 true

第一、第二条直线上各有至少两个点，那么覆盖全局的"第一条直线"（斜率 k）必然由前三个点中的某两个确定——具体：

若点 1、2 在第一条直线上 → 斜率是 k1。
若点 1、3 在第一条直线上 → 斜率是 k2。
若点 2、3 在第一条直线上（点 1 在第二条线）→ 斜率是 k3。
因为前三个点中必有两个在同一条直线上（抽屉原理，3 个点分到 2 条线），所以枚举这三对即可覆盖所有"斜率 k 由前三点中某两点定出"的情况。对每个候选斜率调用 check，任一成功即输出 Yes

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
using namespace std;
constexpr int N = 1e3+5;

int n;
db y[N];
bool check(db k) {
    int p = 0; bool flag = false;
    for (int i = 2; i <= n; ++i) {
        if (y[i]-y[1] == k*(i-1)) continue;
        if (!flag) { flag = true; p = i; }
        else {
            if (y[i]-y[p] != k*(i-p)) {
                flag = false; break;
            }
        }
    }
    if (!flag) return false;
    return true;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> y[i];
    db k1 = y[2]-y[1], k2 = (y[3]-y[1])/2.0, k3 = y[3]-y[2];
    if (check(k1) || check(k2) || check(k3)) cout << "Yes";
    else cout << "No";
    return 0;
}