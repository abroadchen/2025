use std::env;
use std::fs::File;
use std::io::Write;
use std::path::Path;

/**
@author: June
@since: 2025/7/26
@desc:
*/
fn main() {
    let out_dir = env::var("OUT_DIR").unwrap();
    let dest_path = Path::new(&out_dir).join("scripts.rs");
    let mut f = File::create(&dest_path).unwrap();

    f.write_all(b"
        fn some_func() -> &'static str {
            \"some func\"
        }
    ").unwrap();
}