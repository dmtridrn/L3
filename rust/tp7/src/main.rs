use std::rc::{Rc, Weak};
use std::cell::RefCell;
use std::fmt::{self, write};

struct Maillon {
    value: i32,
    suivant: Option<Rc<RefCell<Maillon>>>,
    precedent: Option<Weak<RefCell<Maillon>>>,
}

impl Drop for Maillon{
    fn drop(&mut self) {
        println!("ma valeur est {} et je pars", self.value);
    }
}

impl std::fmt::Display for Maillon {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.value)?;
        if let Some(s) = &self.suivant {
            write!(f, " -> ")?;
            write!(f, "{}", s.borrow())?; 
        }

        Ok(())
    }
}

fn main(){

}