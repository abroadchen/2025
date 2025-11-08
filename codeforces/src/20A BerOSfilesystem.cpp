//
// Created by Psy.C on 2025/9/18.
//

#include <ios>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    string path;
    getline(cin, path);
    string output;
    bool flag(0);

    for (int i = 0; i < path.size(); ++i) {
        if (path[i] != '/' || flag == 0)//前一个字符不是斜杠(flag == 0)
            output += path[i];
        if (path[i] == '/') flag = 1;
        else flag = 0;
    }

    if(flag && output.size() > 1)//如果最后一个字符是斜杠，且输出长度大于1，则删除最后一个斜杠
        output = output.substr(0, output.size() - 1);
    cout << output << endl;
    return 0;
}