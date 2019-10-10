use multiset::HashMultiSet;
use std::iter::FromIterator;

fn is_odd(n: usize) -> bool {
    n % 2 == 1
}

pub fn palindr_perm(string: &str) -> bool {
    let mset: HashMultiSet<char> = FromIterator::from_iter(string.chars());

    let mut odd_chars = 0;
    for c in mset.distinct_elements() {
        if is_odd(mset.count_of(c)) {
            odd_chars += 1;
        }
    }

    if (odd_chars == 1 && is_odd(mset.len())) || (odd_chars == 0) {
        true
    } else {
        false
    }
}
