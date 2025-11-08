//
// Created by Psy.C on 2025/11/7.
//
/*
*int n;: 存储操作次数
string s;: 存储操作命令
vector<int> v;: 维护一个有序整数数组
 *
*使用lower_bound找到x应该插入的位置(保持数组有序)
在该位置插入x值
 *
*使用lower_bound找到x在数组中的位置
删除该位置的元素
 *
*从索引2开始，每隔5个元素取一个(即索引2,7,12,17...)
将这些位置的元素值累加到ans中
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
int n;
string s;
vector<int> v;

int main() {

    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    while (n--) {
        int x; cin >> s;
        if (s[0] == 'a') {
            cin >> x;
            v.insert(lower_bound(v.begin(), v.end(), x), x);
        } else if (s[0] == 'd') {
            cin >> x;
            v.erase(lower_bound(v.begin(), v.end(), x));
        } else {
            ll ans(0);
            for (int i = 2; i < v.size(); i += 5) ans += v[i];
            cout << ans << '\n';
        }
    }
    return 0;
}