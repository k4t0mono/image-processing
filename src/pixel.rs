use std::fmt;


#[derive(Debug, PartialEq, Eq, Clone)]
pub struct Pixel {
	red: u8,
	green: u8,
	blue: u8,
	alpha: u8,
}


impl Pixel {
	pub fn new(red: u8, green: u8, blue: u8, alpha:u8) -> Pixel {
		let p = Pixel{ red, green, blue, alpha };

		p
	}

	pub fn export(&self) -> Vec<u8> {
		vec![self.red, self.green, self.blue, self.alpha]
	}

	#[allow(dead_code)]
	pub fn convert<'a>(data: &'a [u8]) -> Pixel {
		let p = Pixel {
			red: data[0],
			green: data[1],
			blue: data[2],
			alpha: data[3],
		};

		p
	}
}

impl fmt::Display for Pixel {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{:x?}{:x?}{:x?}{:x?}", self.red, self.green, self.blue, self.alpha)
	}
}
