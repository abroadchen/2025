//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
m：颜色 → 宝石名 的映射表
紫色 = Power 力量
绿色 = Time 时间
蓝色 = Space 空间
橙色 = Soul 灵魂
红色 = Reality 现实
黄色 = Mind 心灵
读入 n，再依次读入 n 个"已收集的颜色"。
每个读入的颜色对应的 m[s] 被覆盖成空字符串，表示"这颗宝石已经有了，不用输出它"。
输出缺失数量 6 - n。
用 views::values 遍历 map 的所有value（宝石名）‍，跳过空字符串（即已拥有的），输出去掉的（缺失的）宝石名
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

map<string,string> m;
void get() {
    m["purple"]="Power";
    m["green"]="Time";
    m["blue"]="Space";
    m["orange"]="Soul";
    m["red"]="Reality";
    m["yellow"]="Mind";
}

int n;
string s;
int main() {
    fast;
    get(); cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>s; m[s] = "";
    }
    cout << 6-n << '\n';
    for (const auto &val: m | views::values) {
        if (!val.empty())
            cout << val << '\n';
    }
    return 0;
}