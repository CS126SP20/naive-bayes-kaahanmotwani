// Copyright 2020 Kaahan Motwani. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>

namespace bayes {
  double count = 0;
  double num_correct = 0;

  void ValidateClassification(ifstream& test_images_stream,
      ifstream& test_labels_stream) {
    // Uses an ifstream to get model file, and then places it into an istream
    std::ifstream model_data("data/model_probabilities");
    std::istream& input_stream = model_data;
    // Gets the probabilities of each image and priors from the model using
    // helper functions
    vector< vector< vector<double>>> image_probabilities =
        ReadModelData(input_stream);
    vector<double> priors = ReadPriorsFromModel(input_stream);

    vector<double> test_labels;
    test_labels = AddLabelsToAVector(test_labels_stream);

    IterateThroughImages(test_images_stream,
        image_probabilities, priors, test_labels);

    double percentage_correct = (num_correct / count);
    cout << percentage_correct * 100;
    cout << "% of the images were correctly classified!" << endl;
  }

  vector< vector< vector<double>>> ReadModelData(istream& input_stream) {
    //
    vector< vector< vector<double>>> image_probabilities(kImageSize,
        vector<vector<double>>(kImageSize,
            vector<double>(kNumDigits,0)));
    //
    for (size_t i = 0; i < kNumDigits; i++) {
      for (size_t row = 0; row < kImageSize; row++) {
        for (size_t col = 0; col < kImageSize; col++) {
          input_stream >> image_probabilities[row][col][i];
        }
      }
    }

    return image_probabilities;
  }

  vector<double> ReadPriorsFromModel(istream& input_stream) {
    vector<double> priors(kNumDigits, 0);
    // C
    for (size_t i = 0; i < kNumDigits; i++) {
      double d;
      input_stream >> d;
      priors[i] = d;
    }

    return priors;
  }

  void IterateThroughImages(ifstream& test_images_stream,
      const vector< vector< vector<double>>>& image_probabilities,
      const vector<double>& priors, const vector<double>& test_labels) {

    // will be used to store posterior probabilities for each
    // class for a single image
    vector<double> posterior_probabilities(kNumDigits, 0);
    string image_line;
    int row = 0;

    // getting each line in the image that has 28 rows (lines)
    while (std::getline(test_images_stream, image_line)) {
      cout << image_line << endl;

      for (size_t col = 0; col < kImageSize; col++) {
        for (size_t digit = 0; digit < kNumDigits; digit++) {
          // The if statement below adds the priors to the posterior
          // probabilities, but only once per image. Row and Col being 0
          // was arbitrarily chosen
          if (row == 0 && col == 0) {
            posterior_probabilities[digit] += log10(priors[digit]);
          }

          // getting each character (column) in the row (line)
          if (image_line[col] == '+' || image_line[col] == '#') {
            // If it's shaded, get the probability at that pixel for
            // each class, and then take the log of it
            posterior_probabilities[digit] +=
                log10(image_probabilities[row][col][digit]);
          } else {
            // if the space is empty, check for the probability
            // of the pixel not being shaded in the model
            posterior_probabilities[digit] +=
                log10(1 - image_probabilities[row][col][digit]);
          }
        }
      }

      // to move on to the next line in the image
      row++;
      // If I have reached the end of an image, then reset
      // the posterior probabilities (should be 10 of them per image)
      if (row == 28) {
        ClassifyAnImage(posterior_probabilities, test_labels);
        row = 0;
        // count keeps track of what image we are on in the test images
        count++;
        std::fill(posterior_probabilities.begin(),
            posterior_probabilities.end(), 0);
      }
    }
  }

  void ClassifyAnImage(vector<double>& posterior_probabilities,
      const vector<double>& test_labels) {
    double classified = 0;
    for (size_t i = 0; i < kNumDigits; i++) {
      if (posterior_probabilities[i] > posterior_probabilities[classified]) {
        classified = i;
      }
    }

    cout << classified << endl;

    if (classified == test_labels[count]) {
      num_correct++;
      cout << "correct" << endl;
    }
  }

  vector<double> AddLabelsToAVector(ifstream& test_labels_stream) {
    string label_line;
    double value;
    vector<double> test_labels;
    while (std::getline(test_labels_stream, label_line)) {
      value = std::stoi(label_line);
      test_labels.push_back(value);
    }

    return test_labels;
  }

}  // namespace bayes

