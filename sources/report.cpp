// Copyright 2020 ezuryy <daria.kidinova@gmail.com>

#include "../include/functions.h"

void WriteOneExperiment(const size_t &counter, const float &BufferSize,
                        const std::chrono::duration<double> &sortingTime,
                        vector<YAML::Node> &experiments) {
  YAML::Node node;
  node["experiment"]["number"] = counter;
  std::ostringstream size;
  size << BufferSize << "mb";
  node["experiment"]["input_data"]["buffer_size"] = size.str();
  double timeDouble =
      (sortingTime.count() * 1000000 / (1024 * 128 * BufferSize));
  std::ostringstream time;
  time << std::fixed << std::setprecision(2) << timeDouble << "ns";
  node["experiment"]["results"]["duration"] = time.str();
  experiments.push_back(node);
}

void WriteToFileAllExperiments(const string &TravelVariant, std::ofstream &out,
                               const vector<YAML::Node> &experiments) {
  YAML::Node node;
  node["investigation"]["travel_variant"] = TravelVariant;
  node["investigation"]["experiments"] = experiments;
  out << node << "\n\n";
}
