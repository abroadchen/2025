//
// Created by Psy.C on 2025/9/22.
//
/*
*直接构造：直接在容器的内存位置构造对象，避免临时对象的创建和拷贝
性能更好：减少了拷贝或移动操作，提高了效率
参数传递：接受构造函数的参数，而不是对象本身
 *ans.back()：获取vector中最后一个元素（即最后一个pair）
 *ans.end()[-2]：从末尾迭代器往前数2个位置，即倒数第二个元素
 */

#include <iosfwd>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; cin >> n;// 读取矩形个数n
    vector<array<int, 3>> a;// 定义三维数组向量，存储事件点
    for (int i = 0; i < n; ++i) {
        int h, l, r; cin >> h >> l >> r;
        a.push_back({l, 1, h});// 添加左边界事件：{左边界坐标, 1(进入), 高度}
        a.push_back({r, -1, h});
    }
    sort(a.begin(), a.end());// 按照x坐标对所有事件点排序

    multiset<int> s{0};// 多重集合存储当前活跃的高度，初始包含地面高度0
    vector<pair<int, int>> ans;
    for (int i = 0, j = 0; i < 2 * n; i = j) {// 扫描线主循环，处理相同x坐标的事件组
        while (j < 2 * n && a[i][0] == a[j][0]) {
            if (a[j][1] == 1) s.insert(a[j][2]);
            else s.extract(a[j][2]);// 如果是离开事件，将高度从集合中移除
            j++;
        }
        int H = *s.rbegin();// 获取当前最大高度（多重集合的最后一个元素）
        if (ans.empty()) {
            ans.emplace_back(a[i][0], 0);// 添加起点到地面的线段
            ans.emplace_back(a[i][0], H);// 添加地面到当前高度的线段
        } else {
            if (ans.back().second == ans.end()[-2].second) {// 如果最后两个点高度相同
                ans.back().first = a[i][0];// 合并为一条水平线
            } else {
                ans.emplace_back(a[i][0], ans.back().second);// 添加垂直线段
            }// 如果高度变化，添加新高度点
            if (ans.back().second != H) ans.emplace_back(a[i][0], H);
        }
    }

    cout << ans.size() << "\n";
    for (auto [x, y] : ans) cout << x << " " << y << "\n";

    return 0;
}