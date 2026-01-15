//
// Created by Psy.C on 2026/1/15.
//

#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 111111
#define ip pair<int, pair<char, int>>
#define ii pair<int, int>
using namespace std;

ip n_pair(int st, char c='E', int tim=0) {
    return {st, {c, tim}};
}

vector<ip> ans;// 存储结果的操作序列
void get(const int x, const int y) {
    if (x != 0) {
        const char c = x > 0 ? 'R' : 'L';
        ans.push_back(n_pair(1, c, abs(x)));//添加移动指令(type=1, 方向, 距离)
    }
    if (y != 0) {
        const char c = y > 0 ? 'U' : 'D';
        ans.push_back(n_pair(1, c, abs(y)));
    }
    ans.push_back(n_pair(2));//添加type=2的特殊指令 停留
    //对称的返回操作
    if (y != 0) {
        const char c = y < 0 ? 'U' : 'D';//如果原来向下(-)，返回时向上(U)；反之亦然
        ans.push_back(n_pair(1, c, abs(y)));
    }
    if (x != 0) {
        const char c = x < 0 ? 'R' : 'L';
        ans.push_back(n_pair(1, c, abs(x)));
    }
    ans.push_back(n_pair(3));//添加type=3的结束指令
}


int main() {
    fast;
    int n; cin >> n; ii b[N];//存储第i个目标点的{x,y}坐标
    for (int i = 0; i < n; ++i) cin >> b[i].first >> b[i].second;
    //先按|x|排序，再按|y|排序 优先处理距离原点近的点
    sort(b, b + n, [](const ii& o1, const ii& o2) {
        if (abs(o1.first) != abs(o2.first)) return abs(o1.first) < abs(o2.first);
        return abs(o1.second) < abs(o2.second);
    });
    //遍历排序后的目标点，为每个点生成移动操作序列
    for (int i = 0; i < n; ++i) get(b[i].first, b[i].second);
    cout << ans.size() << '\n';//输出总的操作指令数量
    for (auto [fst, snd] : ans) {
        if (fst != 1) cout << fst << '\n'; else {//如果不是type=1的移动指令，只输出fst
            cout << fst << ' ' << snd.second << ' ' << snd.first << '\n';
        }
    }
    return 0;
}