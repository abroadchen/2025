//
// Created by Psy.C on 2025/11/25.
//
/*
*v: 路径栈，存储从根目录到当前目录的路径组件
s: 存储命令名称（"pwd"或"cd"）
t: 存储命令参数（目标路径）
str: 临时字符串，用于解析路径组件
 *
*以'/'开始（根目录）
依次输出路径栈中的每个目录
每个目录后跟'/'
 *
 *v.push_back(str) 表示进入一个子目录
 *
 *路径字符串的最后一部分后面没有'/'
 *处理循环结束后str中剩余的内容
 *
*时间复杂度：O(n×m)，其中n是命令数，m是路径长度
空间复杂度：O(d)，其中d是目录深度
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fast;
    int n; cin >> n;
    string s, t, str;
    vector<string> v;
    while (n) {
        cin >> s;
        if (s == "pwd") {// 显示当前路径
            cout << '/';
            for (const auto & i : v) cout << i << '/';
            cout << '\n';
        } else {// 解析并切换路径
            cin >> t;
            if (t[0] == '/') v.clear();//绝对路径：清空当前路径
            for (int i = 0; i < t.size(); ++i) {
                if (t[i] == '.' && t[i + 1] == '.') {
                    i++;//跳过第二个 '.' 字符
                    if (!v.empty()) v.pop_back();//返回上级目录
                } else if (t[i] == '/') {
                    if (!str.empty()) v.push_back(str);//"/" 分隔符
                    str.clear();
                } else str.push_back(t[i]);//普通字符
            }
            if (!str.empty()) { v.push_back(str); str.clear(); }
        }
        n--;
    }
    return 0;
}