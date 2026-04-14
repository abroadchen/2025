//
// Created by Psy.C on 2026/4/14.
//
/**
计算哈希表中所有数字的加权和
fst: 键（数字值）
snd: 值（出现次数）
ans += snd*fst: 每个数字乘以其出现次数的总和

all = sum(mp): 计算所有数字的总和
if (mp.size() == 5): 如果5个数字都不同
直接输出总和
退出程序
重新定义局部变量sum（注意：与函数名同名，但作用域不同）
遍历哈希表中每个数字：
if (snd > 1): 如果该数字出现次数>1（有重复）
snd >= 3 ? 3*fst : 2*fst:
如果出现3次或以上，取3个该数字的和
如果只出现2次，取2个该数字的和
b = max(a, b): 记录最大重复价值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

unordered_map<int, int> mp;///每个数字的出现次数
int sum(unordered_map<int, int>& x) {
    int ans = 0;
    for (auto &[fst, snd] : x)
        ans += snd*fst;
    return ans;
}

int x;
int main() {
    fast;
    for (int i = 1; i <= 5; ++i) {
        cin >> x; mp[x]++;
    }
    int all = sum(mp);
    if (mp.size() == 5) {
        cout << all << '\n';
        return 0;
    }
    int a = 0, b = 0;
    for (auto &[fst, snd] : mp) {
        if (snd > 1)
            a = snd >= 3 ? 3*fst : 2*fst;
        b = max(a, b);
    }
    cout << all - b << '\n';
    return 0;
}