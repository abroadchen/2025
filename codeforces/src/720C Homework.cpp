//
// Created by Psy.C on 2026/4/22.
//
/**
x, y: 当前处理的网格位置
k: 目标计数
flag: 解存在标志
a[16][16]: 用于暴力搜索的小网格（最大16×16）
遍历所有2×2子矩形
cnt: 子矩形中1的个数
cnt == 3: 计数加1
cnt == 4: 计数加4
找到解时输出网格
(k==0&&i==1&&j==1): 特殊处理k=0的情况
尝试当前位置填0或1
如果找到解就提前返回

小网格特例处理 小网格直接暴力搜索
大部分特例处理
中等k值处理

网格规范化 确保n ≤ m，简化后续处理
特殊情况处理
网格初始化
清空并重置数组
第一行全为1，其余为0
m-j+1 <= 5: 末尾小区域用特例处理
k < 4: 用f2函数处理小k值
每个位置设置为1会消耗一定的k值：
角落(1,1): 消耗1
边界: 消耗3
内部: 消耗4
时间复杂度根据网格大小变化，小网格O(2^(nm))，大网格O(nm)

x, y: 当前处理的网格位置坐标
if (y > m): 如果列超出边界
dfs(x + 1, 1): 移到下一行第一列
return: 结束当前函数调用
if (x > n): 如果行超出边界，说明整个网格已处理完毕
int num = 0: 初始化计数器
for (int i = 1; i < n; i++): 遍历所有可能的2×2子矩形的左上角行
for (int j = 1; j < m; j++): 遍历所有可能的2×2子矩形的左上角列
int cnt = a[i][j] + a[i+1][j] + a[i][j+1] + a[i+1][j+1]: 计算2×2子矩形中1的个数
if (cnt == 3) num++: 如果有3个1，计数器加1
if (cnt == 4) num += 4: 如果有4个1，计数器加4
if (num == k): 如果计算出的计数等于目标k
putchar(a[i][j]||(k==0&&i==1&&j==1)?'*':'.'): 输出字符
a[i][j]||(k==0&&i==1&&j==1): 如果a[i][j]为1或特殊情况(k=0且在左上角)，输出'*'，否则输出'.'
flag = 1: 设置找到解的标志
return: 返回上一层调用
a[x][y] = 0: 尝试当前位置填0
dfs(x, y+1): 递归处理下一个位置
if (flag) return: 如果已找到解，直接返回
a[x][y] = 1: 尝试当前位置填1
dfs(x, y+1): 递归处理下一个位置
a[x][y] = 0: 恢复状态（虽然这里不必要，但体现回溯思想）

dfs(1, 1): 从位置(1,1)开始搜索
if (!flag) printf("-1\n"): 如果没找到解，输出-1
putchar('\n'): 输出空行


s[N]: 每行用vector存储，动态数组
int x = m - 5: 计算偏移量
if (m == 5): 处理列数为5的特殊情况
后面是一系列根据k值设置网格的代码
flag = 1: 设置找到解标志
y--: 调整y坐标
根据k值和位置在网格中设置特定点

int T = rd(): 读取测试用例数量
tim = 0: 时间戳计数器
while (T--): 处理T个测试用例
flag = 0: 重置标志
n = rd(), m = rd(), k = rd(): 读取网格大小和目标值
++tim: 增加时间戳
if (n < 5 && m < 5): 如果网格很小
bf(): 使用暴力搜索
continue: 跳到下一个测试用例
bool jd = 0: 旋转标志
if (n > m): 如果行数大于列数
swap(n, m): 交换行列数，确保n ≤ m
jd = 1: 设置旋转标志
k == 8*(m-1)-8: 特殊的k值情况
j==m?'.':'*': 最后一列输出'.'，其他输出'*'
if (!jd): 如果不需要旋转，按原顺序输出
else: 如果需要旋转，行列互换输出

s[i].clear(): 清空第i行
s[i].shrink_to_fit(): 释放多余内存
s[i].resize(m+10): 重新调整大小
s[i][j] = i==1: 第一行全为1，其他行为0
for (int i = 2; i <= n; i++): 从第2行开始构造
int o = 0: 操作标志
if (i == n && m-j+1 <= 5): 最后一行的后5个位置用特例处理
if (k < 4): k值很小时用f2处理
s[i][j] = 1: 将当前位置设为1
if (j == 1) k -= 1: 左边界，k减少1
else if (j == m) k -= 3: 右边界，k减少3
else k -= 4: 内部位置，k减少4
if (o) break: 如果操作标志为1，跳出循环

if (!flag): 如果没找到解
if (!jd): 如果不需要旋转，按原顺序输出
s[i][j]?'*':'.': 如果s[i][j]为真输出'*'，否则输出'.'
else: 如果需要旋转，行列互换输出
putchar('\n'): 输出空行分隔
 */
