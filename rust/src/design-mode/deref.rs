/**
@author: June
@since: 2025/7/28
@desc:

1、先匹配T = U;
2、接下来匹配&T = U;
3、最后匹配&**T = U，此处可以多次解引用，即可以&**->&***->&****等;
4、再匹配不上，报错误
*/

trait OrTrait {
    fn foo(self);
}

struct Check;

impl OrTrait for Check {
    fn foo(self) {
        println!("A");
    }
}

impl OrTrait for &Check {
    fn foo(self) {
        println!("B");
    }
}

impl OrTrait for &&&Check {
    fn foo(self) {
        println!("D");
    }
}

fn main() {
    let a = Check;
    let b = &Check;
    let c = &&Check;
    let d = &&&Check;
    let e = &&&&Check;
    let f = &&&&&&&&Check;
    a.foo();
    b.foo();
    c.foo();
    d.foo();
    e.foo();
    f.foo();
}


/*

按照上面的规则，我们在第7~23行分别为Check，&Check，&&&Check实现了OrTrait，那么当调用该trait中的foo方法时，匹配规则中的U可以是Check、&Check、&&&Check三个类型。下面我们再回到main函数中，对各个类型调用foo函数的输出结果进行分析。


第32行，a.foo()可以写成(Check).foo()，T=Check。按照规则1匹配，可以匹配U=Check的情况，所以输出结果为A。


第33行，b.foo()可以写成(&Check).foo()，T=&Check。按照规则1匹配，可以匹配U=&Check的情况，所以输出结果为B。


第34行，c.foo()可以写成(&&Check).foo()，T=&&Check。按照规则1匹配，不匹配Check、&Check、&&&Check中的任何一种，规则1匹配失败；接下来按照规则2匹配，加上&为&(&&Check)->&&&Check匹配成功，输出D。


第35行，d.foo()可以写成(&&&Check).foo()，T=&&&Check。按照规则1匹配，可以匹配U=&&&Check的情况，所以输出结果为D。


第36行，e.foo()可以写成(&&&&Check).foo()，T=&&&&Check。按照规则1匹配，不匹配Check、&Check、&&&Check中的任何一种，规则1匹配失败；按照规则2匹配，加上&为&(&&&&Check)->&&&&&Check，匹配不成功；按照规则3解引用，可以&**(&&&&)Check->&&&Check 匹配成功，所以输出D。


第37行，f.foo()可以写成(&&&&&&&&Check).foo()，T=&&&&&&&&Check。按照规则1匹配，不匹配Check、&Check、&&&Check中的任何一种，规则1匹配失败；按照规则2匹配，加上&为&(&&&&&&&&Check)->&&&&&&&&&Check，匹配不成功；按照规则3解引用，可以&******(&&&&&&&&)Check->&&&Check 匹配成功，所以输出D。












*/










