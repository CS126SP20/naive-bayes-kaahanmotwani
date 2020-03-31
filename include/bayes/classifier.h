// Copyright (c) 2020 Kaahan Motwani. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace bayes {
  const int kNumDigits = 10;
  const int kImageSize = 28;
  void ReadModelData();
}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

