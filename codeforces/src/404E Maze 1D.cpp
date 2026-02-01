//
// Created by Psy.C on 2026/2/1.
//
///时间复杂度：O(n log n)，其中n为字符串长度
///空间复杂度：O(n)
/*
* // 寻找第一个满足条件的位置（最小化问题）
if (condition(mid)) {
    r = mid;  // 条件满足，答案在左半部分包括mid
} else {
    l = mid + 1;  // 条件不满足，答案在右半部分
}
 *
// 寻找最后一个满足条件的位置（最大化问题）
if (ok(mid)) {
    l = mid;      // 条件满足，答案在右半部分包括mid
} else {
    r = mid - 1;  // 条件不满足，答案在左半部分不包括mid
}
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;

char str[N];
bool ok(const int pos) {//是否能到达指定位置
    int now = 0, l = 0; bool flag = true;
    for (int i = 0; str[i]; ++i) {
        if (str[i] == 'R') {
            flag = false;
            //如果下一个位置是目标pos则不移动，否则正常右移
            if (now + 1 == pos) {} else now++;
        } else now--;//向左移动
        if (now < l) { l = now; flag = true; }//更新最小值并设置标志位
    }
    return flag;
}

int main() {
    fast;
    cin >> str;
    const int len = static_cast<int>(strlen(str));
    //字符串末尾是'R'，翻转整个字符串的指令
    if (str[len-1] == 'R') for (int i = 0; str[i]; ++i) {
        if (str[i] == 'R') str[i] = 'L';
        else str[i] = 'R';
    }
    if (ok(len+5)) { cout << "1\n"; return 0; }
    int l = 0, r = len+5;
    while (l < r) {//右端点优先的二分搜索
        if (const int mid = (l + r + 1) >> 1; ok(mid)) l = mid;
        else r = mid - 1;
    }
    cout << l << '\n';
    return 0;
}