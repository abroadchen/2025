//
// Created by Psy.C on 2025/10/26.
//
/*
*n: 变量数量
t[N]: 存储输入数据的数组
k: 目标值
dat: 记录目标值在哪个位置被找到
flag[N]: 标记数组
maxt: 记录最大值
q: 整数队列
 *定义结构体Node，包含三个整数a,b,c
 *声明Node类型数组te[N]用于存储三元组
 *
 *使用宏循环读取3*n个数字到数组t中，并同时推入队列q
 *读取n个三元组，存储到te数组中
 *
*遍历n次操作：
如果队列首元素等于k，记录当前位置并跳出循环
弹出队列首元素
标记当前三元组中的三个元素为已访问
持续弹出队列中已被标记的元素
 *
 *如果没有找到k（dat为0），输出除k外的所有数字
 *重置标记数组
 *重新标记前dat个三元组中的所有元素
 *在包含k的三元组中，找出不等于k的最大元素作为maxt
 *输出不超过maxt的所有被标记元素（除了k本身），并将其标记为2
 *输出剩余的所有未被输出的元素（除了k本身）
 *
 */
#include <queue>
#include <ios>
#include <iostream>
#include <cstring>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

const int N = 3e5+5;
int n, t[N], k, dat, flag[N], maxt;
queue<int> q;

struct Node {
    int a, b, c;
} te[N];

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;
    rep(i, 3*n) { cin >> t[i]; q.push(t[i]); }
    rep(i, n) { cin >> te[i].a >> te[i].b >> te[i].c; }
    cin >> k;
    rep(i, n) {
        if (q.front() == k) { dat = i; break; }
        q.pop();
        flag[te[i].a] = flag[te[i].b] = flag[te[i].c] = 1;
        while (q.size() && flag[q.front()]) q.pop();
    }
    if (dat == 0) {
        rep(i, 3*n) { if (i != k) cout << i << ' '; }
        return 0;
    }
    memset(flag, 0, sizeof(flag));
    rep(i,dat) { flag[te[i].a] = flag[te[i].b] = flag[te[i].c] = 1; }
    if (te[dat].a != k && te[dat].a > maxt) maxt = te[dat].a;
    if (te[dat].b != k && te[dat].b > maxt) maxt = te[dat].b;
    if (te[dat].c != k && te[dat].c > maxt) maxt = te[dat].c;
    rep(i,maxt) { if (flag[i] && i != k) { flag[i] = 2; cout << i << ' '; } }
    rep(i,3*n) { if (flag[i] != 2 && i != k) cout << i << ' '; }
    return 0;
}