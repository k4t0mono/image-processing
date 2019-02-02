use crate::pixel::Pixel;


#[allow(dead_code)]
pub struct Image {
	data: Vec<Pixel>,
	width: usize,
	height: usize,
}

impl Image {

	pub fn open<'a>(path: &'a str) -> Image {
		let decoder = png::Decoder::new(
			std::fs::File::open(path).unwrap()
		);

		let (info, mut reader) = decoder.read_info().unwrap();
		info!("{}", format!(
			"file info: {}x{} {:?} {:?}",
			info.width, info.height, info.color_type, info.bit_depth
		));

		let mut buf = vec![0; info.buffer_size()];
		reader.next_frame(&mut buf).unwrap();

		Image::new(buf, info)
	}

	pub fn save<'a>(&self, path_: &'a str) {
		use png::HasParameters;

		let path = std::path::Path::new(path_);
		let file = std::fs::File::create(path).unwrap();
		let ref mut bw = std::io::BufWriter::new(file);

		let w = self.width as u32;
		let h = self.height as u32;
		let mut encoder = png::Encoder::new(bw, w, h);
		encoder.set(png::ColorType::RGBA).set(png::BitDepth::Eight);
		let mut writer = encoder.write_header().unwrap();

		let mut data: Vec<u8> = Vec::new();
		for p in self.data.iter() {
			data.append(&mut p.export());
		}
		writer.write_image_data(&data).unwrap();
	}

	pub fn new(src: Vec<u8>, info: png::OutputInfo) -> Image {
		let width = info.width as usize;
		let height = info.height as usize;

		let mut data: Vec<Pixel> = Vec::new();
		for i in 0..(width * height) {
			data.push(Pixel::new(
				src[i*4],src[i*4 + 1], src[i*4 + 2], src[i*4 + 3],
			));
		}

		Image{ data, width, height }
	}

	pub fn get(&self, x: usize, y: usize) -> &Pixel {
		&self.data[x * self.width + y]
	}

}

