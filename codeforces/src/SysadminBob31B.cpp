//
// Created by Psy.C on 2025/9/21.
//

#include <ios>
#include <iostream>
#include <cstring>
using namespace std;

const int N = 210;
char word[N];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> word;
    int len = strlen(word);
    bool ok = true, flag = 0;// ok标记是否有效，flag标记是否遇到@
    int tot = 1;// 记录@符号的位置数量
    int ans[N];// 存储需要分割的位置

    ans[0] = -1;
    for (int i = 0; i < len; ++i) {
        if (word[i] == '@') {
            flag = 1;
            if (!i || i == len - 1) {//@不能在字符串开头或结尾
                ok = false;
                break;
            } else {//当前@位置的前一个字符不能是上一个记录的位置
                if (word[i - 1] != '@' && word[i + 1] != '@' && i - 1 != ans[tot-1])
                    ans[tot++] = i + 1;
                else {
                    ok = false;
                    break;
                }
            }
        } else if (i == len - 1 && flag == 0) ok = false;// 如果到末尾都没遇到@，标记为无效
    }

    if (ok) {
        int i = 1;// 分割位置索引
        for (int j = 0; j < len; ++j) {
            cout << word[j];// 输出当前字符
            if (ans[i] == j && i != tot - 1) {// 如果当前位置是记录的分割位置且不是最后一个
                cout << ",";// 输出分隔符
                i++;// 移动到下一个分割位置
            }
        }
    } else
        cout << "No solution" << endl;

    return 0;
}