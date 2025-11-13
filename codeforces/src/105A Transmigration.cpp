//
// Created by Psy.C on 2025/11/12.
//
/*
*n: 学生总数
m: 特殊名额数量
i: 循环变量
t: 临时变量，用于存储计算后的分数
ans: 计数器，初始化为0
k: 缩放因子
 *a，键为学生姓名(string)，值为分数(int)
 *
*遍历所有学生：
计算调整后的分数：原始分数*k + 微小值（防止浮点误差）
如果调整后分数小于100，将分数设为-1（表示不合格）
否则更新分数并增加合格人数计数
 *
*读入m个特殊名额获得者的姓名
如果该学生原本合格，则合格人数减1
否则将其分数设为0（表示通过特殊名额入选）
 *
 *输出最终入选总人数：合格人数 + 特殊名额数
 *只输出分数>=0的学生（即入选的学生）
 */
#include <iostream>
#include <map>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, i, t, ans(0); double k;
    cin >> n >> m >> k;
    string name;
    map<string, int> a;
    for (i = 0; i < n; ++i) {
        cin >> name >> t;
        a[name] = t;
    }
    for (auto it = a.begin(); it != a.end(); ++it) {
        t = (it->second * k) + 0.00000001;
        if (t < 100) it->second = -1;
        else {
            it->second = t;
            ans++;
        }
    }
    for (i = 0; i < m; ++i) {
        cin >> name;
        if (a[name] >= 100) ans--;
        else a[name] = 0;
    }
    cout << ans + m << '\n';
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it->second >= 0)
            cout << it->first << " " << it->second << '\n';
    }
    return 0;
}