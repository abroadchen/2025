//
// Created by Psy.C on 2026/2/3.
//
/*
* 时间复杂度：O(n) - 单次遍历
空间复杂度：O(n) - 存储序列
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    fast;
    int n; cin >> n;//操作次数
    bool flag = true;//符合条件
    vector<int> v[N];//类别i的序列
    for (int i = 0, a, b; i < n; ++i) {//a（数值）和b（类别）
        cin >> a >> b;
        if (a == 0) {
            if (v[b].empty()) v[b].push_back(a);//0只能作为序列的开头
        } else {
            if (v[b].empty()) { flag = false; break; }//设置失败标志
            //序列b的最后一个元素 中间有跳跃，不符合连续递增要求
            if (v[b][v[b].size()-1] < a - 1) { flag = false; break; }
            if (a == v[b][v[b].size()-1] + 1) v[b].push_back(a);//只接受连续递增的序列
        }
    }
    if (flag) cout << "YES\n"; else cout << "NO\n";
    return 0;
}