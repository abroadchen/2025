//
// Created by Psy.C on 2026/9/22.
//
/**
t[N][2]：字典树节点指针，t[x][0] 指向节点 x 的 0 号儿子，t[x][1] 指向 1 号儿子；t[x][c] = 0 表示该子节点还不存在。
sum[N]：节点上的计数，代表"经过这个节点的数有多少个"（用于统计集合大小）。
tot：当前分配到的节点编号，tot(1) 表示把 1 号节点作为根（根节点编号从 1 开始）
x = 1：从根节点开始。
for (int i = 1<<30; i; i>>=1)：从第 30 位（最高位）向第 0 位逐位遍历 p 的二进制（覆盖到约 1e9 以内的数）。
bool tmp = p & i：取出 p 在这一位是 0 还是 1。
if (!t[x][tmp]) t[x][tmp] = ++tot;：若该分支节点不存在，就新建一个（编号 ++tot）。
x = t[x][tmp]：沿该分支下移到子节点。
sum[x] += k;：给这一位路径上的节点计数累加 k——insert(p, 1) 插入时计数 +1，insert(p, -1) 删除时计数 -1【1† 非直接，此处为逻辑】**。这样 sum[x] 记录了"经过节点 x 的数字个数"，删除即减回，实现可增可删的动态集合
当 tmp2 == 1（l 的这一位是 1）‍：
若令 x 的这一位 = tmp，则 x^p 这一位 = 0，此时从这一位起就已经小于 l，该分支下所有数都满足 x^p < l，于是整支计数 sum[t[x][tmp]] 直接计入 ans【逻辑核心】。
之后为了让异或结果与 l 保持"相等、继续往下比"，必须让 x^p 这一位 = 1，也就是 x 的这一位取 !tmp，所以 x = t[x][!tmp]。
当 tmp2 == 0（l 的这一位是 0）‍：
要保证仍可能 x^p < l，x^p 这一位必须为 0（若是 1 就已经大于 l 了），所以 x 的这一位必须等于 tmp，走 x = t[x][tmp]。
若某分支 t[x][...] 不存在则为 0，此时 x 变为 0，sum[0] = 0，后续步骤不再贡献，符合"该分支没有数可走"。
循环结束后返回 ans，即满足 x ^ p < l 的个数。
op == 1：读入 p，调用 insert(p, 1) 插入 p。
op == 2：读入 p，调用 insert(p, -1) 删除 p（计数 -1，若已删光则该路径计数归零，等价于不存在）。
op == 3：读入 p、l，查询并输出"集合中满足 x ^ p < l 的 x 的个数"

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e7+1;

int t[N][2], sum[N], tot(1);
void insert(int p, int k) {
    int x = 1;
    for (int i = 1<<30; i; i>>=1) {
        bool tmp = p&i;
        if (!t[x][tmp]) t[x][tmp] = ++tot;
        x = t[x][tmp];
        sum[x] += k;
    }
}
int query(int p, int l) {
    int x = 1, ans = 0;
    for (int i = 1<<30; i; i>>=1) {
        bool tmp = p&i, tmp2 = l&i;
        if (tmp2) ans += sum[t[x][tmp]], x = t[x][!tmp];
        else x = t[x][tmp];
    }
    return ans;
}

int main() {
    fast;
    int n; cin >> n;
    while (n--) {
        int op, p, l; cin >> op;
        if (op == 1) { cin >> p; insert(p, 1); }
        else if (op == 2) { cin >> p; insert(p, -1); }
        else { cin >> p >> l; cout << query(p, l) << '\n'; }
    }
    return 0;
}