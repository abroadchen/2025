/**
@author: June
@since: 2025/7/28
@desc:
*/
// 简单枚举类型应该被转换为整数，并作为代码返回
enum SimpleError {    IOError = 1,    FileCorrupted = 2,}
impl From<SimpleError> for libc::c_int {
    fn from(e: SimpleError) -> libc::c_int {
        (e as i8).into()
    }
}
// 结构化枚举应该被转换为整数代码，并有字符串错误信息作为提示细节
enum SimpleError2 {    IOError(String) ,    FileCorrupted(String),}
impl From<SimpleError2> for libc::c_int {
    fn from(e: SimpleError2) -> libc::c_int {
        match e {
            SimpleError2::IOError(_) => 1,
            SimpleError2::FileCorrupted(_) => 2,
        }
    }
}
#[no_mangle]
pub extern "C" fn return_err2(t: libc::c_int) -> *mut libc::c_char {
    let err = produce_err2(t as u64);
    let err_str = match err {
        SimpleError2::IOError(e) => format!("Io error: {:?}", e),
        SimpleError2::FileCorrupted(e) => format!("FileCorrupted: {:?}", e),
    };
    let c_error = unsafe {
        let malloc: *mut u8 = libc::malloc(err_str.len() + 1) as *mut _;
        if malloc.is_null() {
            return std::ptr::null_mut();
        }
        let src = err_str.as_bytes().as_ptr();
        std::ptr::copy_nonoverlapping(src, malloc, err_str.len());
        std::ptr::write(malloc.add(err_str.len()), 0);
        malloc as *mut libc::c_char
    };
    c_error
}
// 自定义错误类型应该变的透明，用c表示
struct SimpleError3 {    expected: char,    line: u32,    ch: u16,}
#[repr(C)]
pub struct parse_error {
    pub expected: libc::c_char,
    pub line: u32,
    pub ch: u16,
}
impl From<SimpleError3> for parse_error {
    fn from(s: SimpleError3) -> parse_error {
        let SimpleError3 { expected, line, ch} = s;
        parse_error {
            expected: expected as libc::c_char,
            line,
            ch,
        }
    }
}

/*

二、FFI接受字符串处理

1、惯常做法

当FFI接受字符串时，应该遵循：

    使用外部字符串时尽量是借用，而不是直接复制它们；

    尽量减少从C风格字符串转换到Rust字符串时的复杂性，尽量减少unsafe代码量。


2、第一条的原因

因为C语言中使用的字符串和Rust中使用字符串存在不同的行为：

    C语言字符串时无终止的，Rust字符串会存储其长度；

    C语言字符串可以包含任意非零字节，Rust字符串必须是UTF-8；

    C语言字使用unsafe的指针操作字符串，Rust使用安全的方法与字符串进行交互。

4、其它

Rust标准库提供了CString和&CStr，是String和&str相对于C语言的等价表示，使用它们可以降低Rust和C之间字符串操作代码的复杂性，也可以减少unsafe的代码量。


三、FFI传递字符串


1、通常做法

向FFI函数传递字符串应遵循四个原则：

    字符串的生命周期尽可能长；

    转换过程尽量减少unsafe代码；

    如果C代码可以修改字符串，使用Vec而不是CString；

    除非外部API要求，否则字符串的所有权不应该转移给被调用者。




*/



extern "C" {
    fn set_err(message: *const libc::c_char);
}
// 正确示范
fn report_error_to_ffi<S: Into<String>>(err: S) -> Result<(), std::ffi::NulError> {
    let c_err = std::ffi::CString::new(err.into())?;
    unsafe {        set_err(c_err.as_ptr());    }
    Ok(())
}
// 错误示范
fn report_error<S: Into<String>>(err: S) -> Result<(), std::ffi::NulError> {
    unsafe {        // SAFETY: whoops, this contains a dangling pointer!
        set_err(std::ffi::CString::new(err.into())?.as_ptr());        //我的理解等价于如下：
        // let *mut ptr = null;         //{
        //    let c_err = std::ffi::CString::new(err.into())?;
        //    ptr = c_err.as_ptr();
        // }        //set_err(ptr);
    }
    Ok(())
}











