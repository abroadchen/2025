/**
@author: June
@since: 2025/7/28
@desc: 为了绕过编译器的借用检查，一种设计是将一个大的结构体设计为几个小结构体的组合
*/
struct A {
    a: u32,
    b: u32,
    c: u32,
}

fn foo(a: &mut A) -> &u32 {
    &a.b
}
fn bar(a: &mut A) -> u32 {
    a.a + a.b
}
fn baz(a: &mut A) {
    let x = foo(a);
    // let y = bar(a);  // 此行会报错
    println!("x: {:?}", x);
}

//以使用组合结构体来绕过编译器
struct A1 {
    e: B,
    f: C,
}
struct B {
    b: u32,
}
struct C {
    a: u32,
    b: u32,
}

fn foo2(b: &mut B) -> &u32 {
    &b.b
}
fn bar2(c: &mut C) -> u32 {
    c.a + c.b
}

fn baz2(a: &mut A1) {
    let x = foo2(&mut a.e);
    let y = bar2(&mut a.f); //现在可以编译过了
    println!("x: {}", x);
    println!("y: {}", y);
}