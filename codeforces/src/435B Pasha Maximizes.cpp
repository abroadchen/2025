//
// Created by Psy.C on 2026/2/6.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;


int main() {
    fast;
    char s[N]; string str; cin >> str; strcpy(s + 1, str.data());
    int x; cin >> x;//操作次数
    const int n = static_cast<int>(strlen(s + 1));
    for (int i = 1, cnt; i <= n; ++i) {
        int t = i;//记录当前位置
        cnt = 0;//记录移动的距离
        for (int j = i + 1; j <= n; ++j) {
            //寻找比当前位置字符更大的字符 移动距离不超过剩余操作次数
            if (s[j] > s[t] && x >= j - i) {
                t = j;
                cnt = j - i;
            }
        }
        if (s[t] == s[i]) continue;//跳过（不需要移动）
        //相邻交换，冒泡式地向前移动字符
        for (int k = t; k > i; --k) swap(s[k], s[k-1]);
        x -= cnt;//减少已使用的操作次数
    }
    cout << s + 1 << '\n';
    return 0;
}