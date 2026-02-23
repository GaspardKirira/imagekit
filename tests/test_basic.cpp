/**
 * @file test_basic.cpp
 * @brief Basic tests for imagekit.
 */

#include <imagekit/imagekit.hpp>

#include <cassert>
#include <cstdint>
#include <vector>

static imagekit::Image makeDummyImage(std::size_t width,
                                      std::size_t height,
                                      std::size_t channels)
{
  imagekit::Image img{};
  img.width = width;
  img.height = height;
  img.channels = channels;

  const std::size_t total = width * height * channels;
  img.data.resize(total);

  // Fill with deterministic bytes
  for (std::size_t i = 0; i < total; ++i)
  {
    img.data[i] = static_cast<std::uint8_t>(i % 251);
  }

  return img;
}

static void test_image_valid()
{
  imagekit::Image img{};
  assert(!img.valid());

  img = makeDummyImage(4, 4, 3);
  assert(img.valid());
  assert(img.width == 4);
  assert(img.height == 4);
  assert(img.channels == 3);
  assert(!img.data.empty());
}

static void test_resize_changes_dimensions()
{
  const imagekit::Image input = makeDummyImage(8, 6, 3);

  imagekit::ResizeOptions opt{};
  opt.target_width = 4;
  opt.target_height = 3;
  opt.preserve_aspect_ratio = true;

  const imagekit::Image out = imagekit::Processor::resize(input, opt);

  assert(out.valid());
  assert(out.width == 4);
  assert(out.height == 3);
  assert(out.channels == input.channels);
  assert(out.data.size() == input.data.size()); // skeleton: keeps same data buffer
}

static void test_compress_returns_buffer()
{
  const imagekit::Image input = makeDummyImage(10, 10, 4);

  imagekit::CompressOptions opt{};
  opt.format = imagekit::Format::JPEG;
  opt.quality = 85;

  const std::vector<std::uint8_t> encoded = imagekit::Processor::compress(input, opt);

  assert(!encoded.empty());
  assert(encoded.size() == input.data.size()); // skeleton: returns raw data
}

static void test_resize_rejects_invalid_inputs()
{
  bool threw = false;

  try
  {
    imagekit::Image invalid{};
    imagekit::ResizeOptions opt{};
    opt.target_width = 10;
    opt.target_height = 10;
    (void)imagekit::Processor::resize(invalid, opt);
  }
  catch (const std::invalid_argument &)
  {
    threw = true;
  }

  assert(threw);
}

static void test_compress_rejects_invalid_quality()
{
  bool threw = false;

  try
  {
    const imagekit::Image input = makeDummyImage(2, 2, 3);

    imagekit::CompressOptions opt{};
    opt.format = imagekit::Format::JPEG;
    opt.quality = 101;

    (void)imagekit::Processor::compress(input, opt);
  }
  catch (const std::invalid_argument &)
  {
    threw = true;
  }

  assert(threw);
}

int main()
{
  test_image_valid();
  test_resize_changes_dimensions();
  test_compress_returns_buffer();
  test_resize_rejects_invalid_inputs();
  test_compress_rejects_invalid_quality();

  return 0;
}
