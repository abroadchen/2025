///
/// lines.next() 返回 Option<std::io::Result<String>>
// 外层 Option：表示是否有下一行（Some(result) 或 None）
// 内层 Result<String, std::io::Error>：表示读取行是否成功
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let n: usize = lines.next()??.parse()?;
    let mut a = vec![0; n + 2];
    let input_line = lines.next()??;
    let val: Vec<i32> = input_line.split_whitespace().map(|s| s.parse()?).collect();
    for i in 1..=n { a[i] = val[i - 1]; }
    let m: i32 = lines.next()??.parse()?;
    for _ in 0..m {
        let line = lines.next()??;
        let parts: Vec<usize> = line.split_whitespace().map(|s| s.parse()?).collect();
        let x = parts[0];
        let y = parts[1] as i32;
        a[x - 1] += y - 1;//左侧位置增加 y-1
        a[x + 1] += a[x] - y;//右侧位置增加 a[x]-y
        a[x] = 0;//当前位置清零
    }
    for i in 1..=n { println!("{}", a[i]); }
}