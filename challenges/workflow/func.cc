#include <stddef.h>
#include <stdint.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <vector>

uint8_t func(const uint8_t* data, size_t size) {
  uint8_t tmp_data[8];
  size_t n = 0;
  if (size > 3 && data[3] == 'b') {
    return data[-100];
  }
  if (size == 10 && data[10] == 'a') {
    return 'a';
  }
  if (8 == size && 'f' == data[0] && 'u' == data[1] && 'z' == data[2]) {
    for (n = 0; n <= size; n++) {
      tmp_data[n] = data[n];
    }
  }
  return 0;
}
int main()
{
#ifdef __AFL_HAVE_MANUAL_CONTROL
  __AFL_INIT();
#endif

  // read input from stdin
  std::vector<uint8_t> data(4096);
  size_t size = read(STDIN_FILENO, data.data(), data.size());
  if (size == -1)
  {
    printf("Failed to read from stdin\n");
    return -1;
  }
  data.resize(size);
  func(data.data(), data.size());

  return 0;
}

