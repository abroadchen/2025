//
// Created by Psy.C on 2025/11/7.
//
/*
*mat 存储地图的二维字符串向量
dx 和 dy 数组表示四个方向的移动：右、左、下、上
*n, m: 地图的行数和列数
k: 最多收集的字母种类数
sx, sy: 起点'S'的坐标
gx, gy: 终点'T'的坐标
 *
*逐行读取地图字符串
查找字符'S'的位置作为起点
查找字符'T'的位置作为终点
 *
*pq: 优先队列，按照节点的第一个元素（距离）升序排列
ss: 集合，用于记录已访问的状态
 *
*第一个元素：启发式距离（当前点到终点的曼哈顿距离）
第二个元素：{{路径字符串, 字母掩码}, 一维坐标}
 *
*an: 当前位置的一维坐标
ay, ax: 当前位置的二维坐标
astr: 到达当前位置的路径字符串
mask: 收集到的字母集合（用位掩码表示）
弹出队列顶部元素
 *如果该状态（字母掩码+位置）已经处理过，则跳过；否则将其加入已访问集合
 *尝试四个方向的移动
 *检查新位置是否越界，如果越界则跳过
 *如果到达终点，则输出路径字符串并结束程序
*nstr: 新路径字符串（在原有基础上加上新位置的字符）
nmask: 新的字母集合掩码（如果新位置是字母，则将其对应位设为1）
*如果收集的字母种类不超过k个，则将新状态加入优先队列：
优先级：曼哈顿距离 + 路径长度
状态信息：路径字符串、字母掩码、新位置坐标
 *
 */
#include <vector>
#include <iostream>
#include <set>
#include <cstdlib>
#include <queue>
#include <algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef long long ll;
typedef pair<ll, pair<pair<string, ll>, ll>> node;
vector<string> mat;
int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

ll dist(ll x1, ll x2, ll y1, ll y2) { return abs(y2-y1) + abs(x2-x1); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n, m, k, sx, sy, gx, gy;
    cin >> n >> m >> k;
    string t;
    rep(i,n) {
        cin >> t;
        mat.push_back(t);
        rep(j,m) {
            if (mat[i][j] == 'S') { sy = i; sx = j; }
            else if (mat[i][j] == 'T') { gy = i; gx = j; }
        }
    }
    priority_queue<node, vector<node>, greater<node> > pq;
    set<pair<ll, ll>> ss;
    pq.push({dist(sx, gx, sy, gy), {{"", 0}, sy*m+sx}});
    while (!pq.empty()) {
        ll an = pq.top().second.second, ay = pq.top().second.second / m,
        ax = pq.top().second.second % m;
        string astr = pq.top().second.first.first;
        ll mask = pq.top().second.first.second; pq.pop();
        if (ss.count({mask, an})) continue;
        ss.insert({mask, an});
        rep(i, 4) {
            int nx = ax + dx[i], ny = ay + dy[i];
            if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
            if (ny == gy && nx == gx) { cout << astr << endl; return 0; }
            string nstr = astr + mat[ny][nx];
            ll nmask = mask | (1 << (mat[ny][nx] - 'a'));
            if (__builtin_popcount(nmask) <= k)
                pq.push(make_pair(dist(nx, gx, ny, gy) + nstr.size(),
                make_pair(make_pair(nstr, nmask), ny * m + nx)));
        }
    }
    cout << -1 << endl;
    return 0;
}