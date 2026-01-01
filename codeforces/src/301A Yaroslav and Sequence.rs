/**
现在一次性读取包含所有数组元素的一行
使用 .split_whitespace() 和 .map().collect() 解析多个整数
这样可以正确处理像 "50 50 50" 这样的输入
*/
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: i32 = input.trim().parse().unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let a: Vec<i32> = input.trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
    let mut ans = 0i32;
    if n % 2 == 1 {
        for i in 0..(2 * n - 1) as usize {
            ans += a[i].abs();//累加所有元素的绝对值到 ans
        }
    } else {
        let mut cnt = 0i32;//负数计数器
        let mut mn = 1_000_000_000i32;
        for i in 0..(2 * n - 1) as usize {
            if a[i] < 0 { cnt += 1; }
            mn = mn.min(a[i].abs());//更新最小绝对值
            ans += a[i].abs();
        }
        if cnt % 2 == 1 { ans -= 2 * mn; }//保持最终结果为正数
    }
    println!("{}", ans);
}