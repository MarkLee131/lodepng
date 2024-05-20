#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "lodepng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRandomLengthString();
  const auto width = stream.ConsumeIntegral<unsigned int>();
  const auto height = stream.ConsumeIntegral<unsigned int>();
  std::vector<unsigned char> image_data = stream.ConsumeRemainingBytes<unsigned char>();
  if (image_data.size() != width * height * 4) {
    return 0;
  }
  lodepng_encode32_file(filename.c_str(), image_data.data(), width, height);
  return 0;
}
