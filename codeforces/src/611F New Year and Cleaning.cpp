//
// Created by Psy.C on 2026/3/23.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5, mod = 1e9+7;

char s[N];///输入的字符串，表示移动方向
///根据第k个字符更新坐标(x,y)
void get(ll &x, ll &y, int k) {
    if (s[k] == 'U') y--;//向上移动，y坐标减1
    if (s[k] == 'R') x++;
    if (s[k] == 'D') y++;
    if (s[k] == 'L') x--;
}
///n:操作次数，h:高度，w:宽度，ans:答案，c[]:记录时间点，e[]:记录类型
ll n, h, w, ans, c[N], e[N];
int main() {
    fast;
    scanf("%lld%lld%lld", &n, &h, &w);
    scanf("%s", s + 1);
    ll k = strlen(s + 1), x1 = 1, x2 = w, y1 = 1, y2 = h;//初始化矩形范围(1,1)到(w,h)
    for (int i = 1; i <= k; ++i) {//遍历每个移动指令
        get(x1, y1, i); get(x2, y2, i);//更新两个点的坐标
        //左边界越界时的处理
        if (x1 == 0 && x1 <= x2 && y1 <= y2)
            x1 = 1, ans = (ans + i*(y2-y1+1)%mod)%mod;//x1重置为1，并累加贡献
        //右边界越界时的处理
        if (x2 == w+1 && x1 <= x2 && y1 <= y2)
            x2 = w, ans = (ans + i*(y2-y1+1)%mod)%mod;
        //上边界越界时的处理
        if (y1 == 0 && x1 <= x2 && y1 <= y2)
            y1 = 1, ans = (ans + i*(x2-x1+1)%mod)%mod;
        //下边界越界时的处理
        if (y2 == h+1 && x1 <= x2 && y1 <= y2)
            y2 = h, ans = (ans + i*(x2-x1+1)%mod)%mod;
    }
    ll num = 0;//边界碰撞次数
    for (int i = 1; i <= k; ++i) {
        get(x1, y1, i); get(x2, y2, i);
        if (x1 == 0 && x1 <= x2 && y1 <= y2)
            x1 = 1, ans = (ans + (i+n)*(y2-y1+1)%mod)%mod, c[++num] = i, e[num] = 0;//记录x方向碰撞，e=0表示x方向
        if (x2 == w+1 && x1 <= x2 && y1 <= y2)
            x2 = w, ans = (ans + (i+n)*(y2-y1+1)%mod)%mod, c[++num] = i, e[num] = 0;
        if (y1 == 0 && x1 <= x2 && y1 <= y2)
            y1 = 1, ans = (ans + (i+n)*(x2-x1+1)%mod)%mod, c[++num] = i, e[num] = 1;
        if (y2 == h+1 && x1 <= x2 && y1 <= y2)
            y2 = h, ans = (ans + (i+n)*(x2-x1+1)%mod)%mod, c[++num] = i, e[num] = 1;
    }
    //没有边界碰撞且矩形仍存在，则无解
    if (!num && x1 <= x2 && y1 <= y2) { puts("-1"); return 0; }
    //从第2轮开始，计算剩余矩形大小
    for (ll j = 2, x = x2-x1+1, y = y2-y1+1; x > 0 && y > 0; j++)
        for (int i = 1; i <= num; i++) {//遍历所有边界碰撞事件
            //如果是y方向事件且矩形仍存在
            if (e[i] == 1 && x > 0 && y > 0)
                ans = (ans + max(x, 0ll)*(j*n%mod+c[i])%mod)%mod, y--;//更新答案并减少y维度
            if (e[i] == 0 && x > 0 && y > 0)
                ans = (ans + max(y, 0ll)*(j*n%mod+c[i])%mod)%mod, x--;
        }
    cout << ans%mod;
    return 0;
}