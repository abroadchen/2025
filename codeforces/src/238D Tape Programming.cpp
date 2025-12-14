//
// Created by Psy.C on 2025/12/13.
//
/*
*定义双向链表节点结构：
l: 左邻居索引
r: 右邻居索引
v: 节点值
del()函数删除节点x，维护链表连接关系
 *
*初始化双向链表：
数字字符('0'-'9')转换为0-9
'<'字符转换为11
'>'字符转换为10
*初始化ft和gt数组为大值
添加哨兵节点
 *
*ft[l]记录节点l第一次被访问的时间
f[cur][i]记录在时刻cnt时数字i的计数
只处理未访问过的节点
 *
*如果是数字节点(0-9)：数字减1，计数器加1，如果变为负数则删除节点
如果是方向符：设置移动方向(11表示左，10表示右)
移动到下一个节点
如果连续两个方向符则删除当前节点
维护栈记录访问历史
 *
*当向左移动时，更新栈中节点的离开时间gt
记录离开时的计数状态g
*对于区间[l,r]，计算各数字的出现次数
根据时间关系选择使用进入状态或离开状态计算
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define inf 1<<29
using namespace std;

struct node { int l, r, v; } a[N];
void del(const int x) { a[a[x].l].r = a[x].r; a[a[x].r].l = a[x].l; }

int main() {
    fast;
    int n, q, ft[N], gt[N], cnt = 1, f[N][10], c[10], sta[N], top = 0, g[N][10];
    string str; cin >> n >> q >> str;
    const int len = static_cast<int>(str.length());
    char s[N];
    for (int i = 0; i < len; ++i) s[i + 1] = str[i];//将字符串转换为从索引1开始的字符数组
    for (int i = 1, v; i <= n; ++i) {
        if (s[i] >= '0' && s[i] <= '9') v = s[i] - '0';
        else v = s[i] == '<' ? 11 : 10;
        a[i] = {i - 1, i + 1, v};
    }
    memset(ft, 63, sizeof(ft));
    memset(gt, 63, sizeof(gt));
    ++cnt; ++n;
    a[n] = {n - 1, n + 1, 10};
    bool flag[N];
    for (int l = 1; l <= n; ++l) if (ft[l] > inf) {
        for (int cur = l, nxt = 0, pos = 10; l <= cur && cur <= n; cur = nxt, ++cnt) {
            if (cnt < ft[cur]) {
                ft[cur] = cnt;
                for (int i = 0; i < 10; ++i) f[cur][i] = c[i];
            }
            if (a[cur].v < 10) {
                c[a[cur].v--]++;
                if (a[cur].v < 0) del(cur);
            } else pos = a[cur].v;
            nxt = pos == 11 ? a[cur].l : a[cur].r;
            if (a[cur].v > 9 && a[nxt].v > 9) del(cur);
            if (!flag[cur]) sta[++top] = cur, flag[cur] = true;
            if (pos == 11) {
                for (; a[cur].l < sta[top] && sta[top] <= cur && top; --top) {
                    gt[sta[top]] = ++cnt;
                    for (int i = 0; i < 10; ++i) g[sta[top]][i] = c[i];
                }
            }
        }
    }
    while (q--) {
        int l, r; cin >> l >> r;
        if (ft[r + 1] < gt[l]) {
            for (int i = 0; i < 10; ++i) cout << f[r+1][i] - f[l][i] <<
                (i == 9 ? '\n' : ' ');
        } else {
            for (int i = 0; i < 10; ++i) cout << g[l][i] - f[l][i] <<
                (i == 9 ? '\n' : ' ');
        }
    }
    return 0;
}