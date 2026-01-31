//
// Created by Psy.C on 2026/1/31.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char str[20];
int d[] = {1, 2, 3, 4, 6, 12};//12的所有正因数
vector<int> ans;//存储找到的因数

int main() {
    fast;
    int n; cin >> n;
    while (n--) {
        cin >> str; ans.clear();
        ///遍历数组d中的每个因数i
        ///对于每个因数i，遍历0到12/i-1的所有位置j
        for (int i : d) for (int j = 0; j < 12/i; ++j) {
            bool flag = true;//当前块是否全部为'X'
            //检查大小为i的块中是否全部为'X'
            for (int k = 0; k < i; ++k) if (str[k*12/i+j] != 'X') {
                flag = false;
                break;
            }
            if (flag) { ans.push_back(i); break; }//找到了全是'X'的块
        }
        cout << ans.size();
        for (const int an : ans) cout << ' ' << an << 'x' << 12/an;
        cout << '\n';
    }
    return 0;
}