// Copyright 2020 ezuryy <daria.kidinova@gmail.com>

#include "../include/functions.h"

int main() {
  cout << "Cache L1 : 0.125mb\n"
          "Cache L2 : 0.5mb\n"
          "Cache L3 : 3mb\n";
  vector<float> BufferSizes{0.0625, 0.125, 0.25, 0.5, 1, 2, 4, 4.5};  // mb
  vector<string> TravelVariants{"direction", "reverse", "random"};

  std::ofstream out{"result.yaml"};
  for (const auto &TravelVariant : TravelVariants) {
    size_t counter = 1;
    vector<YAML::Node> experiments;
    for (const auto &BufferSize : BufferSizes) {
      std::chrono::duration<double> sortingTime{};
      Experiment(BufferSize, sortingTime, TravelVariant);
      PrintResultsOfExperiment(counter, BufferSize, sortingTime, TravelVariant);
      WriteOneExperiment(counter, BufferSize, sortingTime, experiments);
      ++counter;
    }
    WriteToFileAllExperiments(TravelVariant, out, experiments);
  }
  out.close();

  return 0;
}
