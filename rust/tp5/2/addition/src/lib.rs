pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

fn logarithm(x: f64) -> f64 {
    if x < 0.0 {
        panic!("paniq");
    }
    f64::log2(x)
}

fn is_even(n: i32) -> bool {
    n % 2 == 0
}

fn first_even(v: &Vec<i32>) -> Result<i32, String> {
    for &i in v {
        if i%2 == 0{
            return Ok(i)
        }
    }
    Err(String::from("pas de pair la dedans"))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 3);
        assert_eq!(result, 5);
    }

    #[test]
    #[should_panic]
    fn log_panic(){
        let res: f64 = logarithm(-2.0);
    }

    #[test]
    fn test_even(){
        let v: Vec<(i32, bool)> = vec![(1,false), (2,true), (3, false)];
        for (elt, att) in v {
            assert_eq!(is_even(elt), att);
        }
    }

    

}
