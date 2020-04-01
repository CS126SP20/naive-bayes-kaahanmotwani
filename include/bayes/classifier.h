// Copyright (c) 2020 Kaahan Motwani. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using std::ifstream;
using std::istream;
using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace bayes {
  const int kNumDigits = 10;
  const int kImageSize = 28;

  /**
   * This method calls most of the other helper functions to help with parsing
   * through the model and classification. Then, it calculates and returns the
   * accuracy for the test images.
   *
   * @param test_images_stream The test images
   * @param test_labels_stream The test labels
   * @return the accuracy of the naive bayes algorithm on the test images
   */
  double ValidateClassificationAndReturnAccuracy(ifstream& test_images_stream,
      ifstream& test_labels_stream);

  /**
   * This method reads the data from the model and uses an input stream
   * to add probabilities for each pixel given a class, to a vector
   *
   * @param input_stream the stream with the data from the model
   * @param kImageSize specify the size of the image, for testing purposes
   * @param kNumDigits specify the number of digits, for testing purposes
   * @return the 3D vector of probabilities from the model
   */
  vector< vector< vector<double>>> ReadModelData(istream& input_stream,
      int kImageSize, int kNumDigits);

  /**
   * This method looks at the last line of the model (the priors) and adds
   * them to a vector
   *
   * @param input_stream the stream, which only has one line left
   * @return the vector of priors
   */
  vector<double> ReadPriorsFromModel(istream& input_stream);

  /**
   * This method adds the test labels to a vector so that it is easier
   * to access them
   *
   * @param test_labels_stream the stream of test labels
   * @return the vector of test labels
   */
  vector<double> AddLabelsToAVector(ifstream& test_labels_stream);

  /**
   * This method does a lot of the classification work. It iterates through
   * each image, and adds the log of the probabilities to a vector of
   * posterior probabilities which are used to classify each image.
   *
   * @param test_images_stream the stream of test images
   * @param image_probabilities the 3D vector of probabilities from the model
   * @param priors the vector of priors
   * @param test_labels the vector of test label that correspond to images
   */
  void IterateThroughImages(ifstream& test_images_stream,
      const vector< vector< vector<double>>>& image_probabilities,
      const vector<double>& priors, const vector<double>& test_labels);

  /**
   * This method classifies the image given the posterior probabilities by
   * choosing the greatest one and finding the index
   *
   * @param posterior_probabilities the vector of posterior probabilities
   * @param test_labels the vector of test labels
   * @return the algorithm's guess as to what digit an image is
   */
  double ClassifyAnImage(vector<double>& posterior_probabilities,
                       const vector<double>& test_labels);

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

