// Copyright 2020 ezuryy <daria.kidinova@gmail.com>

#include "../include/functions.h"

void PrintResultsOfExperiment(const size_t &counter, const float &BufferSize,
                              const std::chrono::duration<double> &sortingTime,
                              const string &TravelVariant) {
  if (counter == 1) {
    cout << "\ninvestigation: \n"
         << "\ttravel_variant: \"" << TravelVariant << "\"\n"
         << "\texperiments:\n";
  }
  std::ostringstream size;
  size << BufferSize;
  cout << std::fixed << std::setprecision(2) << "\t- experiment: \n"
       << "\t\tnumber: " << counter << '\n'
       << "\t\tinput_data:\n"
       << "\t\t\tbuffer_size: \"" << size.str() << "mb\"\n"
       << "\t\tresults:\n"
       << "\t\t\tduration: \""
       << sortingTime.count() * 1000000 / (1024 * 128 * BufferSize) << "ns\"\n";
}
