//
// Created by Psy.C on 2025/11/28.
//
/*
*str用于临时存储输入，ans用于存储当前的答案
读取第一个字符串到str
计算字符串长度len
将str的内容复制到ans数组中（注意：ans从索引1开始存储）
 *
*从第2个字符串开始处理（i从2到n）：
读取下一个字符串到str
逐字符比较当前字符串和ans数组：
如果发现不匹配的字符
将len更新为当前位置j（截断长度）
跳出内层循环
 *len--：长度减1（修正索引偏差）
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5;

int main() {
    fast;
    int n; cin >> n;
    char str[N], ans[N];
    cin >> str;
    int len = static_cast<int>(strlen(str));
    for (int i = 1; i <= len; ++i) ans[i] = str[i - 1];
    for (int i = 2; i <= n; ++i) {
        cin >> str;
        for (int j = 1; j <= len; ++j) if (str[j - 1] != ans[j]) {
            len = j;
            break;
        }
    }
    len--;
    if (len == 0) cout << 0 << '\n';
    else cout << len << '\n';
    return 0;
}