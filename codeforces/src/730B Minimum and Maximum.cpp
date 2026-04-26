//
// Created by Psy.C on 2026/4/25.
//
/**
x：临时变量，用于存储最小值的索引
y：临时变量，用于存储最大值的索引
字符串s：用于存储比较结果（'>'、'<' 或 '='）
队列，存储整数对，用于存放比较结果

读取当前数组长度n
从索引1开始，以步长2遍历数组（每次处理两个相邻元素）
输出查询语句，询问第i个和第i+1个元素的大小关系
读取比较结果
如果第i个元素大于或等于第i+1个元素，则将对(i, i+1)加入队列
否则将对(i+1, i)加入队列（较大元素放在前面，较小元素放在后面）
如果数组长度是奇数，将最后一个元素与自己配对加入队列
初始化x为第一个配对中的第一个元素（较小值的索引）
初始化y为第一个配对中的第二个元素（较大值的索引）
弹出队列首元素
当队列不为空时，循环执行：
查询当前最小值索引x与新配对的第一个元素的大小关系
如果当前最小值小于新元素，则更新x为新元素的索引
查询当前最大值索引y与新配对的第二个元素的大小关系
如果当前最大值小于新元素，则更新y为新元素的索引
弹出队列前端元素
输出结果：y是最大值的索引，x是最小值的索引
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

int t, n, x, y;
string s;
queue<ii> q;
int main() {
    fast;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i < n; i += 2) {
            cout << "? " << i << ' ' << i + 1 << endl;
            cin >> s;
            if (s[0] == '>' || s[0] == '=') q.emplace(i, i+1);
            else q.emplace(i+1, i);
        }
        if (n%2) q.emplace(n, n);
        x = q.front().first, y = q.front().second; q.pop();
        while (!q.empty()) {
            cout << "? " << x << ' ' << q.front().first << endl;
            cin >> s;
            if (s[0] == '<') x = q.front().first;
            cout << "? " << y << ' ' << q.front().second << endl;
            cin >> s;
            if (s[0] == '>') y = q.front().second;
            q.pop();
        }
        cout <<"! " << y << ' ' << x << endl;
    }
    return 0;
}