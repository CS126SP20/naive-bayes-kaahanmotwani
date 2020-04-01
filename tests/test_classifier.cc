// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>

using bayes::ReadModelData;
using bayes::ReadPriorsFromModel;
using bayes::AddLabelsToAVector;
using bayes::ClassifyAnImage;

TEST_CASE("Sanity Check", "[addition]") {
  ifstream sample_images_stream("tests/data/sampleimages");
  ifstream sample_labels_stream("tests/data/samplelabels");
  double accuracy =
      bayes::ValidateClassificationAndReturnAccuracy(sample_images_stream,
                                                     sample_labels_stream);

  REQUIRE(accuracy > .50);
}

TEST_CASE("Sanity Check2", "[addition]") {
  ifstream sample_model_stream("tests/data/test_model_data");
  istream& input_stream = sample_model_stream;

  vector< vector< vector<double>>> image_probabilities =
      ReadModelData(input_stream, 2, 1);

  vector< vector< vector<double>>> expected_probabilities(2,
      vector<vector<double>>(2, vector<double>(1, 0)));

  input_stream >> expected_probabilities[0][0][0];
  input_stream >> expected_probabilities[1][0][0];
  input_stream >> expected_probabilities[0][1][0];
  input_stream >> expected_probabilities[1][1][0];


  REQUIRE(image_probabilities == expected_probabilities);
}

TEST_CASE("Sanity Check3", "[addition]") {
  ifstream sample_model_stream("tests/data/test_prior_data");
  istream& input_stream = sample_model_stream;

  vector<double> expected_probabilities(10, 0.1);
  vector<double> image_probabilities = ReadPriorsFromModel(input_stream);

  REQUIRE(image_probabilities == expected_probabilities);
}

TEST_CASE("Sanity Check4", "[addition]") {
  ifstream labels_stream("tests/data/samplelabels");

  vector<double> test_labels;
  test_labels.push_back(5);
  test_labels.push_back(0);
  test_labels.push_back(4);

  vector<double> expected_labels_stream = AddLabelsToAVector(labels_stream);

  REQUIRE(test_labels == expected_labels_stream);
}

TEST_CASE("Sanity Check5", "[addition]") {

  vector<double> test_posterior_probabilities(10, 0.1);
  test_posterior_probabilities[0] = 1;
  vector<double> test_labels(10);
  for (size_t i = 0; i < test_labels.size(); i++) {
    test_labels.push_back(i);
  }

  REQUIRE(ClassifyAnImage(test_posterior_probabilities, test_labels) == 0);
}
