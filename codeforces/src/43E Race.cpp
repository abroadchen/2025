//
// Created by Psy.C on 2025/9/26.
//
/*
*n：物体数量
s：路程长度
seg[N]：大小为N的向量数组，每个元素存储pair<int,int>，表示速度和时间区间
 *
 *定义solve函数，计算物体x和物体y相遇的次数
*ans：相遇次数计数器
dx, dy：物体x和y当前段的索引
lastx, nowx：物体x的上一位置和当前位置
lasty, nowy：物体y的上一位置和当前位置
t：当前时间
 *
 *计算当前时间段的长度：取两个物体当前段结束时间的较小值减去当前时间
 *更新当前时间
 *
 *如果两个物体当前位置不同，则更新它们的上一位置
*根据当前速度和时间更新两个物体的位置：
seg[x][dx].first是物体x当前段的速度
seg[y][dy].first是物体y当前段的速度
 *
*判断是否发生相遇：
1ll表示长整型字面量1
如果上次位置差和当前位置差符号相反，说明发生了超越，相遇次数加1
 *
*根据当前段的结束时间决定移动哪个索引：
如果x物体先结束当前段，则dx++
如果y物体先结束当前段，则dy++
如果同时结束，则都++
 *
*将相对时间转换为绝对时间（前缀和）
每段的时间变成从开始到该段结束的累计时间
 *
 *
 *
 */
#include <iosfwd>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 123;
typedef long long ll;
int n, s;
vector<pair<int,int>> seg[N];

int solve(int x, int y) {
    int ans(0), dx(0), dy(0), lastx(0), nowx(0), lasty(0), nowy(0), t(0);
    while (nowx < s && nowy < s) {//当两个物体都未到达终点时继续循环
        int tmp = min(seg[x][dx].second, seg[y][dy].second) - t;
        t += tmp;
        if (nowx != nowy) { lastx = nowx; lasty = nowy; }
        nowx += seg[x][dx].first * tmp;
        nowy += seg[y][dy].first * tmp;
        if (1ll * (lastx - lasty) * (nowx - nowy) < 0) ans++;
        if (seg[x][dx].second < seg[y][dy].second) dx++;
        else if (seg[x][dx].second > seg[y][dy].second) dy++;
        else { dx++; dy++; }
    }
    return ans;
}


int main() {

    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>s;
    int c;//声明变量c用于存储每段的数量

    for (size_t i = 0; i < n; ++i) {
        cin>>c;//读取物体i的段数c
        for (int j = 0; j < c; ++j) {
            int v, t; cin>>v>>t;//读取c段的速度v和时间t，并存储到seg[i]中
            seg[i].push_back(make_pair(v,t));
        }
        for (int j = 1; j < c; ++j) seg[i][j].second += seg[i][j-1].second;
    }

    int ans(0);//初始化总相遇次数ans为0
    for (size_t i = 0; i < n; ++i) {//双重循环比较每对物体(i,j)，其中j>i
        for (size_t j = i + 1; j < n; ++j)
            ans += solve(i, j);
    }
    cout << ans << '\n';
    return 0;
}