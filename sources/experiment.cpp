// Copyright 2020 ezuryy <daria.kidinova@gmail.com>

#include "../include/functions.h"

void MakeRandArray(int64_t *&arr, const size_t &size) {
  std::srand(std::time(nullptr));
  for (size_t i = 0; i < size; ++i) {
    arr[i] = std::rand();
  }
}

void Experiment(const float &BufferSize,
                std::chrono::duration<double> &sortingTime,
                const string &TravelVariant) {
  auto size = static_cast<size_t>(1024 * 128 * BufferSize);
  auto *arr = new int64_t[size];
  MakeRandArray(arr, size);
  int64_t elem = 0;

  if (TravelVariant == "direction") {
    ///прорев
    for (size_t i = 0; i < size; i += 8) {
      elem = arr[i];
    }
    ///обход
    auto startTime = std::chrono::steady_clock::now();  // начальное время
    for (size_t k = 0; k < 1000; ++k) {
      for (size_t i = 0; i < size; i += 8) {
        elem = arr[i];
      }
    }
    auto endTime = std::chrono::steady_clock::now();  // конечное время
    sortingTime = endTime - startTime;
  } else if (TravelVariant == "reverse") {
    ///прогрев
    for (int i = static_cast<int>(size - 8); i >= 0; i -= 8) {
      elem = arr[i];
    }
    ///обход
    auto startTime = std::chrono::steady_clock::now();  // начальное время
    for (size_t k = 0; k < 1000; ++k) {
      for (int i = static_cast<int>(size - 8); i >= 0; i -= 8) {
        elem = arr[i];
      }
    }
    auto endTime = std::chrono::steady_clock::now();  // конечное время
    sortingTime = endTime - startTime;
  } else if (TravelVariant == "random") {
    vector<size_t> IndexesForRandomTravel;
    for (size_t j = 0; j < size; j += 8) IndexesForRandomTravel.push_back(j);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(IndexesForRandomTravel.begin(), IndexesForRandomTravel.end(),
                 g);
    ///прогрев
    for (int i = static_cast<int>(size - 9); i >= 0; i -= 8) {
      elem = arr[i];
    }
    ///обход
    auto startTime = std::chrono::steady_clock::now();  // начальное время
    for (size_t k = 0; k < 1000; ++k) {
      std::shuffle(IndexesForRandomTravel.begin(), IndexesForRandomTravel.end(),
                   g);
      for (int i = static_cast<int>(size - 9); i >= 0; i -= 8) {
        elem = arr[i];
      }
    }
    auto endTime = std::chrono::steady_clock::now();  // конечное время
    sortingTime = endTime - startTime;
  }
  std::ofstream out;
  out.open("trash.txt");
  out << elem << '\n';
  out.close();
  delete[] arr;
}
