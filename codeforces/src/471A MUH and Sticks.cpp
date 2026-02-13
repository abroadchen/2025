//
// Created by Psy.C on 2026/2/13.
//
/**
时间复杂度：O(1)（固定6次循环）
空间复杂度：O(1)（固定大小数组）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int cnt[10], id;

int main() {
    fast;
    for (int i = 0, x; i < 6; ++i) {
        cin >> x; cnt[x]++;//每个数字出现的次数
        if (cnt[x] == 4) id = x;//出现4次的数字
    }
    if (!id) { cout << "Alien\n"; return 0; }//没有数字出现4次
    cnt[id] -= 4;//减去4个相同的数字（移除4个一样的）
    int ans = 0;
    for (const int i : cnt) if (i) ans++;//剩余的不同数字个数
    if (ans == 1) cout << "Elephant\n";//只有1种
    else cout << "Bear\n";
    return 0;
}