//
// Created by Psy.C on 2026/3/28.
//
/**
n: 参赛人数
b: 每场比赛需要的瓶子数
p: 每人需要的毛巾数
x: 总共需要的瓶子数（结果1）
y: 总共需要的毛巾数（结果2），每人p条毛巾，共n人

当有奇数个人时，需要安排一个人轮空
实际上是安排1场比赛（2人参赛，1人获胜，消耗2b瓶水）
剩余n-1个人继续比赛
n个人进行n/2场比赛
每场比赛消耗b瓶水，总共(n/2)2b = nb瓶
产生n/2个获胜者，n变为n/2
每个获胜者需要1瓶水，所以加n瓶

总共进行 n-1 场比赛（每次淘汰1人，需要淘汰n-1人才剩1个冠军）
每场比赛消耗 b 瓶水 → (n-1)*b 瓶
每个参赛者都需要1瓶水 → n*1 = n 瓶
总计：(n-1)b + n = nb - b + n = n*(b+1) - b

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, b, p;
int main() {
    fast;
    cin >> n >> b >> p;
    int x = 0, y = n*p;
    while (n > 1) {
        if (n%2) {
            x += b<<1;//需要2b瓶水
            x++;//产生1个获胜者
            n--;//变成偶数
        } else {
            x += n*b;//n个人，n/2场比赛，每场b瓶水，总共(n/2)*2b=n*b瓶
            n >>= 1;//进入下一轮
            x += n;//下一轮新增n个获胜者，每人1瓶水
        }
    }
    cout << x << ' ' << y << '\n';
    return 0;
}