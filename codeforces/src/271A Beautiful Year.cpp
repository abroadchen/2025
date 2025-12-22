//
// Created by Psy.C on 2025/12/22.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int y; cin >> y;//起始年份
    while (true) {//直到满足特定条件才会跳出
        y += 1;//检查下一个年份
        const int a = y / 1000,//提取年份y的千位数字
        b = y / 100 % 10,//先去掉最低两位数字  取余数得到百位数字
        c = y / 10 % 10,//先去掉最低一位数字 取余数得到十位数字
        d = y % 10;//直接取最低位数字
        if (a != b && a != c && a != d &&//千位数字与其它三位都不同
            b != c && b != d && c != d) break;//百位数字与十位、个位都不同 十位数字与个位数字不同
    }
    cout << y << "\n";//第一个各位数字都不相同的年份
    return 0;
}