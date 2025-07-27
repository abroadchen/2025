/**
@author: June
@since: 2025/7/28
@desc:
*/

use std::io;use std::fs;
fn main() -> Result<(), Box<dyn std::error::Error>> {
    let arg = "-";
    // These must live longer than `readable`, and thus are declared first:
    let (mut stdin_read, mut file_read);
    // We need to ascribe the type to get dynamic dispatch.
    let readable: &mut dyn io::Read = if arg == "-" {
        stdin_read = io::stdin();
        &mut stdin_read
    } else {
        file_read = fs::File::open(arg)?;
        &mut file_read
    };
    // Read from `readable` here.
    Ok(())}