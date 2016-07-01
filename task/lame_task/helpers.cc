#include "helpers.h"

namespace helpers {
  int GetFileSize(FILE *file) {
    int file_size = 0;
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return file_size;
  }
}  // namespace helpers
