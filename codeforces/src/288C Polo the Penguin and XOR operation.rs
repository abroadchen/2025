/**
计算位数长度：将 i 转换为浮点数，计算以 2 为底的对数
floor() 向下取整得到最高位位置
+1 得到表示该数字所需的总位数
示例：对于 i=7（二进制：111），log2(7)≈2.8，floor=2，+1=3 位
创建掩码：将 1 左移 lv 位，然后减 1
结果：创建一个有 lv 位全为 1 的数字
示例：如果 lv=3，那么 1 << 3 = 8（1000₂），减 1 = 7（111₂）
异或操作：num（全 1）与 i 异或，翻转 i 的所有位
位反转：这创建了一个"位反转"或互补数字
示例：如果 i=5（101₂）和 num=7（111₂），那么 tmp = 111₂ XOR 101₂ = 010₂ = 2
创建双向映射：在 i 和 tmp 之间存储配对关系
对称存储：如果 i 与 tmp 配对，那么 vis[i] = tmp 且 vis[tmp] = i
*/
use std::io;
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();//非负整数类型
    let mut vis = vec![0; 1024000];
    for i in (1..=n).rev() {
        if vis[i] != 0 { continue }
        let lv = (i as f64).log2().floor() as usize + 1;
        let num = (1<<lv) - 1;
        let t = num ^ i;
        vis[t] = i;
        vis[i] = t;
    }
    let mut sum = 0i64;
    for i in 0..=n { sum += (i ^ vis[i]) as i64; }
    println!("{}", sum);
    for i in 0..=n {
        print!("{} ", vis[i]);
    }
    println!();
}