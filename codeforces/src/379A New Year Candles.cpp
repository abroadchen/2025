//
// Created by Psy.C on 2026/1/24.
//
/**
* a: 你最初拥有的饮料瓶数
b: 兑换1瓶新饮料需要的空瓶数
 *all: 总共喝的饮料数，初始等于起始瓶数
 *
*while (a >= b): 当你有足够的空瓶时继续兑换
a / b: 通过兑换可以获得的新饮料数量
all += a / b: 将新获得的饮料加到总消费量中
a % b: 无法兑换的剩余瓶子
a / b: 刚刚消费的饮料变成的空瓶
a = a % b + a / b: 更新下一轮的总空瓶数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b; cin >> a >> b;
    int all = a;
    while (a >= b) all += a / b, a = a % b + a / b;
    cout << all << '\n';
    return 0;
}