// Copyright [2020] <Alyona Dorodnyaya>

#include <cstddef>
#include <set>

// void - так как храним только указатели
void const** reverse(size_t const length) {
  void const** arr = new void const*[length];
  arr[0] = &arr[length - 16];
  for (size_t i = 32; i < length; i += 16) {
    arr[i] = &arr[i - 16];  // ссылка на последующий
  }
  arr[16] = nullptr;
  return arr;
}