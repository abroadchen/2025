//
// Created by Psy.C on 2025/9/21.
//

#include <iosfwd>
#include <iostream>
#include <vector>
using namespace std;

const int N = 101;
bool x[N][N][N], y[N][N][N];// 标记数组：x[a][b][d]表示垂直线段，y[b][a][c]表示水平线段
vector<int> ans;// 存储结果面积的向量


void dfs(int xmin, int xmax, int ymin, int ymax) {
    for (int i = xmin + 1; i <= xmax - 1; ++i) {// 在当前矩形区域内寻找垂直分割线
        if (x[i][ymin][ymax]) {// 检查是否存在从ymin到ymax的垂直线段
            dfs(xmin, i, ymin, ymax);// 左侧矩形
            dfs(i, xmax, ymin, ymax);// 右侧矩形
            return;// 找到分割线后立即返回
        }
    }
    for (int i = ymin + 1; i <= ymax - 1; ++i) {// 在当前矩形区域内寻找水平分割线
        if (y[i][xmin][xmax]) {// 检查是否存在从xmin到xmax的水平线段
            dfs(xmin, xmax, ymin, i);// 下方矩形
            dfs(xmin, xmax, i, ymax);// 上方矩形
            return;
        }
    }
    // 如果没有找到任何分割线，说明这是一个完整的不可分割区域
    ans.push_back((xmax - xmin) * (ymax - ymin));// 计算并存储面积
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int w, h, n; cin >> w >> h >> n;// 读取矩形宽度、高度和线段数量
    for (int i = 0; i < n; ++i) {
        int a, b, c, d; cin >> a >> b >> c >> d;// 读取线段的两个端点(a,b)和(c,d)
        if (a == c) x[a][b][d] = 1;// 垂直直线段，x坐标为a，y坐标从b到d
        else if (b == d) y[b][a][c] = 1;// 水平直线段，y坐标为b，x坐标从a到c
    }
    dfs(0, w, 0, h);
    sort(ans.begin(), ans.end());

    for (auto t : ans) cout << t << ' ';
    cout << endl;

    return 0;
}