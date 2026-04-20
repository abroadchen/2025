//
// Created by Psy.C on 2026/4/19.
//
/**
id: 节点ID
num[N]: 存储矩阵元素值
r[N]: 右指针
d[N]: 下指针
这是一个十字链表结构，用于表示稀疏矩阵
将二维坐标(x,y)转换为一维ID
m: 矩阵列数
初始化矩阵的十字链表结构
i, j从0开始，创建虚拟边界行和列
if (i&&j) cin >> num[id];: 从(1,1)开始输入实际数据
d[id] = get(i+1, j);: 设置向下指针
r[id] = get(i, j+1);: 设置向右指针

n, m: 矩阵行列数
q: 操作数量
a, b, c, d2: 操作的矩形区域坐标
h, w: 操作的高度和宽度

输入矩阵大小和操作数
初始化十字链表结构
读取操作参数
x, y: 定位到第一个矩形的左上角
x = d[x], x = r[x]: 移动到指定位置

初始化: O(n*m)
每次操作: O(h + w)
输出: O(n*m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 15e5;
int m;
int get(int x, int y) { return x*m + y; }

int id, num[N], r[N], d[N];
void init(int x, int y) {
    for (int i = 0; i <= x; ++i)
        for (int j = 0; j <= y; ++j) {
            id = get(i, j);
            if (i&&j) cin >> num[id];
            d[id] = get(i+1, j);
            r[id] = get(i, j+1);
        }
}

int n, q, a, b, c, d2, h, w;
int main() {
    fast;
    cin >> n >> m >> q; init(n, m);
    while (q--) {
        cin >> a >> b >> c >> d2 >> h >> w;
        int x = 0, y = 0, tx, ty;
        for (int i = 1; i < a; ++i) x = d[x];
        for (int i = 1; i < b; ++i) x = r[x];
        for (int i = 1; i < c; ++i) y = d[y];
        for (int i = 1; i < d2; ++i) y = r[y];
        tx = x, ty = y;
        for (int i = 0; i < h; ++i) {
            tx = d[tx]; ty = d[ty];
            swap(r[tx], r[ty]);//交换两矩形的行指针
        }
        for (int i = 0; i < w; ++i) {
            tx = r[tx]; ty = r[ty];
            swap(d[tx], d[ty]);//交换两矩形的列指针
        }
        tx = x, ty = y;//恢复tx, ty
        //反向操作
        for (int i = 0; i < w; ++i) {
            tx = r[tx]; ty = r[ty];
            swap(d[tx], d[ty]);
        }
        for (int i = 0; i < h; ++i) {
            tx = d[tx]; ty = d[ty];
            swap(r[tx], r[ty]);
        }
    }
    int x = 0, y;
    for (int i = 1; i <= n; ++i) {
        x = d[x]; y = x;//从虚拟行开始，移动到实际数据位置
        for (int j = 1; j <= m; ++j) {
            y = r[y];
            cout << num[y] << ' ';//按行输出矩阵元素
        }
        cout << '\n';
    }
    return 0;
}