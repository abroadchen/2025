//
// Created by Psy.C on 2025/12/2.
//
/*
*s：用于临时存储输入的单词
ans：用于构建最终的结果字符串
 *
*在ans中添加"<"，然后递归调用dfs()处理第一个子项
添加","分隔符，再次递归调用dfs()处理第二个子项
最后添加">"结束标记
这实现了对嵌套结构的递归解析
 *
*cin >> s：检查是否还有多余的输入未被处理
ans.find("<,") != string::npos：检查是否存在"<,"模式（不完整的pair）
ans.find(",>") != string::npos：检查是否存在",>"模式（不完整的pair）
 */
#include <iostream>
#include <string>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s, ans;

void dfs() {
    if (cin >> s) {
        ans += s;
        if (s == "pair") {
            ans += "<"; dfs(); ans += ","; dfs(); ans += ">";
        }
    }
}


int main() {
    fast;
    int n; cin >> n;
    dfs();
    if (cin >> s || ans.find("<,") != string::npos ||
        ans.find(",>") != string::npos) cout << "Error occurred" << '\n';
    else cout << ans.c_str() << '\n';
    return 0;
}