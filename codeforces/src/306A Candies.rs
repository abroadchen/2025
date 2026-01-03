use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let c = parts[0];//糖的个数
    let f = parts[1];//朋友的个数
    let n = c / f;//先给每个人平均n个糖
    let mut a = vec![n; f as usize];
    let mut r = c % f;//给过之后还剩多少个糖
    let mut i = f - 1;//从最后一个朋友开始
    while r > 0 {
        a[i as usize] += 1;//从后向前，每人多分一个糖
        r -= 1;//剩余糖果数量减1
        i -= 1;//移动到前一个朋友
    }
    for i in 0..f as usize {
        if i == f as usize - 1 { print!("{}", a[i]); } else {
            print!("{} ", a[i]);
        }
    }
    println!();
}