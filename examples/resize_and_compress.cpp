#include <imagekit/imagekit.hpp>
#include <iostream>

int main()
{
  imagekit::Image img{};
  img.width = 1024;
  img.height = 768;
  img.channels = 3;
  img.data.resize(img.width * img.height * img.channels, 200);

  imagekit::ResizeOptions resize_opt{};
  resize_opt.target_width = 640;
  resize_opt.target_height = 480;

  imagekit::Image resized =
      imagekit::Processor::resize(img, resize_opt);

  imagekit::CompressOptions compress_opt{};
  compress_opt.format = imagekit::Format::WEBP;
  compress_opt.quality = 75;

  auto encoded =
      imagekit::Processor::compress(resized, compress_opt);

  std::cout << "Final image: "
            << resized.width << "x"
            << resized.height
            << " | Encoded bytes: "
            << encoded.size() << "\n";

  return 0;
}
