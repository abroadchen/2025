//
// Created by Psy.C on 2025/12/13.
//
/*
*声明左边界l和右边界r
声明大小为10的整型数组ans并初始化为全0（用于统计0-9数字出现次数）
声明位置变量pos并初始化为1（表示向右移动方向）
从标准输入读取查询的左右边界
 *
*如果当前字符是数字('0'到'9')：
对应数字的计数器加1（s[i]-'0'将字符转换为数字索引）
如果是'0'，从字符串中删除该字符，如果向右移动则位置回退
否则数字减1
按照当前方向移动位置指针
使用continue跳过后续处理
*如果当前字符是'<'，设置移动方向为向左(pos=-1)
如果当前字符是'>'，设置移动方向为向右(pos=1)
 *按照当前方向移动位置指针
*检查边界条件：i在有效范围内且当前字符是方向符号
删除当前位置的字符
如果向右移动则位置指针回退
 *
*输入方式替换：
scanf("%d%d", &n, &q) → cin >> n >> q
gets(t) → getline(cin, t) (需要两次调用以跳过换行符)
scanf("%d %d", &l, &r) → cin >> l >> r
字符串处理：
使用substr()替代C风格的字符指针操作
使用length()替代C风格的字符串结束符检查
输出方式替换：
printf("%d ", ans[i]) → cout << ans[i] << ' '
printf("%d\n", ans[9]) → cout << ans[9] << '\n'
边界检查增强：
添加了i >= 0 && i < s.length()检查以防止数组越界
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;


int main() {
    fast;
    int n, q; cin >> n >> q;
    string t; getline(cin, t); getline(cin, t);//读取第一行剩余内容和第二行
    while(q--) {
        int l, r, ans[10]={}, pos = 1; cin >> l >> r;
        string s = t.substr(l - 1, r - l + 1);
        for (int i = 0; s[i];) {
            if ('0' <= s[i] && s[i] <= '9') {
                ans[s[i] - '0']++;
                if (s[i] == '0') {
                    s.erase(s.begin() + i);
                    if (pos == 1) i--;
                } else s[i]--;
                i += pos;
                continue;
            }
            if (s[i] == '<') pos = -1;
            else if (s[i] == '>') pos = 1;
            i += pos;
            if (s[i] && (s[i] == '>' || s[i] == '<')) {
                s.erase(s.begin() + i - pos);
                if (pos == 1) i--;
            }
        }
        for (int i = 0; i < 9; ++i) cout << ans[i] << ' ';
        cout << ans[9] << '\n';
    }
    return 0;
}