// Copyright 2020 ezuryy <daria.kidinova@gmail.com>

#ifndef TEMPLATE_FUNCTIONS_H
#define TEMPLATE_FUNCTIONS_H

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

using std::cout;
using std::string;
using std::vector;

void MakeRandArray(int64_t *&arr, const size_t &size);

void Experiment(const float &BufferSize,
                std::chrono::duration<double> &sortingTime,
                const string &TravelVariant);

void PrintResultsOfExperiment(const size_t &counter, const float &BufferSize,
                              const std::chrono::duration<double> &sortingTime,
                              const string &TravelVariant);

void WriteOneExperiment(const size_t &counter, const float &BufferSize,
                        const std::chrono::duration<double> &sortingTime,
                        vector<YAML::Node> &experiments);

void WriteToFileAllExperiments(const string &TravelVariant, std::ofstream &out,
                               vector<YAML::Node> &experiments);

#endif  // TEMPLATE_FUNCTIONS_H
