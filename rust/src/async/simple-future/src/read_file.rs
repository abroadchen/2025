use std::{fs, io};
use std::path::Path;

/**
@author: June
@since: 2025/7/26
@desc:
*/

fn visit_dirs(dir: &Path) -> io::Result<()> {
  if dir.is_dir() {
    for entry in fs::read_dir(dir)? {
      let entry = entry?;
      let path = entry.path();
      if path.is_dir() {
        visit_dirs(&path)?;
      } else {
        let c = fs::read_to_string(&path)?;
      }
    }
  }
  Ok(())
}


fn main() {
  let context = fs::read("./pin.rs").unwrap();
  let context = fs::read_to_string("./pin.rs").unwrap();
}