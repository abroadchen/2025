use std::io;

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();//存储输入内容
    stdin.read_line(&mut input).unwrap();//unwrap()处理可能的错误
    let mut parts = input.split_whitespace();
    let n: usize = parts.next().unwrap().parse().unwrap();//获取第一个分割部分
    input.clear();//清空input字符串，准备读取下一行
    stdin.read_line(&mut input).unwrap();
    let ch = input.trim_end();
    //统计字符串ch中字符'A'的数量：将字符串转为字符迭代器，过滤出'A'字符，计算数量并转换为i32
    let a = ch.chars().filter(|&c| c == 'A').count() as i32;
    let cnt = ch.chars().filter(|&c| c == 'I').count() as i32;
    let f = ch.chars().filter(|&c| c == 'F').count() as i32;
    if cnt == 1 { println!("1"); }
    else if cnt == 0 { println!("{}", a); }
    else { println!("0"); }
}