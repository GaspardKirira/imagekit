#include <imagekit/imagekit.hpp>
#include <iostream>

int main()
{
  imagekit::Image img{};
  img.width = 512;
  img.height = 512;
  img.channels = 3;
  img.data.resize(img.width * img.height * img.channels, 128);

  imagekit::CompressOptions opt{};
  opt.format = imagekit::Format::JPEG;
  opt.quality = 80;

  auto encoded = imagekit::Processor::compress(img, opt);

  std::cout << "Compressed size: "
            << encoded.size() << " bytes\n";

  return 0;
}
