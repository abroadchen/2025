//
// Created by Psy.C on 2026/1/24.
//

#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    map<int, int> mp;
    for (int i = 0, a; i < n; ++i) {
        cin >> a;
        if (a > 0) mp[i] = a;//位置->数量对
    }
    auto it = mp.begin();//指向当前目标位置的迭代器
    int i = 0, j;//从位置0开始
    while (!mp.empty()) {
        for (j = i; j < it->first; ++j) cout << 'R';//从当前位置i向右移动(R)到目标位置
        for (j = it->first; j < i; ++j) cout << 'L';//如需要，向左移动(L)
        cout << 'P';//拾取物品(P)
        it->second--;//减少当前位置的数量
        i = it->first;//更新当前位置i
        const auto it1 = it;//在可能改变之前保存当前迭代器
        //移动到映射中的相邻位置（如果不是开头就尝试向后移动）
        if (mp.size() > 1 && it != mp.begin()) --it;
        else if (mp.size() > 1) ++it;
        if (it1->second == 0) mp.erase(it1->first);
        if (mp.size() == 1) {//当只剩一个位置还有物品时 处理该位置的剩余物品
            it = mp.begin();
            if (i != it->first) {
                for (j = i; j < it->first; ++j) cout << 'R';
                for (j = it->first; j < i; ++j) cout << 'L';
                cout << 'P';
                it->second--;
            }
            //模式取决于位置是正还是负
            if (it->first > 0) for (j = 0; j < it->second; ++j) cout << "LRP";
            else for (j = 0; j < it->second; ++j) cout << "RLP";
            break;
        }
    }
    cout << '\n';
    return 0;
}