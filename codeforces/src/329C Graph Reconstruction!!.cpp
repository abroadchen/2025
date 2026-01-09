//
// Created by Psy.C on 2026/1/9.
//
/**
* 1. 使用默认随机引擎
cpp
default_random_engine gen(time(nullptr));
shuffle(p, p + v, gen);
2. 使用静态生成器（避免重复创建）
cpp
static random_device rd;
static mt19937 gen(rd());
shuffle(p, p + v, gen);
3. 简单的随机数生成器
cpp
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 gen(seed);
shuffle(p, p + v, gen);
 *
*int e;：边数
ii g[N];：存储边的数组，每条边用一对整数表示
 *
*ok函数：检查边(u,v)是否存在于图中
minmax(u, v)：返回{min(u,v), max(u,v)}，标准化边的表示
binary_search<ii*,ii>(g, g + e, minmax(u, v))：在有序数组g中二分查找边
返回边是否存在
 *
 *v为顶点数，p为顶点数组，cnt为计数器
 *iota(p, p + v, 1);：将p数组初始化为{1, 2, 3, ..., v}
 *flag[N];：标志数组，记录相邻顶点对是否不存在于原图中
 *
 *随机打乱顶点排列，p[v] = p[0]
*循环检查相邻顶点对
!ok(p[i], p[i+1])：如果边不存在于原图中，flag[i]为true
cnt += flag[i]：统计不存在的边数
 *
 *如果不存在的边数大于等于原图的边数
*循环输出不存在的边
e -= flag[i] && ...：如果flag[i]为true，输出边并减少e
 *如果没有找到解，输出-1
 *
 *
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100054
#define ii pair<int, int>
using namespace std;

int e;
ii g[N];
//ii*：表示迭代器类型（指向 pair<int,int> 的指针）
//ii：表示要查找的值的类型（pair<int,int>）
bool ok(const int u, const int v) {//g 是一个 ii* 类型的指针（指向 pair<int,int> 数组）
    return binary_search<ii*,ii>(g, g + e, minmax(u, v));
}

int main() {
    fast;
    static random_device rd;
    static mt19937 gen(rd());
    int v, p[N], cnt; cin >> v >> e;
    for (int i = 0, x, y; i < e; ++i) {
        cin >> x >> y; g[i] = minmax(x, y);
    }
    sort(g, g + e); iota(p, p + v, 1);
    bool flag[N];
    for (int q = (v < 6 ? 1254 : INT_MAX); q; --q) {
        shuffle(p, p + v, gen), p[v] = *p;
        for (int i = cnt = 0; i < v; ++i) cnt += flag[i] = !ok(p[i], p[i+1]);
        if (cnt >= e) {
            for (int i = 0; i < v && e; ++i) e -= flag[i] && cout << p[i] << ' ' << p[i+1] << '\n';
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}