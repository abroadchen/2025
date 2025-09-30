//
// Created by Psy.C on 2025/9/28.
//
/*
*n: 区间数量
m: map容器，键是区间左端点，值是包含{右端点,索引}的向量
读取每个区间的左右端点，并按左端点分组存储
 *
*res: 结果数组，存储每个区间分配的时间点
in: set容器，存储当前可选的区间{右端点,索引}，按键值排序
cur: 当前考虑的时间点
 *
 *
*当 i != n-1 时（不是最后一个元素）
[i==n-1] = [false] = [0]
" \n"[0] = ' '  // 空格字符
当 i == n-1 时（是最后一个元素）
[i==n-1] = [true] = [1]
" \n"[1] = '\n' // 换行字符
 *
 */
#include <ios>
#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin>>n;
    map<int,vector<array<int, 2>>> m;

    for (int i = 0; i < n; ++i) {
        int l, r; cin>>l>>r;
        m[l].push_back({r,i});
    }

    vector<int> res(n);
    set<array<int, 2>> in;

    int cur(0);
    while (in.size() || m.size()) {//当还有未处理的区间时继续
        if (in.empty()) cur = m.begin()->first;//如果没有可选区间，跳转到下一个最早开始的区间
        for (auto [r, id] : m[cur]) in.insert({r,id});//将当前时间点开始的所有区间加入可选集合
        m.erase(cur);//从map中删除键为cur的元素，因为这些区间已经被处理过了
        auto [r, id] = *in.begin();
        in.erase(in.begin());
        res[id] = cur++;//为选中的区间分配当前时间点，并推进时间
    }

    for (int i = 0; i < n; ++i) cout<<res[i]<<" \n"[i==n-1];
    return 0;
}