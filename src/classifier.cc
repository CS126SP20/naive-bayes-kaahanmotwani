// Copyright 2020 Kaahan Motwani. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>

namespace bayes {
  void ReadModelData() {
    std::ifstream model_data("data/model_probabilities.csv");
    std::istream& input_stream = model_data;
    std::string line;
    while (std::getline(model_data, line)) {

      double probabilities[kNumDigits];
      
      std::vector<std::string> results;

      // This set of nested for loops correctly calculates
      for (size_t i = 0; i < kNumDigits; i++) {
        probabilities[i] = 0;
        for (size_t x = 0; x < kImageSize; x++) {
          for (size_t y = 0; y < kImageSize; y++) {
            probabilities[i] += log10(count_of_shaded_pixels[x][y][i]);
          }
        }
        probabilities[i] += priors[i];
      }
    }

  }
}  // namespace bayes

