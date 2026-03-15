//
// Created by Psy.C on 2026/3/15.
//
/**
同时设置双向链接 nxt[u]=v, pre[v]=u

c=s[i]=='L'：如果s[i]=='L'则c=1，否则c=0
如果当前字符是'L'，则尝试与队列q[1]中的'R'配对
如果当前字符是'R'，则尝试与队列q[0]中的'L'配对
配对成功后建立双向链接

遍历所有节点，找到未被连接的头节点
找到每个独立链表的首尾节点
将链表段压入栈中
循环执行合并操作直到不能再合并


将a段的右端连接到b段的右端
将b段的右端连接到b段的左端（形成一个回路）
断开x节点的后续连接（如果x存在的话）
这样分离了原本连接到b.r的部分
--tp：栈顶指针减一（弹出两个元素，压入一个）
新段的左端点是a.l（a段的左端点）
新段的右端点是x（原来连接到b.r的节点）

时间复杂度
O(n)：每个节点最多参与常数次操作
空间复杂度
O(n)：存储链表和栈空间

i是头节点（通过!pre[i]判断）
p是尾节点（通过!nxt[p]判断）
只需修改一个指针即可断开链表
如果只有单向连接，断开操作会更复杂
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ex(u,v) nxt[u]=v, pre[v]=u
using namespace std;
constexpr int N = 1e5+5;

struct node { int l, r; } st[N];///链表段的左端点和右端点

int tp, pre[N], nxt[N];///链表指针数组
char s[N];///输入字符串
bool ok() {
    if (tp <= 1) return false;//至少需要两个段才能操作
    auto a = st[tp], b = st[tp-1];//取栈顶两个段
    //a的右端与b的左端字符不同 -> 直接连接
    if (s[a.r] != s[b.l]) {
        ex(a.r, b.l), st[--tp] = {a.l, b.r};
        return true;
    }
    //a的左端与b的右端字符不同 -> 反向连接
    if (s[a.l] != s[b.r]) {
        ex(b.r, a.l), st[--tp] = {b.l, a.r};
        return true;
    }
    //a的左端与b的左端字符不同 -> 复杂重组
    if (s[a.l] != s[b.l]) {
        if (a.r > b.r) swap(a, b);//a.r ≤ b.r，即a段在b段的左侧或重叠
        int x = pre[b.r];//x是b段右端点的前驱节点
        ex(a.r, b.r), ex(b.r, b.l), nxt[x] = 0, st[--tp] = {a.l, x};
        return true;
    }
    return false;
}

queue<int> q[2];///q[0]存储'L'字符位置，q[1]存储'R'字符位置
int main() {
    fast;
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1, c; i <= n; q[c^1].push(i++))
        if (!q[c=s[i]=='L'].empty())
            ex(q[c].front(), i), q[c].pop();
    int ans = 0;
    for (int i = 1; i <= n; ++i) if (!pre[i]) {//找到链表头节点
        ++ans;
        int p = i;
        while (nxt[p]) p = nxt[p];//找到链表尾节点
        st[++tp] = {i, p};//记录链表段
        while (ok());//不断尝试合并
    }
    cout << ans - 1 << '\n';
    for (int x = st[1].l; x; x = nxt[x]) cout << x << ' ';//输出最终链表
    return 0;
}