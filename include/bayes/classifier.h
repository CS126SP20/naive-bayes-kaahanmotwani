// Copyright (c) 2020 Kaahan Motwani. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using std::ifstream;
using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace bayes {
  const int kNumDigits = 10;
  const int kImageSize = 28;
  void ReadModelData(ifstream& test_images_stream, ifstream& test_labels_stream,
                     vector< vector< vector<double> > >& pixel_probabilities, vector<double> priors);
  /**
   *
   * @param posterior_probabilities
   * @param test_labels
   */
  void ClassifyAnImage(vector<double>& posterior_probabilities, vector<double>& test_labels);
  vector<double> AddLabelsToAVector(ifstream& test_labels_stream);
  void classify(ifstream& test_images_stream, vector<double> posterior_probabilities,
    vector< vector< vector<double> > >& pixel_probabilities,
    vector<double> priors, vector<double> test_labels);

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

