/**
@author: June
@since: 2025/7/28
@desc:
*/
//Option可以被看做一个包含零或一个元素的容器。因为它实现了trait IntoIterator，所以可以用来迭代。
fn main1() {
    let a = Some("a string");
    let mut s1 = vec!["a", "b", "c"];
    s1.extend(a);
    println!("s1: {:?}", s1);
    println!("+++++++++++++++++++++++++++");
    let b = Some("b string");
    let s1 = vec!["d", "e", "f"];
    for s in s1.iter().chain(b.iter()) {
        println!("item: {}", s);
    }
}


//默认情况下，闭包通过借用捕获其环境。在将变量转移到闭包中时，在单独的作用域中使用变量重绑定
use std::rc::Rc;
fn main() {
    // 好的示范
    let a = Rc::new(1);
    let b = Rc::new(2);
    let c = Rc::new(3);
    let closure = {
        let b = b.clone();
        let c = c.as_ref();
        move || {
            let ret = *a + *b + *c;
            println!("ret = {:?}", ret);
        }
    };
    closure();
    println!("++++++++++++++++++++++++++++++++");
    // 差的示范
    let a = Rc::new(1);
    let b = Rc::new(2);
    let c = Rc::new(3);
    let b_cloned = b.clone();
    let c_borrowed = c.as_ref();
    let closure = move || {
        let ret = *a + *b_cloned + *c_borrowed;
        println!("ret = {:?}", ret);
    };
    closure();
}