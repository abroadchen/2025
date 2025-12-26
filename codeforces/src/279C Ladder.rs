/**
创建一个可变的字符串变量 input，用于存储用户输入
从标准输入读取一行到 input 变量中
unwrap() 解包结果，如果读取失败则程序崩溃
input.trim() 去除字符串首尾的空白字符
.split_whitespace() 按空白字符分割字符串
.collect() 将分割结果收集为字符串切片向量
将第一个部分解析为 usize 类型（数组长度）
将第二个部分解析为 usize 类型（查询次数）
parse() 将字符串转换为指定类型

c: 当前连续递减/递增序列的长度
inc[0] = 1: 第一个元素的递减序列长度为1
dec[n-1] = 1: 最后一个元素的递增序列长度为1

从索引1开始遍历数组
如果 a[i] <= a[i-1]，说明当前元素不大于前一个元素，递减序列延续
否则重置计数器 c = 1
inc[i] 存储以位置 i 结尾的递减序列长度

重置计数器
for i in (0..n-1).rev() 从 n-2 到 0 反向遍历
如果 a[i] <= a[i+1]，说明当前元素不大于后一个元素，递增序列延续
dec[i] 存储从位置 i 开始的递增序列长度

inc[y]：从位置 y 向左的递减序列长度
dec[x]：从位置 x 向右的递增序列长度
如果 inc[y] + dec[x] >= y - x + 2，说明区间 [x, y] 可以被分割为一个递减部分和一个递增部分
*/
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<&str> = input.trim().split_whitespace().collect();
    let n: usize = parts[0].parse().unwrap();
    let m: usize = parts[1].parse().unwrap();

    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let a: Vec<i64> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let mut inc = vec![0; n];
    let mut dec = vec![0; n];
    let mut c = 1; inc[0] = 1; dec[n - 1] = 1;
    for i in 1..n {
        if a[i] <= a[i - 1] { c += 1; } else { c = 1; }
        inc[i] = c;
    }
    c = 1;
    for i in (0..n - 1).rev() {
        if a[i] <= a[i + 1] { c += 1; } else { c = 1; }
        dec[i] = c;
    }
    for _ in 0..m {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<&str> = input.trim().split_whitespace().collect();
        let x: usize = parts[0].parse().unwrap();
        let y: usize = parts[1].parse().unwrap();
        let x = x - 1;//转换为0索引
        let y = y - 1;
        if inc[y] + dec[x] >= y - x + 2 { println!("Yes"); } else { println!("No"); }
    }
}