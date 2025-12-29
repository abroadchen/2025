/**
.split_whitespace()：按空白字符分割字符串，返回迭代器
.map(|x| x.parse().unwrap())：对每个分割的字符串应用转换函数
|x|：闭包参数，代表分割后的每个字符串片段

k > n：如果需要的不同字符数大于字符串长度，不可能实现
(k == 1 && n > 1)：如果只需要1种字符但字符串长度大于1，不可能实现（因为会有重复）

cnt as u8：将字符索引转换为u8类型
+ b'a'：加上字符'a'的ASCII值（97）
as char：将ASCII值转换为字符

*/
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0];
    let mut k = parts[1];
    if k > n || (k == 1 && n > 1) { println!("-1"); return; }
    if k == 1 && n == 1 { println!("a"); return; }//只需要1种字符且字符串长度为1
    let mut res = String::new();
    let mut cnt = 2;//从字符 'c' 开始
    k -= 2;//已经使用了 'a' 和 'b'
    for i in 1..=n {
        if n - i < k {//剩余位置数小于剩余需要的不同字符数
            res.push((cnt as u8 + b'a') as char);
            cnt += 1;//增加下一个字符索引
            k -= 1;//减少剩余需要的不同字符数
        } else {//交替使用'a'和'b'
            if i & 1 == 1 { res.push('a'); } else { res.push('b'); }
        }
    }
    println!("{}", res);
}