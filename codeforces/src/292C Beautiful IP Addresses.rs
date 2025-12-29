///
/// Rust 字符串是 UTF-8 编码，字符长度不固定
// 不能直接用 cur[idx] 访问字符（只能访问字节）
// 必须通过 .chars().nth(idx) 来安全地获取第 idx 个 Unicode 字符
///nth() 方法会跳过前 idx 个元素，返回第 idx+1 个元素（索引从0开始）
// 返回 Option<char> 类型（Some(char) 或 None）
///
/// parse::<i32>() 返回 Result<i32, ParseIntError> 类型
// 当字符串成功解析为整数时，返回 Ok(整数值)
// 当解析失败时，返回 Err(错误信息)
// unwrap_or(999) 的作用
// 如果 Result 是 Ok(值)，则返回该值
// 如果 Result 是 Err(错误)，则返回提供的默认值 999
///
use std::io;
fn ok(s: &str, n: usize) -> bool {
    let mut vis = [false; 10];//标记0-9数字是否出现过
    let mut cnt = 0;//记录不同数字的个数
    for ch in s.chars() {//遍历字符串中的每个字符
        let d = ch as u8 - b'0';//将字符转换为数字（'0'的ASCII码是48，'1'是49，以此类推）
        if d < 10 && !vis[d as usize] {//如果是数字字符且之前没出现过
            vis[d as usize] = true;//标记该数字已出现
            cnt += 1;//计数器加1
        }
    }
    cnt == n//返回不同数字个数是否等于n
}

fn dfs(s: &str, st: usize, res: &mut Vec<String>, ans: &mut Vec<Vec<String>>) {
    if !res.is_empty() {//结果数组不为空
        let pre = res.last().unwrap();//获取最后一个IP段
        //如果以0开头，返回（无效IP段）
        if pre.len() == 2 { if pre.chars().next().unwrap() == '0' { return; } } else if pre.len() == 3 {
            if pre.chars().next().unwrap() > '2' ||//第一位大于'2'
                pre.chars().next().unwrap() == '0' ||//第一位是'0'
                pre.parse::<i32>().unwrap_or(999) > 255 { return; }//转换为整数后大于255
        }
    }
    if res.len() > 4 { return; }//IP段数超过4个
    if st >= s.len() {//已处理完整个字符串
        if res.len() != 4 { return; }
        ans.push(res.clone());//将有效的IP地址加入结果
        return;
    }
    for i in st..=std::cmp::min(st + 2, s.len() - 1) {//尝试长度为1-3的IP段
        res.push(s[st..i + 1].to_string());//添加当前IP段 截取从st到i的子串作为IP段
        dfs(s, i + 1, res, ans);//递归处理剩余部分
        res.pop();//回溯，移除当前IP段
    }
}

fn dfs2(mx: usize, i: usize, cur: String, n: usize, op: &[i32], ans: &mut Vec<Vec<String>>) {
    if ((mx&1) == 1 && i > mx / 2 + 1) || ((mx&1) == 0 && i > mx / 2) {//检查是否达到回文串的中点
        if !ok(&cur, n) { return; }//当前串是否包含n个不同数字
        let mut cur = cur.clone();//复制当前字符串 如果不复制，一个分支的修改会影响其他分支
        let p = if (mx&1) == 1 { cur.len() - 2 } else { cur.len() - 1 };//计算回文起点
        for idx in (0..=p).rev() {//从后往前添加字符形成回文
            if idx < cur.len() { cur.push(cur.chars().nth(idx).unwrap()); }//添加对称位置的字符
        }
        let mut res = Vec::new();
        dfs(&cur, 0, &mut res, ans);//用生成的回文串生成IP地址
        return;
    }
    for j in (0..n).rev() {//遍历可用数字（倒序）
        let ch = (op[j] as u8 + b'0') as char;//将数字转换为字符
        dfs2(mx, i + 1, format!("{}{}", cur, ch), n, op, ans);//递归构建回文串
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut op = vec![0; 10];
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let v: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    for i in 0..n { op[i] = v[i]; }//将输入数字存入op数组
    let mut ans = Vec::new();
    for i in std::cmp::max(4, 2 * n - 1)..=12 {//遍历可能的回文串长度
        dfs2(i, 1, String::new(), n, &op, &mut ans);//生成回文串并找IP地址
    }
    println!("{}", ans.len());
    for ip in &ans {
        for j in 0..3 {//输出前三个IP段
            print!("{}.{}", ip[j], "");
        }
        println!("{}", ip[3]);//输出最后一个IP段
    }
}