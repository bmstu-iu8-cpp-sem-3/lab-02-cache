// Copyright [2020] <Alyona Dorodnyaya>

#include <cstddef>
#include <set>

// void - так как храним только указатели
void const* * direct(size_t const length) {
  void const* * arr = new void const*[length];
  for (size_t i = 0; i < length - 16; i+=16) {
    arr[i] = &arr[i + 16]; // ссылка на последующий
  }
  arr[length - 16] = nullptr;
  return arr;
}