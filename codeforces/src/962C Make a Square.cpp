//
// Created by Psy.C on 2026/10/21.
//
/**
把 n 的每一位十进制数字依次放入 b[1..cnt]（从低位到高位）
x：已选数字个数（实际未直接用于剪枝判断，仅递归深度计数）。
num：当前拼出的数。
lb：上一个选用的数字在 b 中的下标（保证严格递增下标，从而每个可选的"位"至多用一次、且保持原 n 的数字相对顺序）。
计算 num 的十进制位数 tot。

判平方数：q = sqrt(num)，若 num == q*q 则是完全平方数，此时用 res = min(cnt - tot, res) 更新答案——cnt - tot 表示"总共 cnt 个数字位里，用了 tot 位拼出平方数，剩下 cnt-tot 个数字被丢弃/不用"。

剪枝：if (lb >= cnt) return; 下标已越界则回溯。

枚举：for 从 lb+1 到 cnt，尝试把 b[i] 追加到 num 末尾（num*10+b[i]），递归。这保证了挑选的数字下标严格递增，即保持原数中各数字的相对顺序，且每个位最多用一次
读入 n，拆位。
res = inf 初始化。
reverse(b+1, b+1+cnt)：把数字反转，使 b[1..cnt] 变成从高位到低位（因为 get 原本存的是低位在前）。
dfs(1, 0, 0)：从空数开始搜索。
输出：若 res == cnt（没找到任何平方数，因为永远最小也就是"全不用 cnt 个"这种基准没被更新成更小），输出 -1；否则输出 res
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e4+5, inf = 0x3f3f3f3f;

int b[N], cnt;
void get(int x) { while (x) { b[++cnt] = x%10; x /= 10; } }

int res;
void dfs(int x, int num, int lb) {
    int t = num, tot = 0;
    while (t) t/=10, tot++;
    int q = sqrt(num);
    if (num == q*q) res=min(cnt-tot, res);
    if (lb >= cnt) return;
    for (int i = lb+1; i <= cnt; i++) dfs(x+1, num*10+b[i], i);
}


int main() {
    fast;
    int n; cin >> n; get(n); res = inf; reverse(b+1, b+1+cnt);
    dfs(1, 0, 0);
    if (res == cnt) cout << "-1\n"; else cout << res << '\n';
    return 0;
}