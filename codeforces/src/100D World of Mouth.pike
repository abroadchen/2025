//
// Created by Psy.C on 2025/11/12.
//
/*
从标准输入读取第一行，使用sscanf解析为整数并存储到n中
连续读取两行输入，分别赋值给a和b
m初始化为n1，然后设置为两个长度中的较小值
s用于计算两个字符串从开头开始连续相同的字符数
循环比较两个字符串的每个字符：
如果字符相同，s递增
如果字符不同，立即跳出循环
重新计算m：
n1 + n2是两个字符串长度之和
s + s是两倍的相同前缀长度
结果m表示需要改变的字符数（删除不同的后缀，添加新的后缀）
判断是否能在n次操作内将字符串a转换为字符串b

找到两个字符串的公共前缀
计算需要删除的字符数（a的非公共部分）
计算需要添加的字符数（b的非公共部分）
总操作数 = 删除数 + 添加数
*/
int main() {
    int n;
    sscanf(Stdio.stdin->gets(), "%d", n);
    string a = Stdio.stdin->gets(), b = Stdio.stdin->gets();
    int n1 = strlen(a), n2 = strlen(b), m = n1;
    if (n2 < m) m = n2;
    int s = 0;
    for (int i = 0; i < m; ++i) {
        if (a[i] == b[i]) s++;
        else break;
    }
    m = n1 + n2 - s - s;
    if (m > n) write("No");
    else write("Yes");
    return 0;
}