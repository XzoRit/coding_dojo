fn to_string(a: &str) -> String {
    a.to_string()
}

fn split_with_default_separator(nums: String) -> Vec<String> {
    let with_default_separator = |a| {
        a == ',' || a == '\n'
    };
    nums.split(with_default_separator).map(to_string).collect()
}

fn split_with_separator_spec(nums: String) -> Vec<String> {
    nums.find('\n')
        .map(|a| nums.split_at(a + 1))
        .map(|a| (a.0.get(2..a.0.len() - 1), a.1))
        .map(|a| a.1.split_terminator(a.0.unwrap()))
        .map(|a| a.map(to_string))
        .map(|a| a.collect()).unwrap()
}

fn split_by_separator(nums: String) -> Vec<String> {
    if nums.starts_with("//") {
        split_with_separator_spec(nums)
    }
    else {
        split_with_default_separator(nums)
    }
}

pub fn add(nums: String) -> Result<i32, String> {
    if nums.is_empty() {
        return Ok(0);
    }
    match split_by_separator(nums).iter()
        .map(|a| a.parse::<i32>().unwrap())
        .partition::<Vec<_>, _>(|a| a.is_positive()) {
            (pos, neg) if neg.is_empty() => Ok(pos.iter().sum()),
            (_, neg) => Err(neg
                            .iter()
                            .fold(String::from("negatives not allowed:"), |acc, a| acc + " " + &a.to_string()))
        }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn add_with_empty_string_returns_0() {
        assert_eq!(Ok(0), add(String::from("")));
    }

    #[test]
    fn add_with_one_number_returns_that_number() {
        assert_eq!(Ok(1), add(String::from("1")));
        assert_eq!(Ok(12), add(String::from("12")));
        assert_eq!(Ok(123), add(String::from("123")));
    }

    #[test]
    fn add_with_two_numbers_returns_the_sum() {
        assert_eq!(Ok(3), add(String::from("1,2")));
        assert_eq!(Ok(13), add(String::from("1,12")));
    }

    #[test]
    fn add_with_many_numbers_returns_the_sum() {
        assert_eq!(Ok(6), add(String::from("1,2,3")));
        assert_eq!(Ok(356), add(String::from("1,22,333")));
    }

    #[test]
    fn new_line_is_a_valid_separator_too() {
        assert_eq!(Ok(356), add(String::from("1,22\n333")));
    }

    #[test]
    fn add_with_negative_numbers_returns_an_error() {
        assert_eq!(Err(String::from("negatives not allowed: -22 -444")), add(String::from("1,-22,333,-444")));
    }

    #[test]
    fn separator_can_be_specified() {
        assert_eq!(Ok(356), add(String::from("//**\n1**22**333")));
    }
}
