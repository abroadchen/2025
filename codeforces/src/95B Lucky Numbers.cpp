//
// Created by Psy.C on 2025/11/10.
//
/*
*如果构造字符大于原字符，返回true（构造的数更大）
如果构造字符小于原字符，返回false（构造的数更小）
 *如果所有字符都相等，返回true
 *
*如果长度是奇数：
构造一个包含(l+1)/2个'4'和(l+1)/2个'7'的字符串
 *
 *主循环，逐位构造结果字符串
*如果flag为true（表示可以任意选择）：
优先选择'4'（因为4<7），否则选择'7'
 *如果flag为false（表示需要谨慎选择以确保结果≥输入）
*如果还有'4'可用：
如果'4' > 当前字符，选择'4'并设置flag为true
如果'4' == 当前字符，调用函数f检查后续是否能构造出≥原数的数
 */
#include <iostream>
#include <string>
using namespace std;

string n;

bool f(int c4, int c7, int start) {
    int len = c4 + c7;
    for (int i = 0; i < len; ++i) {
        char c = i < c7 ? '7' : '4';//前c7个是'7'，后面是'4'
        if (c > n[start + i]) return true;
        if (c < n[start + i]) return false;
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n; int l = n.size();
    if (l % 2 == 1) {
        int m = (l + 1) / 2;
        cout << string(m, '4') << string(m, '7') << '\n';
        return 0;
    }
    int c4(l/2), c7(l/2), i;
    string ans; bool flag = false;
    for (i = 0; i < l; ++i) {
        if (flag) {
            if (c4 > 0) { ans += '4'; c4--; }
            else { ans += '7'; c7--; }
        } else {
            if (c4 > 0) {
                if ('4' > n[i]) { ans += '4'; flag = true; c4--; continue; }
                else if ('4' == n[i]) {
                    if (f(c4 - 1, c7, i + 1)) {
                        ans += '4'; c4--; continue;
                    }
                }
            }
            if (c7 > 0) {
                if ('7' > n[i]) { ans += '7'; flag = true; c7--; continue; }
                else if ('7' == n[i]) {
                    if (f(c4, c7 - 1, i + 1)) {
                        ans += '7'; c7--; continue;
                    }
                }
            }
            break;
        }
    }
    if (i == l) cout << ans << '\n';//如果成功构造了完整长度的字符串，输出结果
    else {
        int m = (l + 2) / 2;//构造下一个
        cout << string(m, '4') << string(m, '7') << '\n';
    }
    return 0;
}