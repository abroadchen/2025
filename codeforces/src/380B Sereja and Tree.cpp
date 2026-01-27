//
// Created by Psy.C on 2026/1/26.
//

#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 7005
#define M 200000
using namespace std;

struct node {
    int l, r, val;
    node() = default;
    node(const int l, const int r, const int val) : l(l), r(r), val(val) {}
};

int n, dl[M], dr[M];//左右指针数组
vector<node> v[N];//每层存储的节点向量
int get(const int d, int x, int y) {//从第d层开始查询
    set<int> ans;//唯一值的集合
    for (int i = d; i <= n; ++i) {
        for (auto& c : v[i]) {//遍历第i层的所有节点
            if (c.l <= y && c.r >= x) ans.insert(c.val);//节点区间包含[x,y]，插入值到集合
        }
        x = dl[x] == -1 ? dr[x] : dl[x];//dl[x]是否存在更新x
        y = dr[y];
    }
    return static_cast<int>(ans.size());//不同值的数量
}

int main() {
    fast;
    int cnt = 1, p = 3;
    memset(dl, -1, sizeof(dl)); memset(dr, -1, sizeof(dr));
    dl[1] = 1; dr[1] = 2;
    for (int i = 2; i < M; ++i) {// 循环构建指针数组
        if (1<<cnt == i) {
            cnt++;
            dl[i] = p++;//设置dl[i]并递增p
        }
        dr[i] = p++;
    }
    int m; cin >> n >> m;
    for (int i = 0, op, d, x, y, val; i < m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> d >> x >> y >> val;
            v[d].emplace_back(x, y, val);//在第d层添加节点
        } else {
            cin >> d >> x;
            cout << get(d, x, x) << '\n';
        }
    }
    return 0;
}