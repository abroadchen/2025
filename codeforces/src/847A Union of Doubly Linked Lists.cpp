//
// Created by Psy.C on 2026/9/28.
//
/**
n：节点个数（节点编号 1..n）。
nxt[i]：节点 i 的后继（下一个节点）。若 nxt[i]==0 表示 i 目前没有后继（段尾）。
lst[i]：节点 i 的前驱（上一个节点）。若 lst[i]==0 表示 i 目前没有前驱（段头）。
读入 n 行，每行两个数，填入数组
t 是一个"待接上的当前段头"指针。初始为 0（空）
只有当节点 i 当前没有后继（nxt[i]==0，即 i 是某条残缺段的段尾）时才处理。
反过来，nxt[i] != 0 的节点已经"接着"别人，不需要改动
把节点 i 的后继设为 t（上一个处理出来的段头）。
含义：把上一条段的头 t 接到当前节点 i 的后面，即 i → t
把 t 的前驱设为 i（因为 t 现在跟在 i 后面）。
即接上 t 这个头的前驱是 i
暂时把 t 更新为 i。此时 i 是"刚处理完这轮的节点"
这是为了把 t 沿着前驱链往回走到该段的起点（段头）‍。
因为接上后，t=i 可能不是这一段真正的头，通过反复 t = lst[t] 沿前驱跳到前驱为 0 的那个节点——即这段链的头。
这样循环结束后 t 就指向当前已形成这条链的真正开头，作为下次 nxt[i+1] = t 时被接上的段头
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

vector<int> nxt, lst;
int main() {
    fast;
    int n, i; cin >> n;
    nxt = vector<int>(n+1); lst = vector<int>(n+1);
    for (i = 1; i <= n; ++i) cin >> nxt[i] >> lst[i];
    int t = 0;
    for (i = 1; i <= n; ++i) {
        if (nxt[i] == 0) {
            nxt[i] = t; lst[t] = i; t = i;
            while (lst[t] != 0) t = lst[t];
        }
    }
    for (i = 1; i <= n; ++i)
        cout << nxt[i] << ' ' << lst[i] << '\n';
    return 0;
}