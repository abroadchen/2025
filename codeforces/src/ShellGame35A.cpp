//
// Created by Psy.C on 2025/9/22.
//

#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

int main() {

    FILE* f = fopen("input.txt", "r");
    int ball(0); fscanf(f, "%d\n", &ball);// 读取第一行的整数值，存储在ball变量中

    const int N = 3;

    for (int i = 0; i < N; ++i) {
        int first(0), second(0); fscanf(f, "%d %d\n", &first, &second);// 读取每行的两个整数
        if (first == ball) ball = second;// 如果first等于ball的值，则将ball更新为second
        else if (second == ball) ball = first;
    }
    fclose(f);

    FILE* o = fopen("output.txt", "w");
    fprintf(o, "%d\n", ball);
    fclose(o);
    return 0;
}