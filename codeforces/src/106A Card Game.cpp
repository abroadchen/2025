//
// Created by Psy.C on 2025/11/13.
//
/*
*创建牌面值数组：6,7,8,9,T,J,Q,K,A（按从小到大排列）
遍历数组查找字符ch的位置
返回位置索引+1（1表示6，2表示7，...，9表示A）
 *
*读入王牌花色字符ch
读入两张牌s1和s2（每张牌由面值和花色组成，如"9H"表示红桃9）
*如果两张牌花色不同，且两张牌都不是王牌花色，则输出"NO"
这意味着第一张牌无法击败第二张牌
*如果两张牌花色不同：
如果第一张牌是王牌花色，则输出"YES"（王牌可以击败任何非王牌）
否则输出"NO"
*如果两张牌花色相同：
获取两张牌面值的位置p1和p2
如果第一张牌面值大于第二张牌面值，则输出"YES"
否则输出"NO"
 */
#include <iostream>
#include <vector>
using namespace std;

int pos(char ch) {
    vector<char> arr = {
        '6', '7', '8', '9',
        'T', 'J', 'Q', 'K', 'A'
    };
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == ch) return i + 1;
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    char ch; cin>>ch;
    string s1, s2; cin >> s1 >> s2;
    if (s1[1] != s2[1] && s1[1] != ch && s2[1] != ch) cout << "NO";
    else if (s1[1] != s2[1]) {
        if (s1[1] == ch) cout << "YES";
        else cout << "NO";
    } else if (s1[1] == s2[1]) {
        int p1 = pos(s1[0]), p2 = pos(s2[0]);
        if (p1 > p2) cout << "YES";
        else cout << "NO";
    }
    return 0;
}