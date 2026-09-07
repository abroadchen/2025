//
// Created by Psy.C on 2026/9/7.
//
/**
val[pos]：dfs 中计算得到的以 pos 为根的子树权值和。
tem[i]：节点 i 的原始点权（读入时的值）。
sum：整棵树点权和。
son[pre]：记录每个父节点下的子节点列表。
ans：栈，收集满足条件的切点（最多 2 个）

val[pos] = tem[pos]; —— 先把自己点权赋值给 val。
l = son[pos].size(); —— 子节点个数。
若有子节点
递归每个子树，并把子树的 val 累加到自己头上 → 后序遍历，val[pos] = 以 pos 为根的整棵子树权值和
val[pos]*3 == sum：这棵子树权值和恰好等于 sum/3（三块等分的一份）。
pos != son[0][0]：排除根节点本身（根不能作为"切"出来的独立块的一部分，且题目要求输出两个非根节点）。
ans.size() < 2：最多只取前两个。
命中则入栈 ans，并把 val[pos] = 0 清零——表示这块已经被"切走"，避免父节点再次把它算进大块，从而保证三块严格独立

读入 n 行，每行 pre[i] tem[i]：

pre[i] = 节点 i 的父节点（根节点的 pre 为 0）。
tem[i] = 点权。
sum += tem[i] 累加总权。
son[pre[i]].push_back(i)：把 i 挂到父节点下。
dfs(son[0][0]); —— son[0][0] 就是根节点（因为题目中根的父节点为 0，而根是唯一挂到 son[0] 下的第一个节点）。从根开始后序遍历整棵树
若 sum % 3 != 0：总权都不是 3 的倍数，直接 -1。
若成功收集到 2 个切点：倒序输出（栈顶先出，即后找到的先输出）。
否则输出 -1（找不够两块独立块
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6+5;

int val[N], tem[N], sum;
vector<int> son[N];
stack<int> ans;
void dfs(int pos) {
    val[pos] = tem[pos];
    int l = son[pos].size();
    if (l > 0) {
        for (int i = 0; i < l; ++i) {
            dfs(son[pos][i]);
            val[pos] += val[son[pos][i]];
        }
    }
    if (val[pos]*3 == sum && pos != son[0][0] && ans.size() < 2) {
        ans.push(pos);
        val[pos] = 0;
    }
}

int pre[N];
int main() {
    fast;
    int n; cin >> n; sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> pre[i] >> tem[i]; sum += tem[i];
        son[pre[i]].push_back(i);
    }
    dfs(son[0][0]);
    if (ans.size() == 2 && sum % 3 == 0) {
        cout << ans.top(); ans.pop();
        cout << ' ' << ans.top() << '\n'; ans.pop();
    } else cout << "-1\n";
    return 0;
}