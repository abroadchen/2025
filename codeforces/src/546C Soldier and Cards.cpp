//
// Created by Psy.C on 2026/3/7.
//
/**
n：最大步数限制的基数
x, y：两个数组的长度
a, b：两个存储游戏牌的向量
sum：记录游戏进行的回合数
f：记录获胜玩家（1或2）
flag：标记游戏是否正常结束（1表示正常，0表示超时）

当两个向量都不为空时继续游戏
增加回合计数
获取两个向量的首元素（当前对决的两张牌）
如果a的牌更大：
将b的牌和a的牌依次加入a的末尾（胜利者获得这两张牌）
删除两个向量的首元素
如果b的牌更大：
将a的牌和b的牌依次加入b的末尾
删除两个向量的首元素
更新获胜者：如果b不空，f=2；如果a不空，f=1
如果回合数超过n的6次方，认为游戏陷入无限循环
设置flag为0，输出"-1"，跳出循环
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, x, y;
vector<int> a, b;
int main() {
    fast;
    cin >> n >> x;
    for (int i = 0, num; i < x; ++i) {
        cin >> num; a.push_back(num);
    }
    cin >> y;
    for (int i = 0, num; i < y; ++i) {
        cin >> num; b.push_back(num);
    }
    int sum = 0, f = 0, flag = 1;
    while (!a.empty() && !b.empty()) {
        sum++;
        int n1 = a.front(), n2 = b.front();
        if (n1 > n2) {
            a.push_back(n2); a.push_back(n1);
            auto t1 = a.begin(), t2 = b.begin();
            a.erase(t1); b.erase(t2);
        }
        if (n2 > n1) {
            b.push_back(n1); b.push_back(n2);
            auto t1 = a.begin(), t2 = b.begin();
            a.erase(t1); b.erase(t2);
        }
        if (!b.empty()) f = 2;
        if (!a.empty()) f = 1;
        if (sum >= n*n*n*n*n*n) {
            flag = 0;
            cout << "-1\n";
            break;
        }
    }
    if (flag) cout << sum << ' ' << f << '\n';
    return 0;
}