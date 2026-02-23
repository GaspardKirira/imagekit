#include <imagekit/imagekit.hpp>
#include <iostream>

int main()
{
  imagekit::Image img{};
  img.width = 800;
  img.height = 600;
  img.channels = 3;
  img.data.resize(img.width * img.height * img.channels, 255);

  imagekit::ResizeOptions opt{};
  opt.target_width = 400;
  opt.target_height = 300;

  imagekit::Image resized = imagekit::Processor::resize(img, opt);

  std::cout << "Original: "
            << img.width << "x" << img.height << "\n";

  std::cout << "Resized:  "
            << resized.width << "x" << resized.height << "\n";

  return 0;
}
