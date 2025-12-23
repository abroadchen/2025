//
// Created by Psy.C on 2025/12/23.
//
/*
*n, m：网格的行数和列数
s1, s2：两个集合数组，用于存储特定方向上的障碍物坐标
mp：映射，记录障碍物位置
 *
 *计算斜线索引：方向1用x-y+m+1，方向2用x+y
 *在网格中添加障碍物：同时更新两个方向的集合和映射
 *在网格边界添加障碍物
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <iostream>
#include <set>
#include <map>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200010
using namespace std;

int n, m;
set<int> s1[N], s2[N];
map<pair<int, int>, bool> mp;
int get(const int x, const int y, const int d) { return d == 1 ? x - y + m + 1 : x + y; }
void add(int x, int y) {
    s1[get(x, y, 1)].insert(x);
    s2[get(x, y, 2)].insert(x);
    mp[{x, y}] = true;
}

void init() {
    for (int i = 0; i <= m + 1; ++i) { add(0, i); add(n + 1, i); }
    for (int i = 1; i <= n; ++i) { add(i, 0); add(i, m + 1); }
}

struct node { int x, y, d; };//坐标(x,y)和方向d
bool ok(int x, int y) { return mp[{x, y}]; }//判断坐标(x,y)是否为障碍物
pair<node, int> dfs(const node u) {
    node v{};
    set<int>::iterator it;
    if (u.d == 1) {//方向1(NW)：沿左上对角线移动，碰到障碍物后反弹
        it = s1[get(u.x, u.y, 1)].lower_bound(u.x); --it;
        v.x = u.x - (abs(*it - u.x) - 1); v.y = u.y - (abs(*it - u.x) - 1);
        if (ok(v.x - 1, v.y) && ok(v.x, v.y - 1)) v.d = 3;
        else if (ok(v.x - 1, v.y)) v.y--, v.d = 4;
        else if (ok(v.x, v.y - 1)) v.x--, v.d = 2;
        else v.d = 3;
    }
    if (u.d == 2) {//方向2(NE)：沿右上对角线移动，碰到障碍物后反弹
        it = s2[get(u.x, u.y, 2)].lower_bound(u.x); --it;
        v.x = u.x - (abs(*it - u.x) - 1); v.y = u.y + (abs(*it - u.x) - 1);
        if (ok(v.x - 1, v.y) && ok(v.x, v.y + 1)) v.d = 4;
        else if (ok(v.x - 1, v.y)) v.y++, v.d = 3;
        else if (ok(v.x, v.y + 1)) v.x--, v.d = 1;
        else v.d = 4;
    }
    if (u.d == 3) {//方向3(SE)：沿右下对角线移动，碰到障碍物后反弹
        it = s1[get(u.x, u.y, 1)].lower_bound(u.x);
        v.x = u.x + (abs(*it - u.x) - 1); v.y = u.y + (abs(*it - u.x) - 1);
        if (ok(v.x + 1, v.y) && ok(v.x, v.y + 1)) v.d = 1;
        else if (ok(v.x + 1, v.y)) v.y++, v.d = 2;
        else if (ok(v.x, v.y + 1)) v.x++, v.d = 4;
        else v.d = 1;
    }
    if (u.d == 4) {//方向4(SW)：沿左下对角线移动，碰到障碍物后反弹
        it = s2[get(u.x, u.y, 2)].lower_bound(u.x);
        v.x = u.x + (abs(*it - u.x) - 1); v.y = u.y - (abs(*it - u.x) - 1);
        if (ok(v.x + 1, v.y) && ok(v.x, v.y - 1)) v.d = 2;
        else if (ok(v.x + 1, v.y)) v.y--, v.d = 1;
        else if (ok(v.x, v.y - 1)) v.x++, v.d = 3;
        else v.d = 2;
    }
    return {v, abs(*it - u.x)};//返回新节点和移动距离
}

bool same(const node a, const node b) {//判断两个节点是否完全相同
    if (a.x == b.x && a.y == b.y && a.d == b.d) return true;
    return false;
}
ll ans;
bool ok(node u) {//计算路径长度直到回到起始状态 检查是否存在死循环（相反方向的冲突）
    const node v = u;//记录初始状态
    do {
        const pair<node, int> cur = dfs(u);//执行一次移动
        ans += 1ll * cur.second;//累加移动距离
        switch (cur.first.d) {
            case 1: if (u.d == 3) return false; break;//1和3相反
            case 2: if (u.d == 4) return false; break;//2和4相反
            case 3: if (u.d == 1) return false; break;//3和1相反
            case 4: if (u.d == 2) return false; break;//4和2相反
            default: ;
        }
        u = cur.first;//更新当前状态
    } while (!same(v, u));//直到回到初始状态
    return true;//成功完成一个循环
}

int main() {
    fast;
    int k; cin >> n >> m >> k; init();//读入网格大小和障碍物数量，初始化边界
    for (int i = 1, x, y; i <= k; ++i) { cin >> x >> y; add(x, y); }//读入k个障碍物坐标并添加到网格中
    int x, y, d; char ch[5]; string str; cin >> x >> y >> str;
    strcpy(ch + 1, str.c_str());
    if (ch[1] == 'N' && ch[2] == 'W') d = 1;//将字符串转换为数字方向
    if (ch[1] == 'N' && ch[2] == 'E') d = 2;
    if (ch[1] == 'S' && ch[2] == 'E') d = 3;
    if (ch[1] == 'S' && ch[2] == 'W') d = 4;
    node st = {x, y, d}; st = dfs(st).first;//执行一次移动，如果发现死循环则调整方向
    if (!ok(st)) {
        ans--;
        switch (st.d) {
            case 1: st.d = 3; break;
            case 2: st.d = 4; break;
            case 3: st.d = 1; break;
            case 4: st.d = 2; break;
            default: ;
        }
        ok(st);//重新计算从修正后状态开始的完整循环路径
    }
    cout << ans << '\n';
    return 0;
}