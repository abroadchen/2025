//
// Created by Psy.C on 2025/11/6.
//
/*
*num：名字数组的大小，即5个角色
n：输入的位置编号（第几个）
p：倍数因子，初始化为1
 *
*用于确定n在哪个"层级"中

序列规律是：每个名字按以下方式重复出现

第1层：每个名字出现1次 → Sheldon, Leonard, Penny, Rajesh, Howard
第2层：每个名字出现2次 → Sheldon, Sheldon, Leonard, Leonard, ...
第3层：每个名字出现4次 → Sheldon, Sheldon, Sheldon, Sheldon, ...
第k层：每个名字出现2^(k-1)次
循环的作用是跳过完整的层级，找到n所在的层级

p * num表示当前层的总元素个数（p是每个名字的重复次数，num是名字总数）

如果n大于当前层的元素个数，就减去这个数量并进入下一层
 *
 *(n - 1)/p：确定在当前层中是第几个不同的名字
 */
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

vector<string> names = {
    "Sheldon", "Leonard", "Penny",
    "Rajesh", "Howard"
};

int main() {
    int num = names.size();
    int n, p(1); scanf("%d\n", &n);
    while (n > p * num) {
        n -= p * num;
        p *= 2;
    }
    printf("%s\n", names[(n - 1)/p].c_str());
    return 0;
}