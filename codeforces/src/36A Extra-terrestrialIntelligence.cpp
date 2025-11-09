//
// Created by Psy.C on 2025/9/22.
//

#include <cstdio>
using namespace std;

int main() {

    FILE* f = fopen("input.txt", "r");
    int n(0); fscanf(f, "%d\n", &n);

    int lst(-1), dis(-1);// lst:上一个'1'的位置，dis:相邻'1'之间的距离
    bool ok(1);

    for (int i = 0; i < n; ++i) {
        char tmp('0'); fscanf(f, "%c", &tmp);// 读取当前位置的字符
        if (tmp == '1') {
            if (lst < 0) lst = i;// 如果是第一个'1'，记录位置
            else if (dis < 0) {// 如果是第二个'1'，计算距离
                dis = i - lst;
                lst = i;// 更新上一个'1'的位置
            } else if (i - lst == dis) lst = i;// 如果距离相等，更新位置
            else if (i - lst != dis) {// 如果距离不等
                ok = 0;// 标记为不满足条件
                break;
            }
            printf("%d %d %d\n", i, lst, dis);
        }
    }
    fclose(f);

    FILE* f2 = fopen("output.txt", "w");
    if (ok) fprintf(f2, "YES\n");
    else fprintf(f2, "NO\n");
    fclose(f2);

    return 0;
}