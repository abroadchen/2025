//
// Created by Psy.C on 2026/4/21.
//
/**
前序遍历：访问节点时将其压栈并翻转符号
后序遍历：从子节点返回时再次访问父节点
特殊处理：当某个节点仍为-1时，通过特定序列将其变为1
建图：O(n)
DFS遍历：O(n)
总体：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+7;
struct edge { int to, nxt; } e[N<<1];

int head[N], cnt;
void add(int u, int v) {
    e[++cnt] = {v, head[u]}, head[u] = cnt;
}

int st[N<<1], top, a[N];
void dfs(int x, int fa) {
    st[++top] = x; a[x] *= -1;//将当前节点压入栈，同时翻转a[x]的符号
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, x);
        st[++top] = x; a[x] *= -1;//返回时再次访问当前节点，翻转符号
    }
    if (a[x] == -1) {//当前节点的值仍为-1
        if (x != 1) {//不是根节点
            st[++top] = fa; a[fa] *= -1;//访问父节点，翻转父节点符号
            st[++top] = x; a[x] = 1;//再次访问当前节点，设置为1
        } else {//根节点
            st[++top] = e[head[1]].to;//访问根的第一个子节点
            st[++top] = 1;//访问根节点
            st[++top] = e[head[1]].to;//再次访问根的第一个子节点
        }
    }
}

int n;
int main() {
    fast;
    cin >> n;
    bool flag = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] == -1) flag = 1;//是否存在-1
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    if (!flag) cout << '1';//没有-1，直接输出'1'
    else {
        a[1] *= -1;//根节点符号翻转
        dfs(1, 0);
        for (int i = 1; i <= top; ++i)
            cout << st[i] << ' ';//输出访问序列
    }
    return 0;
}