#include <bits/stdc++.h>
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
constexpr int N = 2e5+7, mod = 1e9+7;

int n, m, a[16][16], k, flag;
void dfs(int x, int y) {
    if (y > m) { dfs(x + 1, 1); return; }
    if (x > n) {
        int num = 0;
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++) {
                int cnt = a[i][j] + a[i+1][j] + a[i][j+1] + a[i+1][j+1];
                if (cnt == 3) num++;
                if (cnt == 4) num += 4;
            }
        if (num == k) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++)
                    putchar(a[i][j]||(k==0&&i==1&&j==1)?'*':'.');
                putchar('\n');
            }
            flag = 1;
        }
        return;
    }
    a[x][y] = 0; dfs(x, y+1); if (flag) return;
    a[x][y] = 1; dfs(x, y+1);
    a[x][y] = 0;
}
void bf() {
    dfs(1, 1);
    if (!flag) printf("-1\n");
    putchar('\n');
}

vector<int> s[N];
void f1() {
    int x = m - 5;
    if (m == 5) {
        if (k == 0) { flag = 1; return; }
        if (k == 1) { s[n][1] = 1; flag = 1; return; }
        if (k == 2) { s[n][1] = s[n][5] = 1; flag = 1; return; }
        if (k == 3) { s[n][1] = s[n][3] = 1; flag = 1; return; }
        if (k == 4) { s[n][2] = s[n][4] = 1; flag = 1; return; }
        if (k == 5) { s[n][1] = s[n][2] = 1; flag = 1; return; }
        if (k == 6) { s[n][1] = s[n][2] = s[n][5] = 1; flag = 1; return; }
        if (k == 7) { s[n][1] = s[n][2] = s[n][4] = 1; flag = 1; return; }
        if (k == 8) { flag = 0; return; }
        if (k == 9) { s[n][1] = s[n][2] = s[n][3] = 1; flag = 1; return; }
        if (k == 10) { s[n][1] = s[n][2] = s[n][4] = s[n][5] = 1; flag = 1; return; }
        if (k == 11) { flag = 0; return; }
        if (k == 12) { flag = 0; return; }
        if (k == 13) { s[n][1] = s[n][2] = s[n][3] = s[n][4] = 1; flag = 1; return; }
        if (k == 14) { flag = 0; return; }
        if (k == 15) { flag = 0; return; }
        if (k == 16) { s[n][1] = s[n][3] = s[n][4] = s[n][5] = s[n][2] = 1; flag = 1; return; }
        flag = 0; return;
    }
    if (k == 0) { flag = 1; return; }
    if (k == 1) { s[n][m] = 1; flag = 1; return; }
    if (k == 2) { s[n][x+2] = 1; flag = 1; return; }
    if (k == 3) { s[n][x+2] = s[n][m] = 1; flag = 1; return; }
    if (k == 4) { s[n][x+2] = s[n][x+4] = 1; flag = 1; return; }
    if (k == 5) { s[n][x+1] = s[n][m] = 1; flag = 1; return; }
    if (k == 6) { s[n][x+1] = s[n][x+4] = 1; flag = 1; return; }
    if (k == 7) { s[n][x+2] = s[n][x+4] = s[n][x+5] = 1; flag = 1; return; }
    if (k == 8) { s[n][x+1] = s[n][x+2] = 1; flag = 1; return; }
    if (k == 9) { s[n][x+1] = s[n][x+2] = s[n][m] = 1; flag = 1; return; }
    if (k == 10) { s[n][x+1] = s[n][x+2] = s[n][x+4] = 1; flag = 1; return; }
    if (k == 11) { flag = 0; return; }
    if (k == 12) { s[n][x+1] = s[n][x+2] = s[n][x+3] = 1; flag = 1; return; }
    if (k == 13) { s[n][x+1] = s[n][x+2] = s[n][x+4] = s[n][x+5] = 1; flag = 1; return; }
    if (k == 14) { flag = 0; return; }
    if (k == 15) { flag = 0; return; }
    if (k == 16) { s[n][x+1] = s[n][x+2] = s[n][x+3] = s[n][x+4] = 1; flag = 1; return; }
    if (k == 19) { s[n][x+1] = s[n][x+2] = s[n][x+3] = s[n][x+4] = s[n][x+5] = 1; flag = 1; return; }
    flag = 0;
}

