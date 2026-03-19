//
// Created by Psy.C on 2026/3/19.
//
/**
字符串长度n、替换次数m、原始字符串str
v.push_back('a' + i)：将字符'a'到'z'依次添加到向量v中
最终v[0]='a', v[1]='b', ..., v[25]='z'，建立初始的字母到自身的映射

char a, b;：定义两个字符变量，用于存储每次替换的两个字符
外层循环：执行m次替换操作
cin >> a >> b;：读取本次操作要交换的两个字符
内层循环：遍历向量v的所有元素（26个字母）
if (v[j] == a) v[j] = b;：如果v[j]原本映射到字符a，则改为映射到b
else if (v[j] == b) v[j] = a;：如果v[j]原本映射到字符b，则改为映射到a
效果：实现a和b在映射表中的互换

char &i：引用方式访问，可以直接修改原字符
i - 'a'：将字符转换为索引（'a'→0, 'b'→1, ..., 'z'→25）
v[i - 'a']：获取该字符在映射表中对应的替换字符
i = v[i - 'a']：将原字符替换为其映射后的字符
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 26;
int n, m;
string str;
vector<char> v;
int main() {
    fast;
    cin >> n >> m >> str;
    for (int i = 0; i < N; ++i)
        v.push_back('a' + i);
    char a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        for (int j = 0; j < N; ++j) {
            if (v[j] == a) v[j] = b;
            else if (v[j] == b) v[j] = a;
        }
    }
    for (char &i : str) i = v[i - 'a'];
    cout << str << '\n';
    return 0;
}