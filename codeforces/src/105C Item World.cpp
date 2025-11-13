//
// Created by Psy.C on 2025/11/12.
//
/*
 *定义物品结构体
*name：名称
stat：属性值
siz：大小/容量
tp：类型（0=武器，1=护甲，2=其他）
 *定义资源结构体
*name：名称
bonus：加成值
tp：类型
home：所属物品的索引
 *
*sa[3]：按类型分类的物品索引向量（3种类型）
sb[3]：按类型分类的资源索引向量（3种类型）
res：存储未分配资源的向量
items：物品名称到索引的映射
resids：资源名称到索引的映射
 *
*n（物品数）、k（资源数）
pts[N]：物品获得的额外点数
occup[M]：资源占用标记数组
 *
*s1：物品名称
s2：物品类型
x,y,z：三种属性值
w：物品容量
累计总容量sum
 *
*s1：资源名称
s2：资源类型
x：加成值
s3：所属物品名称
 *
 *
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int N = 105, M = 1005;

struct item {
    string name;
    int stat, siz, tp;
} a[N];
struct resid {
    string name;
    int bonus, tp, home;
} b[M];

vector<int> sa[3], sb[3], res;
map<string, int> items, resids;


int n, k, pts[N], occup[M];
void solve() {
    cin >> n;
    int sum = 0, x, y, z, w;
    string s1, s2, s3, s4;
    for (int i = 1; i <= n; ++i) {
        cin >> s1 >> s2 >> x >> y >> z >> w;
        sum += w;
        a[i].name = s1;
        if (s2 == "weapon") { a[i].tp = 0; a[i].stat = x; }
        else if (s2 == "armor") { a[i].tp = 1; a[i].stat = y; }
        else { a[i].tp = 2; a[i].stat = z; }
        sa[a[i].tp].push_back(i);
        items[s1] = i;
        a[i].siz = w;
    }
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        cin >> s1 >> s2 >> x >> s3;
        b[i].name = s1; b[i].bonus = x;
        if (s2 == "gladiator") b[i].tp = 0;
        else if (s2 == "sentry") b[i].tp = 1;
        else b[i].tp = 2;
        sb[b[i].tp].push_back(i);
        if (a[items[s3]].tp == b[i].tp)
            pts[items[s3]] += b[i].bonus;
        b[i].home = items[s3];
    }
    if (k == sum) {
        int ans[3] = {0, 0, 0};
        for (int i = 1; i <= n; ++i) {
            int tp = a[i].tp;
            if (a[ans[tp]].stat + pts[ans[tp]] <
                a[i].stat + pts[i]) ans[tp] = i;
        }
        for (int i = 0; i <= 2; ++i) {
            cout << a[ans[i]].name << " " << a[ans[i]].siz << " ";
            for (int j = 1; j <= k; ++j) if (b[j].home == ans[i]) {
                cout << b[j].name << " ";
            }
            cout << '\n';
        }
    } else {
        int ans[3], rs[3] = {-1, -1, -1};
        for (int i = 0; i <= 2; ++i) {
            sort(sb[i].begin(), sb[i].end(), [](int x, int y) {
                return b[x].bonus > b[y].bonus;
            });
        }
        for (int i = 1; i <= n; ++i) {
            int used = 0;
            for (int j : sb[a[i].tp]) {
                if (used == a[i].siz) break;
                used++;
                a[i].stat += b[j].bonus;
            }
            if (a[i].stat > rs[a[i].tp]) {
                ans[a[i].tp] = i;
                rs[a[i].tp] = a[i].stat;
            }
        }
        for (int i = 0; i <= 2; ++i) {//标记已被分配的资源
            int used = 0;
            for (int j : sb[i]) {
                if (used == a[ans[i]].siz) break;
                used++;
                occup[j] = 1;
            }
        }
        for (int i = 1; i <= k; ++i) if (!occup[i]) {//收集未被分配的资源
            res.push_back(i);
        }
        int fp = 0;
        for (int i = 0; i <= 2; ++i) {
            cout << a[ans[i]].name << " " <<
                min(a[ans[i]].siz,
                    (int)(sb[i].size() + res.size() - fp)) << " ";
            int used = 0;
            for (int j : sb[i]) {
                if (used == a[ans[i]].siz) break;
                used++;
                cout << b[j].name << " ";
            }
            while (fp < res.size()) {
                if (used == a[ans[i]].siz) break;
                used++;
                cout << b[res[fp++]].name << " ";
            }
            cout << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
    return 0;
}