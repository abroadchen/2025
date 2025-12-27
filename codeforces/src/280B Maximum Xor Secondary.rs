/**
使用引用 & 避免所有权转移

当栈不为空且栈顶元素小于当前元素时
st.is_empty() 检查栈是否为空
st.last().unwrap() 获取栈顶元素（返回 Option，用 unwrap 解包）
*st.last().unwrap() 解引用，获取实际值
st.pop() 弹出栈顶元素
将当前元素压入栈

st[st.len() - 1] 栈顶元素
st[st.len() - 2] 栈顶第二个元素

parse() 将字符串解析为指定类型
*/
fn f(v: &Vec<i32>) -> i32 {
    let mut ans = v[0] ^ v[1];//初始答案
    let mut st: Vec<i32> = Vec::new();//单调栈
    for i in 0..v.len() {
        while !st.is_empty() && *st.last().unwrap() < v[i] { st.pop(); }
        st.push(v[i]);
        if st.len() >= 2 { ans = ans.max(st[st.len() - 1] ^ st[st.len() - 2]) }
    }
    ans
}

fn main() {
    let mut input = String::new();//读取 n
    std::io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut input = String::new();//读取数组
    std::io::stdin().read_line(&mut input).unwrap();
    let mut v: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let mut ans = f(&v);
    v.reverse();
    ans = ans.max(f(&v));
    println!("{}", ans);
}