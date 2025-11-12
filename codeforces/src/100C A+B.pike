//
// Created by Psy.C on 2025/11/12.
//

/*
第一个(int)Stdio.stdin.gets() - 读取第一个数字
第二个(int)Stdio.stdin.gets() - 读取第二个数字
+ - 将两个整数相加
+"" - 将结果转换为字符串（通过与空字符串连接）
*/
void main() {
    write(((int)Stdio.stdin.gets()+
        (int)Stdio.stdin.gets())+"");
}