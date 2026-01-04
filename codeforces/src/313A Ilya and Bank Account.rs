/**
i % 10：获取i的个位数
i - i % 10：将i的个位数变为0
(i - i % 10 + j)：将i的个位数替换为j
*/
use std::io;

fn main() {
    loop {
        let mut input = String::new();
        match io::stdin().read_line(&mut input) {//处理Result类型
            Ok(_) => {//下划线表示不使用返回值
                let a: i32 = match input.trim().parse() {
                    Ok(num) => num,
                    Err(_) => break,
                };
                if a >= 0 { print!("{}", a); } else {
                    let b = a.abs();
                    let j = b % 10;//个位数
                    let i = b / 10;//去掉个位数
                    let x = (i - i % 10 + j);
                    if i <= x {
                        if i != 0 { println!("-{}", i); } else { println!("0"); }
                    } else {
                        if x != 0 { println!("-{}", x); } else { println!("0"); }
                    }
                }
            }
            Err(_) => break,
        }
    }
}