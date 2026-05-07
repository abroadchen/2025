//
// Created by Psy.C on 2026/4/29.
//
/**
pre(x)：计算位置x的前一个位置（环形结构）
nxt(x)：计算位置x的下一个位置（环形结构）
检查位置p及其周围的5个位置（p, pre(p), pre(pre(p)), nxt(p), nxt(nxt(p)))是否满足条件
如果满足条件且之前未被访问，则加入队列
更新对应位置的vis标记
pi[i][2]：存储第i对数对的两个值
to[x]：存储x配对的对象（x与to[x]是一对）

循环读入n/2对数字
记录每对数字到pi数组
建立配对关系到to数组
初始化数组a，使相邻位置值不同（奇数位为1，偶数位为0）
遍历所有位置，确保每对中的两个元素不相等
如果一对元素相等，则翻转其中一个
检查每个位置是否满足三连相同条件
将满足条件的位置加入队列
当队列非空时循环
如果当前位置不再满足条件则跳过
随机选择一个位置进行翻转
翻转该位置及其配对位置的值
检查受影响的位置
输出结果，将0变成2，1变成1（通过2-a的方式转换）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+7;

int n;
int pre(int x) { return (x-2+n)%n+1; }
int nxt(int x) { return x%n+1; }

int a[N];///存储每个位置的状态（0或1）
///检查三个连续位置是否都相等：检查位置i、下一个位置、下下个位置的值是否相同
bool check(int i) {
    return a[i] == a[nxt(i)] && a[nxt(i)] == a[nxt(nxt(i))];
}
bool vis[N];///标记某个位置是否满足条件
queue<int> q;///存储满足条件的位置
void chk(int p) {
    if (check(p)) {
        if (!vis[p]) q.push(p);
        vis[p] = true;
    } else vis[p] = false;
    if (check(pre(p))) {
        if (!vis[pre(p)]) q.push(pre(p));
        vis[pre(p)] = true;
    } else vis[pre(p)] = false;
    if (check(pre(pre(p)))) {
        if (!vis[pre(pre(p))]) q.push(pre(pre(p)));
        vis[pre(pre(p))] = true;
    } else vis[pre(pre(p))] = false;
    if (check(nxt(p))) {
        if (!vis[nxt(p)]) q.push(nxt(p));
        vis[nxt(p)] = true;
    } else vis[nxt(p)] = false;
    if (check(nxt(nxt(p)))) {
        if (!vis[nxt(nxt(p))]) q.push(nxt(nxt(p)));
        vis[nxt(nxt(p))] = true;
    } else vis[nxt(nxt(p))] = false;
}

int pi[N][2], to[N];
int main() {
    fast;
    cin >> n; n <<= 1;
    for (int i = 1, x, y; i <= n/2; ++i) {
        cin >> x >> y;
        pi[i][0] = x, pi[i][1] = y;
        to[x] = y; to[y] = x;
    }
    for (int i = 1; i <= n; ++i) a[i] = i&1;
    for (int i = 1; i <= n; ++i)
        if (a[i] == a[to[i]]) a[to[i]] = !a[to[i]];
    for (int i = 1; i <= n; ++i) {
        vis[i] = check(i);
        if (vis[i]) q.push(i);
    }
    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (!check(x)) continue;
        int pos = rand()%2+1;
        if (pos == 1) pos = x;
        else if (pos == 2) pos = nxt(x);
        else if (pos == 3) pos = nxt(nxt(x));
        a[pos] = !a[pos]; a[to[pos]] = !a[to[pos]];
        chk(pos); chk(to[pos]);
    }
    for (int i = 1; i <= n/2; ++i)
        cout << 2-a[pi[i][0]] << ' ' << 2-a[pi[i][1]] << '\n';
    return 0;
}