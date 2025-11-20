//
// Created by Psy.C on 2025/11/20.
//

#include <iostream>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n; cin>>n;
    int week[7];//一周七天每天能完成的工作量
    for (int i = 0; i < 7; ++i) cin>>week[i];
    int i = 0;//表示星期一（数组索引从0开始）
    while (n > 0) {
        n -= week[i];
        if (n <= 0) break;
        i++;//进入下一天
        i %= 7;//星期循环
    }
    cout << i + 1 << '\n';//数组索引从0开始，实际星期数需要加1
    return 0;
}