void f2(int x, int y) {
    flag = 1;
    if (k == 0) return; y--;
    if (k == 1) {
        if (y <= m-2) s[x][m] = 1; else s[x+1][1] = 1;
        return;
    }
    if (k == 2) {
        if (y <= m-3) s[x][m-1] = 1; else s[x+1][2] = 1;
        return;
    }
    if (k == 3) {
        if (y <= m-4) { s[x][y+2] = 1; s[x][m] = 1; }
        else if (y >= m-1) { s[x+1][1] = s[x+1][3] = 1; }
        else if (y <= 1) { s[x][3] = s[x][m] = 1; }
        else if (y == m-2) { s[x+1][2] = 1; s[x][m] = 1; }
        else { s[x+1][1] = 1; s[x][m-1] = 1; }
    }
}


int main() {
    int T = rd(), tim = 0;
    while (T--) {
        flag = 0;
        n = rd(), m = rd(), k = rd(); ++tim;
        if (n < 5 && m < 5) { bf(); continue; }
        bool jd = 0;
        if (n > m) swap(n, m), jd = 1;
        if (n == 3 && k == 8*(m-1)-8) {
            if (!jd) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= m; j++) putchar(j==m?'.':'*');
                    putchar('\n');
                }
            } else {
                for (int j = 1; j <= m; j++) {
                    for (int i = 1; i <= n; i++) putchar(j==1?'.':'*');
                    putchar('\n');
                }
            }
            putchar('\n');
            continue;
        }
        for (int i = 1; i <= n; i++) {
            s[i].clear(); s[i].shrink_to_fit(); s[i].resize(m+10);
            for (int j = 1; j <= m; j++) s[i][j] = i==1;
        }
        for (int i = 2; i <= n; i++) {
            int o = 0;
            for (int j = 1; j <= m; j++) {
                if (i == n && m-j+1 <= 5) { o = 1; f1(); break; }
                if (k < 4) { o = 1; f2(i, j); break; }
                s[i][j] = 1;
                if (j == 1) k -= 1;
                else if (j == m) k -= 3;
                else k -= 4;
            }
            if (o) break;
        }
        if (!flag) {
            printf("-1\n"); putchar('\n');
            continue;
        }
        if (!jd) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) putchar(s[i][j]?'*':'.');
                putchar('\n');
            }
        } else {
            for (int j = 1; j <= m; j++) {
                for (int i = 1; i <= n; i++) putchar(s[i][j]?'*':'.');
                putchar('\n');
            }
        }
        putchar('\n');
    }
    return 0;
}