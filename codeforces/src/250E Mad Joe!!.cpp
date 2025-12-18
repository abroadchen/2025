//
// Created by Psy.C on 2025/12/17.
//
/*
 *n（行数）和m（列数)
*f1：标志位，表示是否到达底部行
f2：标志位，表示初始状态（开始时为true）
tim：时间计数器
dep：当前深度/行数
l：左边界位置
r：右边界位置
to：方向（0表示向右，1表示向左）
 *
 *主循环，持续执行直到到达底部行或确定无法继续
*检查是否在两个方向都被阻挡（非初始状态时）：
右边界已到或右边是墙
左边界已到或左边是墙
如果是这样，则跳出循环（无法继续前进）
 *标记不再处于初始状态
 *如果正在向右移动，增加从左到右边界遍历的时间
*尝试从最右侧位置向下移动：
如果下方格子为空（'.'），则向下移动
更新左边界为当前位置
增加深度，检查是否到达底部
跳出内层循环
*如果无法向右移动（到达边界或遇到障碍）：
改变方向为向左（to = 1）
如果右边有'+'号，则将其转换为'.'（清除障碍）
跳出内层循环
 *向右移动一步并增加时间
 *
 *如果正在向左移动，增加从右到左边界遍历的时间
*尝试从最左侧位置向下移动：
如果下方格子为空（'.'），则向下移动
更新右边界为当前位置
增加深度，检查是否到达底部
跳出内层循环
*如果无法向左移动（到达边界或遇到障碍）：
改变方向为向右（to = 0）
如果左边有'+'号，则将其转换为'.'（清除障碍）
跳出内层循环
 *向左移动一步并增加时间
 *
*如果到达底部行（f1=true），输出总时间
否则输出"Never"表示无法到达底部
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 110, M = 10010;

int main() {
    fast;
    int n, m; cin >> n >> m; char mp[N][M];
    for (int i = 0; i < n; ++i) cin >> mp[i];
    bool f1 = false, f2 = true; ll tim = 0;
    int dep = 0, l = 0, r = 0, to = 0;
    while (!f1) {
        if (!f2 && (r + 1 == m || mp[dep][r+1] == '#') &&
            (l == 0 || mp[dep][l-1] == '#')) break;
        f2 = false;
        if (to == 0) {
            tim += r - l;
            while (true) {
                if (mp[dep+1][r] == '.') {
                    tim++; l = r; f2 = true;
                    if (++dep == n - 1) f1 = true;
                    break;
                }
                if (r == m - 1 || mp[dep][r+1] != '.') {
                    tim++; to = 1;
                    if (r + 1 < m && mp[dep][r+1] == '+')
                        mp[dep][r+1] = '.';
                    break;
                }
                r++, tim++;
            }
        } else {
            tim += r - l;
            while (true) {
                if (mp[dep+1][l] == '.') {
                    tim++; r = l; f2 = true;
                    if (++dep == n - 1) f1 = true;
                    break;
                }
                if (l == 0 || mp[dep][l-1] != '.') {
                    tim++; to = 0;
                    if (l - 1 >= 0 && mp[dep][l-1] == '+')
                        mp[dep][l-1] = '.';
                    break;
                }
                l--, tim++;
            }
        }
    }
    if (f1) cout << tim << '\n'; else cout << "Never\n";
    return 0;
}