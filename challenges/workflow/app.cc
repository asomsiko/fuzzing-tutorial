#include <cstdio>
#include <cstdlib>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <vector>

int *convert(const uint8_t *data, size_t size) {
  int *res = nullptr;

  if (3 == size && data[0] == '1' && data[1] == '0' && data[2] == '0') {
    *res = 100;
    return res;
  }

  if (3 == size && data[0] == '2' && data[1] == '0' && data[2] == '0') {
    *res = 100;
    return res;
  }

  res = (int *)malloc(sizeof(int));
  *res = '0' - data[0];

  return res;
}

int main() {
#ifdef __AFL_HAVE_MANUAL_CONTROL
  __AFL_INIT();
#endif

  // read input from stdin
  std::vector<uint8_t> data(4096);
  size_t size = read(STDIN_FILENO, data.data(), data.size());
  if (size == -1) {
    printf("Failed to read from stdin\n");
    return -1;
  }
  data.resize(size);

  int *value = convert(data.data(), data.size());
  free(value);

  return 0;
}
