//
// Created by Psy.C on 2025/9/21.
//

#include <cstdio>
#include <vector>
using namespace std;

int main() {

    int n(0); scanf("%d", &n);// 读取数组大小n
    int* arr = new int[n];// 动态分配数组内存
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);// 读取数组元素

    bool done(0);
    vector<int> ans;
    // 三重嵌套循环遍历所有可能的三元组(i,j,k)，其中i<j<k
    for (int i = 0; i < n - 2; ++i) {
        if (done) break;
        for (int j = i + 1; j < n - 1; ++j) {
            if (done) break;
            for (int k = j + 1; k < n; ++k) {
                if (arr[k] == arr[i] + arr[j]) {
                    ans.push_back(k);
                    ans.push_back(i);
                    ans.push_back(j);
                    done = 1;
                    break;
                } else if (arr[j] == arr[i] + arr[k]) {
                    ans.push_back(j);
                    ans.push_back(i);
                    ans.push_back(k);
                    done = 1;
                    break;
                } else if (arr[i] == arr[j] + arr[k]) {
                    ans.push_back(i);
                    ans.push_back(j);
                    ans.push_back(k);
                    done = 1;
                    break;
                }
            }
        }
    }

    if (done)
        printf("%d %d %d", 1 + ans[0], 1 + ans[1], 1 + ans[2]);
    else
        puts("-1");


    return 0;
}