//
// Created by Psy.C on 2026/1/31.
//
/**
* a代表总页数
b代表当前页码
c代表显示范围（当前页前后各c页）
输出格式化页码，当前页用括号高亮，边界页码用<< >>标记
特殊处理第一页和最后一页的情况
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b, c; cin >> a >> b >> c;
    for (int i = b - c; i <= b + c; ++i) if (i > 0) {
        if (i == 1) {//输出"(1) "；否则输出"1 "
            if (b == 1) cout << '(' << 1 << ')' << ' ';
            else cout << 1 << ' ';
            continue;
        }
        if (i == a) {//输出"(b)"；否则输出"a "
            if (b == a) cout << '(' << b << ')';
            else cout << a << ' ';
            break;
        }
        if (i == b - c) cout << "<< " << i << ' ';//输出"<< " + i + " "
        else if (i == b) cout << '(' << b << ')' << ' ';//输出"(b) "
        else if (i == b + c) cout << i << " >>" << ' ';//输出i + " >> "
        else cout << i << ' ';
    }
    return 0;
}