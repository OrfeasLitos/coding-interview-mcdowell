mod lib;

use lib::palindr_perm;

fn main() {
    if !palindr_perm("lol") {
        panic!("lol");
    }

    if palindr_perm("asdf") {
        panic!("asdf");
    }

    if palindr_perm("lolaab") {
        panic!("lolaab");
    }
}
