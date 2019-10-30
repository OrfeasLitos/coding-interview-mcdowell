use std::collections::HashMap;

type PrimaryName<'a> = HashMap<&'a str, &'a str>;
type CountsMap<'a> = HashMap<&'a str, usize>;
type Synonyms<'a> = Vec<(&'a str, &'a str)>;
type Counts<'a> = Vec<(&'a str, usize)>;

fn map_from_synonyms(list: Synonyms) -> PrimaryName {
    let mut res = PrimaryName::new();

    for (left, right) in list {
        let has_left = res.contains_key(left);
        let has_right = res.contains_key(right);

        if has_left && !has_right {
            res.insert(right, res.get(left).unwrap());
        } else if !has_left && has_right {
            res.insert(left, res.get(right).unwrap());
        } else if !has_left && !has_right {
            res.insert(left, left);
            res.insert(right, left);
        }
    }

    res
}

#[test]
fn synonyms_to_map() {
    let mut map = PrimaryName::new();

    let mapped_synonyms = vec![
        ("Jon", "Jon"), ("John", "Jon"),
        ("Chris", "Chris"), ("Johnny", "Jon"),
        ("Christopher", "Chris"), ("Kris", "Chris")
    ];

    for (left, right) in mapped_synonyms {
        map.insert(left, right);
    }

    let synonyms = vec![
        ("Jon", "John"), ("John", "Johnny"),
        ("Chris", "Kris"), ("Chris", "Christopher")
    ];

    assert_eq!(map, map_from_synonyms(synonyms));
}

pub fn baby_names<'a>(synonyms: Synonyms<'a>, counts: Counts<'a>) -> Counts<'a> {
    let primary_names = map_from_synonyms(synonyms);
    let mut freq_map = CountsMap::new();

    for (name, freq) in counts {
        let primary = match primary_names.get(name) {
            Some(primary) => primary,
            None => name
        };

        if freq_map.contains_key(primary) {
            freq_map.insert(primary, freq_map.get(primary).unwrap() + freq);
        } else {
            freq_map.insert(primary, freq);
        }
    }

    freq_map.iter().map(|(&key, &val)| (key, val)).collect()
}

#[test]
fn test_baby_names() {
    let synonyms = vec![
        ("Jon", "John"), ("John", "Johnny"),
        ("Chris", "Kris"), ("Chris", "Christopher")
    ];

    let counts = vec![
        ("John", 15), ("Jon", 12), ("Chris", 13),
        ("Kris", 4), ("Christopher", 19), ("Phoebe", 3)
    ];

    let expected = vec![
        ("Chris", 36), ("Jon", 27), ("Phoebe", 3)
    ];

    let mut res = baby_names(synonyms, counts);
    res.sort_by(
        |(name_a, _), (name_b, _)| {
            name_a.cmp(name_b)
        }
    );
    assert_eq!(expected, res);
}
