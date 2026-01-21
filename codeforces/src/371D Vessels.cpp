//
// Created by Psy.C on 2026/1/21.
//
/*
* 单次查询: O(α(n))，α为阿克曼函数的反函数
单次更新: O(α(n) × 填充的区间数)
总体: 接近线性时间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200050
using namespace std;

int fa[N];
int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {//将相邻位置连接，表示该位置已完成处理
    x = find(x); y = find(y);
    fa[x] = y;
}

int main() {
    fast;
    int n, v[N]; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> v[i];
    for (int i = 1; i <= n + 1; ++i) fa[i] = i;//n+1作为边界哨兵
    int a[N]={}, q;
    cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {//区间更新操作
            int k, c; cin >> k >> c;
            while (c) {
                k = find(k);//找到当前有效的处理位置 从k开始第一个未满的位置
                if (k > n) break;
                if (a[k] + c >= v[k]) {//当前位置无法完全容纳剩余容量
                    c -= v[k] - a[k];//减少剩余容量
                    a[k] = v[k];//当前位置填满
                    merge(k, k + 1);//合并当前位置与下一位置
                } else {//当前位置可以完全容纳剩余容量
                    a[k] += c;//增加当前值
                    c = 0;//容量用完
                }
            }
        } else {//查询操作
            int k; cin >> k;
            cout << a[k] << '\n';
        }
    }
    return 0;
}