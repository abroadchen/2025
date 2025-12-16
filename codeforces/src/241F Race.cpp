//
// Created by Psy.C on 2025/12/14.
//
/*
*m: 地图的行数
n: 地图的列数
k: 初始能量值
*s[200][200]: 二维字符数组存储地图（最大200×200）
str: 临时字符串变量用于读取每一行
*循环m次读取每一行地图
将读取的字符串复制到s[i]+1的位置（从索引1开始存储）
这样做是为了让坐标从(1,1)开始，便于处理
*x[30]: 存储每个字母的行坐标
y[30]: 存储每个字母的列坐标
 *
*双重循环遍历整个地图
如果当前位置是小写字母（'a'到'z'）：
记录该字母在地图上的坐标位置
将字母位置改为'1'（表示可以通过，消耗1点能量）
将字符数字转换为整数数字（如'1'转为1）
 *
*s2[20000]: 字符数组存储需要访问的字母序列
rs, cs: 起始位置的行和列坐标
re, ce: 最终目标位置的行和列坐标
*rs, cs: 起始坐标
s2: 需要按顺序访问的字母字符串
re, ce: 最终目标坐标
 *t: 当前要访问的字母在序列中的索引
 *
*当还未访问完所有字母时继续循环
获取当前要访问字母的目标坐标(tx, ty)
 *
*水平移动到目标字母所在行：
当还没到达目标行且还有足够能量时继续移动
如果目标在下方，则向下移动；否则向上移动
每次移动消耗当前位置的能量值
*垂直移动到目标字母所在列：
当还没到达目标列且还有足够能量时继续移动
如果目标在右方，则向右移动；否则向左移动
每次移动消耗当前位置的能量值
*检查是否因能量不足而无法到达目标：
如果当前位置不等于目标位置且能量不足以继续移动
输出当前位置并结束程序
 *完成当前字母的访问，处理下一个字母
 *
 *访问完所有字母后，水平移动到最终目标
 *访问完所有字母后，垂直移动到最终目标
*如果因能量不足未能到达最终目标，输出当前位置
否则输出最终目标位置
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int m, n, k; cin >> m >> n >> k;
    char s[200][200]; string str;
    for (int i = 1; i <= m; ++i) cin >> str, strcpy(s[i] + 1, str.c_str());
    int x[30], y[30];
    for (int i = 1; i <= m; ++i) for (int j = 1; j <= n; ++j) {
        if (s[i][j] >= 'a' && s[i][j] <= 'z') {
            x[s[i][j] - 'a'] = i; y[s[i][j] - 'a'] = j;
            s[i][j] = '1';//将字母位置设为可通过
        }
        s[i][j] -= '0';// 转换为数字
    }
    char s2[20000];
    int rs, cs, re, ce;
    cin >> rs >> cs >> s2 >> re >> ce;
    int nx = rs, ny = cs, t = 0;
    const int len = static_cast<int>(strlen(s2));
    while (t < len) {
        const int tx = x[s2[t] - 'a'], ty = y[s2[t] - 'a'];
        while (nx != tx && k >= s[nx][ny]) {
            if (tx > nx) { k -= s[nx][ny]; nx++; }
            else { k -= s[nx][ny]; nx--; }
        }
        while (ny != ty && k >= s[nx][ny]) {
            if (ty > ny) { k -= s[nx][ny]; ny++; }
            else { k -= s[nx][ny]; ny--; }
        }
        if ((nx != tx || ny != ty) && k < s[nx][ny]) {
            cout << nx << ' ' << ny;
            return 0;
        }
        t++;
    }
    while (nx != re && k >= s[nx][ny]) {
        if (re > nx) { k -= s[nx][ny]; nx++; }
        else { k -= s[nx][ny]; nx--; }
    }
    while (ny != ce && k >= s[nx][ny]) {
        if (ce > ny) { k -= s[nx][ny]; ny++; }
        else { k -= s[nx][ny]; ny--; }
    }
    if ((nx != re || ny != ce) && k < s[nx][ny]) cout << nx << ' ' << ny;
    else cout << re << ' ' << ce;
    return 0;
}