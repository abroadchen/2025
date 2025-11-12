//
// Created by Psy.C on 2025/11/12.
//
/*
使用/操作符按逗号,分割字符串，得到字符串数组

(int)a[i]：将当前字符串转换为整数
(int)a[i-1]：将前一个字符串转换为整数
对于每个元素，检查当前数字是否能被前一个数字整除

*/

int main() {
    int n = (int)Stdio.stdin->gets();
    array(string) a = Stdio.stdin->gets() / ",";//从标准输入读取第二行字符串
    bool f = 1;
    for (int i = 1; i < n; ++i) {
        if (((int)a[i] % (int)a[i - 1]) > 0) f = 0;
    }
    write(f ? "FRIENDS" : "NOT FRIENDS");
    return 0;
}