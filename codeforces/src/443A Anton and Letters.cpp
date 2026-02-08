//
// Created by Psy.C on 2026/2/8.
//

#include <iostream>
using namespace std;


int main() {
    int a[500]{};
    char ch = getchar();
    while (ch != '}') {
        a[ch]++;//利用字符的ASCII值作为数组下标
        ch = getchar();
    }
    int cnt = 0;
    //遍历所有小写字母('a'到'z')
    for (int i = 'a'; i <= 'z'; ++i) if (a[i] > 0) ++cnt;//字母i在输入中出现过
    printf("%d\n", cnt);
    return 0;
}