//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
读入 2n 个权值，全部进 q（全局堆，之后每次“自由拿”都取最大未取的）
对每个绑定对 (x,y)：把权值较大的一端压入 tq（绑定堆）。
记录双向映射 mp[x]=y, mp[y]=x
= 剩余未处理的绑定数量。
n 更新为总元素数 2n。
读 k，f 是“本回合是否已经因绑定摆脱自由选择”的标记
模式 k == 2（玩家轮流，先自己拿再替对方拿）

每轮循环整体流程大概是：

当前玩家自由选择（参与者 A）；
有时候会被迫带出同伴（对手 B）——即这段输出两个数、f=1
玩家1真正决策的“拿”靠 cin >> x（输入给定了，它是在模仿代码写死策略）。
拿完 x 若触发它的绑定 mp[x]，则带动它（对手）也被拿走 —— 这是把绑定对整体出清。
若没触发绑定，那么轮到对手，对手贪心地从绑定堆 tq 里抢一个绑定对的“大头”‍；没有绑定的话就从全局 q 抢最大的。
也就是说：尽量优先拿“成对的绑定大件”，避免对手平分权重——这是经典的“配对博弈取最优”的贪心策略。
和 k==2 唯一的区别是顺序不同：先帮自己用堆抢一个，再读入对手的拿取（cin >> x）并处理绑定。即双方的行动顺序/优先权颠倒
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 3e5+10;

ll n, m, a[N], x, y, t, k, vis[N];
priority_queue<ii> q, tq;
map<int,int> mp;
int main() {
    cin >> n >> m;
    rep(i,n<<1) { cin >> a[i]; q.emplace(a[i], i); }
    rep(i,m) {
        cin >> x >> y;
        if (a[x] > a[y]) tq.emplace(a[x], x);
        else tq.emplace(a[y], y);
        mp[x] = y; mp[y] = x;
    }
    t = m; n = n<<1;
    cin >> k; int f = 0;
    if (k == 2) {
        while (n) {//还有元素未拿
            //玩家1拿走 x（自由选，输入里的动作）
            cin >> x; n--; vis[x] = 1; f = 0;
            if (mp[x] && !vis[mp[x]]) {//x 有绑定且绑定还没被拿
                cout << mp[x] << '\n';//玩家1的"取x"顺带触发拿了它的绑定
                t--; vis[mp[x]] = 1; n--; f = 1;//消耗一个绑定，标记伙伴已拿，f=1
            }
            if (n == 0) break;//取完结束
            //若本回合还没触发绑定动作，则玩家要给"对手"选：
            if (t && f == 0) {//还有绑定对 → 从绑定堆里给对手拿最大
                while (vis[tq.top().second]) tq.pop();//跳过已拿
                cout << tq.top().second << '\n';
                vis[tq.top().second] = 1; t--; n--;
            } else if (!t && f == 0) {
                while (vis[q.top().second]) q.pop();//没有绑定对 → 从全局堆给对手拿最大
                cout << q.top().second << '\n'; n--;
                vis[q.top().second] = 1; q.pop();
            }
        }
    } else {
        while (n) {
            if (t && f == 0) {
                while (vis[tq.top().second]) tq.pop();
                cout << tq.top().second << '\n';
                vis[tq.top().second] = 1; t--; n--;
            } else if (!t && f == 0) {
                while (vis[q.top().second]) q.pop();
                cout << q.top().second << '\n'; n--;
                vis[q.top().second] = 1; q.pop();
            }
            if (n == 0) break; f = 0;
            cin >> x; n--; vis[x] = 1;
            if (mp[x] && !vis[mp[x]]) {
                cout << mp[x] << '\n';
                t--; vis[mp[x]] = 1; n--; f = 1;
            }
        }
    }
    return 0;
}