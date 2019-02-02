#[macro_use]
extern crate log;
extern crate simplelog;

mod pixel;
mod image;


fn set_logger(level: usize) {
	use simplelog::*;

	let log_level: LevelFilter = match level {
		0 => LevelFilter::Off,
		1 => LevelFilter::Error,
		2 => LevelFilter::Warn,
		3 => LevelFilter::Info,
		4 => LevelFilter::Debug,
		_ => LevelFilter::Trace,
	};

	TermLogger::init(log_level, Config::default()).unwrap();
}


fn main() {
	set_logger(4);
	info!("image-processing");
	
	let img = image::Image::open("img/t00.png");
	img.save("img/t01.png");
}
