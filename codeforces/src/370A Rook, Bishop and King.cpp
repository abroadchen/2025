//
// Created by Psy.C on 2026/1/21.
//
/**
 *1. 车 (Rook) 步数
* 1步: 如果在同一行或同一列 (r1 == r2 || c1 == c2)
2步: 否则需要2步（先移动到同行或同列，再移动到目标位置）
 *2. 象 (Bishop) 步数
*0步: 如果两点不在同一颜色格子上（r1+c1 和 r2+c2 奇偶性不同），象无法到达
1步: 如果在同一条对角线上（斜率为±1的直线）
r1 - c1 == r2 - c2: 在斜率为1的对角线上
r1 + c1 == r2 + c2: 在斜率为-1的对角线上
2步: 否则最多需要2步
 *3. 王 (King) 步数
*切比雪夫距离: 王可以斜向移动，所以最少步数是 max(|r1-r2|, |c1-c2|)
这是曼哈顿距离和对角线移动结合的结果
 *
 *时间复杂度: O(1)，纯数学计算
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;//起始坐标 目标坐标
    if (r1 == r2 && c1 == c2) {
        cout << "0 0 0";
        return 0;
    }
    if (r1 == r2 || c1 == c2) cout << "1 "; else cout << "2 ";
    if ((r1 + c1) % 2 != (r2 + c2) % 2) cout << "0 ";
    else if (r1 - c1 == r2 - c2 || r1 + c1 == r2 + c2) cout << "1 ";
    else cout << "2 ";
    cout << max(abs(r1 - r2), abs(c1 - c2));
    return 0;
}