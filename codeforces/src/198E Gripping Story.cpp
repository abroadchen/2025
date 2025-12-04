//
// Created by Psy.C on 2025/12/4.
//
/*
*n: 夹爪的数量
da 结构体表示一个夹爪设备，包含：
x, y: 坐标位置
m: 质量
p: 力量(power)
r: 作用半径(radius)
dis: 到飞船的距离
a[N]: 存储所有夹爪数据的数组，a[0]代表飞船的初始夹爪
block 结构体表示数据块，包含左边界(l)和右边界(r)
b[N]: 存储分块信息的数组
 *
*cnt: 块的数量
len: 每块的长度
mx[N]: 每个块中的最大质量
idx[N]: 每个元素所属的块索引
函数功能：
根据n的平方根确定分块数量和每块大小
设置每个块的左右边界
最后一块的右边界设置为n
对每块内部按距离排序
计算每块的最大质量和记录元素所属块
 *
*vis[N]: 标记是否已经访问过某个夹爪
q: BFS队列
ans: 收集到的夹爪总数
attract函数：使用当前夹爪u来吸引其他夹爪
找到第一个质量超过当前夹爪力量的块
对于所有质量都不超过当前力量的块，利用已排序特性快速获取可吸引夹爪
对于第一个质量超标的块，逐一检查其中的夹爪
 *
 *时间复杂度约为O(n√n)
 *
 */
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000009
using namespace std;

int n;
struct da { int x, y, m, p; ll r, dis; } a[N];
struct block { int l, r; } b[N];

ll sq(const int k) { return static_cast<ll>(k) * k; }//整数的平方
ll dis(const da& m1, const da& m2) {//两个夹爪之间的欧几里得距离的平方
    const int x1 = m1.x, y1 = m1.y, x2 = m2.x, y2 = m2.y;
    return sq(x1 - x2) + sq(y1 - y2);
}

void bs(const int id) {//对指定块内的夹爪按距离排序
    const int l = b[id].l, r = b[id].r;
    sort(a + l, a + r + 1, [](const da& m1, const da& m2) {
        return m1.dis < m2.dis;
    });
}

int cnt, len, mx[N], idx[N];
void build() {
    cnt = len = static_cast<int>(sqrt(n));
    for (int i = 1; i <= cnt; ++i) {
        b[i].l = b[i - 1].r + 1;
        b[i].r = len * i;
    }
    b[cnt].r = n;
    for (int i = 1; i <= cnt; ++i) {
        bs(i);
        for (int j = b[i].l; j <= b[i].r; ++j) {//遍历块内所有元素
            mx[i] = max(mx[i], a[j].m);//该块的最大质量
            idx[j] = i;//每个元素所属的块号
        }
    }
}

bool vis[N];
queue<da> q; int ans;

void attract(const da& u) {
    int pos = n + 1;//第一个质量超过当前夹爪力量的块的位置
    for (int i = 1; i <= cnt; ++i) { if (mx[i] > u.p) { pos = i; break; } }
    for (int i = 1; i <= pos - 1; ++i) {//处理所有最大质量都不超过当前夹爪力量的块
        //块的左边界不超过右边界且该位置元素距离飞船不超过u的半径
        while (b[i].l <= b[i].r && dis(a[0], a[b[i].l]) <= u.r) {
            const int j = b[i].l;//获取当前检查元素的索引
            if (!vis[j]) {
                ans++;//收集计数加1
                q.push(a[j]);//将该夹爪加入队列（后续可以用来吸引其他夹爪）
                vis[j] = true;//标记为已访问
            }
            b[i].l++;//移动块的左边界指针 下次循环检查下一个元素
        }
    }
    if (pos == n + 1) return;//所有块的质量都满足要求
    //处理第一个质量可能超过当前夹爪力量的块
    for (int i = b[pos].l; i <= b[pos].r; ++i) {//遍历该块中的所有元素
        if (a[i].m <= u.p && dis(a[0], a[i]) <= u.r && !vis[i]) {
            ans++;
            vis[i] = true;
            q.push(a[i]);
        }
    }
}


int main() {
    fast;//飞船的初始位置(x,y)、初始夹爪的力量(p)和半径(r)，以及太空中的夹爪数量(n)
    cin >> a[0].x >> a[0].y >> a[0].p >> a[0].r >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].x >> a[i].y >> a[i].m >> a[i].p >> a[i].r;
    for (int i = 0; i <= n; ++i) {
        a[i].r = sq(static_cast<int>(a[i].r));//将半径转换为其平方值（避免后续多次开方运算）
        a[i].dis = dis(a[0], a[i]);//每个夹爪到飞船的距離平方
    }
    sort(a + 1, a + n + 1, [](const da& m1, const da& m2) {
        return m1.m < m2.m;//按质量从小到大排序
    });
    build(); vis[0] = true; q.push(a[0]);//飞船夹爪加入队列作为BFS起点
    while (!q.empty() && ans < n) {//还没有收集完所有夹爪时
        auto u = q.front(); q.pop();//从队列中取出一个夹爪u
        attract(u);//使用夹爪u去吸引其他可收集的夹爪
    }
    cout << ans;
    return 0;
}