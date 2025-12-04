//
// Created by Psy.C on 2025/12/3.
//
/*
*条件判断：将k转换为bool类型进行判断，确保k不为0
如果k不为0，则计算直线与x轴的交点：当y=0时，0 = kx + b，解得x = -b/k
将这个x值作为键存入map中，值设为true
由于map的键是唯一的，重复的x值不会增加map的大小
 *输出map的大小，即不同x轴交点的数量
 *
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
long double k, b;//斜率k和截距b
map<long double, bool> mp;//存储唯一的x值

int main() {
    fast;
    cin >> n;
    while (n--) {
        cin >> k >> b;
        if (static_cast<bool>(k)) mp[-b/k] = true;
    }
    cout << mp.size() << '\n';
    return 0;
}