# imagekit

Lightweight image resize and compression toolkit for modern C++.

`imagekit` provides a minimal API for resizing and compressing in-memory
images. It is designed for backend services, edge applications and
storage optimization pipelines.

Header-only core abstraction with no heavy dependencies.

## Why imagekit?

Unlike heavy image processing frameworks, this library:

-   Provides a simple in-memory image abstraction
-   Offers explicit resize and compression configuration
-   Uses clear and minimal APIs
-   Is fully header-only
-   Is easy to extend with real encoding backends (libjpeg, libpng, stb,
    etc.)

Perfect for:

-   Web backend preprocessing
-   CDN image optimization
-   Thumbnail generation
-   Edge services
-   Storage compression workflows

## Installation

### Using Vix Registry

``` bash
vix add gaspardkirira/imagekit
vix deps
```

### Manual

Clone the repository:

``` bash
git clone https://github.com/GaspardKirira/imagekit.git
```

Add the `include/` directory to your project.

## Quick Resize Example

``` cpp
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

  auto resized = imagekit::Processor::resize(img, opt);

  std::cout << "Resized to "
            << resized.width << "x"
            << resized.height << "\n";
}
```

## Quick Compression Example

``` cpp
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
            << encoded.size()
            << " bytes\n";
}
```

## Features

-   Header-only
-   C++17 compatible
-   Simple image abstraction
-   Configurable resize behavior
-   Configurable compression quality
-   Format selection (JPEG, PNG, WEBP)
-   Explicit error handling via exceptions
-   Backend-agnostic design

## API Overview

``` cpp
imagekit::Image img;

imagekit::ResizeOptions resize;
resize.target_width = 400;
resize.target_height = 300;

imagekit::CompressOptions compress;
compress.format = imagekit::Format::JPEG;
compress.quality = 85;

auto resized = imagekit::Processor::resize(img, resize);
auto encoded = imagekit::Processor::compress(resized, compress);
```

## Design Philosophy

imagekit focuses on:

-   Simplicity over feature bloat
-   Clear data ownership
-   Explicit configuration
-   Extensibility toward real encoders

The current implementation provides a safe abstraction layer. Real
encoding backends can be integrated transparently.

## Tests

Run:

``` bash
vix build
vix tests
```

## License

MIT License
Copyright (c) Gaspard Kirira

