//
// Created by Psy.C on 2025/10/15.
//
/*
*cnt: 当前处理到的表格编号计数器。
fa[N]: 每个表格的父级表格索引数组。
f: 当前所在的表格层级（当前活跃的表格编号）。
ans[N]: 存储每个表格中 <td> 元素数量的数组。
 *
*初始化两个字符串变量 s（完整输入）和 s1（临时读取）。
循环从标准输入读取单词直到遇到空字符串为止，并将所有读入的单词拼接成一个完整的字符串 s
 *
 *遍历整个字符串 s，注意循环上限减去9是为了防止越界访问子串。
 *
*如果当前位置起始的7个字符是 <table>：
表示发现一个新的表格开始标签。
将表格计数器 cnt 加一。
设置新表的父表为当前表 (fa[cnt] = f)。
更新当前活动表为这个新的表 (f = cnt)。
 *
*如果当前位置起始的8个字符是 </table>：
表示一个表格结束标签。
回退到上一层表格（即回到其父表）。
 *
*如果当前位置起始的4个字符是 <td>：
表示找到一个表格数据单元格。
对应当前所在表格的数据单元格计数加一。
 *
 *循环结束后对所有表格中的 <td> 数量进行排序
 *输出排序后的结果（从第1个有效元素开始输出，跳过索引0）
 *从一段HTML文本中解析嵌套的 <table> 结构，并统计每层表格内的 <td> 标签数目。最终按照从小到大的顺序输出这些数字
 */
#include <algorithm>
#include <ios>
#include <iostream>
#include <string>
using namespace std;

const int N = 5010;
int cnt, fa[N], f, ans[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    string s, s1;
    while (cin >> s1) {
        if (s1 == "") break;
        s += s1;
    }
    for (int i = 0; i < s.size() - 9; ++i) {
        if (s.substr(i, 7) == "<table>") {
            cnt++;
            fa[cnt] = f;
            f = cnt;
        }
        if (s.substr(i, 8) == "</table>") f = fa[f];
        if (s.substr(i, 4) == "<td>") ans[f]++;
    }
    sort(ans, ans + cnt + 1);
    for (int i = 1; i <= cnt; ++i) cout << ans[i] << " ";
    return 0;
}