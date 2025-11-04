//
// Created by Psy.C on 2025/11/4.
//
/*
 *n(车厢总数)、m(控制员初始位置)、k(偷渡者初始位置)
 *读取两个字符串到d，但只保留第二个(通过两次读取覆盖第一次)
 *读取操作序列字符串s
*确定偷渡者的移动方向：
如果d等于"head"，方向为-1(向车头移动)
否则方向为1(向车尾移动)
 *
 *遍历操作序列中的每一步操作
 *如果当前操作是'1'(偷渡者移动)：
 *偷渡者按照当前方向移动一步
 *如果偷渡者到达车头(1号车厢)或车尾(n号车厢)，则调转方向
*根据偷渡者的新位置确定控制员的位置：
如果在车头，控制员移到车尾
如果在车尾，控制员移到车头
否则控制员移到偷渡者之前所在的位置
 *
 *如果当前操作是'0'(控制员移动)：
*控制员根据偷渡者的位置移动：
如果偷渡者在控制员后面且控制员不在车头，则向前移动
如果偷渡者在控制员前面且控制员不在车尾，则向后移动
*偷渡者仍然按原方向移动一步
如果到达端点则调转方向

检查偷渡者和控制员是否在同一车厢
如果是，则控制员获胜，输出"Controller"和步数，程序结束
 */
#include <iostream>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    string d; cin >> d >> d;
    string s; cin >> s;

    int dir = (d == "head") ? -1 : 1;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            k += dir;
            if (k == 1 || k == n) dir = -dir;
            if (k == 1) m = n;
            else if (k == n) m = 1;
            else m = k - dir;
        } else {
            if (k > m && m != 1) --m;
            if (k < m && m != n) ++m;
            k += dir;
            if (k == 1 || k == n) dir = -dir;
        }
        if (k == m) {
            cout << "Controller " << i + 1 << endl;
            return 0;
        }
    }
    cout << "Stowaway" << endl;
    return 0;
}