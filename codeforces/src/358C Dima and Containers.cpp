//
// Created by Psy.C on 2026/1/18.
//

#include <algorithm>
#include <iostream>
#include <bitset>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define ii pair<int, int>
using namespace std;

string s[] = {
    "0","1","2","3","pushStack","pushQueue",
    "pushFront","pushBack","popStack","popQueue",
    "popFront","popBack"
};

int main() {
    fast;
    int n, m = 1; cin >> n;
    bitset<N> vis;//标记某些位置
    vector<ii> q[N];
    vector<int> ans[N];
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (!x) { vis[m] = true; m++; } //进入下一个组
        else q[m].emplace_back(x, i);//添加到第m组
    }
    for (int i = 1, id = 1; i <= m; ++i) {//遍历每个组
        id += static_cast<int>(q[i].size());//增加当前组的元素数量
        ranges::sort(q[i], greater<>());//对当前组按降序排序
        for (int j = 0; j < 3 && j < q[i].size(); ++j)//处理前3个元素
            ans[q[i][j].second].push_back(4 + j);//对应4,5,6
        for (int j = 3; j < q[i].size(); ++j)//处理第4个及以后的元素
            ans[q[i][j].second].push_back(7);//对应7
        if (vis[i]) {//当前组被标记
            ans[id].push_back(min(static_cast<int>(q[i].size()), 3));//添加0-3的数字
            for (int j = 0; j < 3 && j < q[i].size(); ++j)//添加pop操作
                ans[id].push_back(j + 8);//对应8,9,10
        }
        id++;
    }
    for (int i = 1; i <= n; ++i) {//遍历每个输出位置
        for (const auto pos : ans[i]) {//遍历当前位置的所有操作
            cout << s[pos];//输出对应的操作字符串
            if (pos != ans[i].back()) cout << ' ';//不是最后一个，输出空格分隔
        }
        cout << '\n';
    }
    return 0;
}