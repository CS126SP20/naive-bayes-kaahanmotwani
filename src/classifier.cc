// Copyright 2020 Kaahan Motwani. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>

namespace bayes {

  double count = 0;
  double num_correct = 0;
  void ReadModelData(ifstream& test_images_stream, ifstream& test_labels_stream,
      vector< vector< vector<double> > >& pixel_probabilities,
      vector<double> priors) {


    std::ifstream model_data("data/model_probabilities.csv");
    std::istream& input_stream = model_data;
    std::string line;

    vector<double> test_labels;
    test_labels = AddLabelsToAVector(test_labels_stream);


    string image_line;

    // will be used to store posterior probabilities for each class for a single image
    vector<double> posterior_probabilities(kNumDigits, 0);

    classify(test_images_stream, posterior_probabilities, pixel_probabilities,
        priors, test_labels);

    double percentage = (num_correct / count);
    cout << percentage << endl;

  }


  void classify(ifstream& test_images_stream, vector<double> posterior_probabilities,
                vector< vector< vector<double> > >& pixel_probabilities,
                vector<double> priors, vector<double> test_labels) {
    string image_line;
    int row = 0;

    // getting each line in the image that has 28 rows (lines)
    while (std::getline(test_images_stream, image_line)) {
      cout << image_line << endl;
      for (size_t col = 0; col < kImageSize; col++) {

        for (size_t digit = 0; digit < kNumDigits; digit++) {
          if (row == 0 && col == 0) {
            posterior_probabilities[digit] += log10(priors[digit]);

          }
          // getting each character (column) in the row (line)
          if (image_line[col] == '+' || image_line[col] == '#') {
            posterior_probabilities[digit] += log10(pixel_probabilities[row][col][digit]);
            // If it's shaded, get the probability at that pixel for each class, and then take the log of it
            // count_of_shaded_pixels[row][col][digit]++;

          } else {
            posterior_probabilities[digit] += log10(1 - pixel_probabilities[row][col][digit]);
            // if the space is empty, check for the inverse
          }


        }
      }
      // to move on to the next line in the image
      row++;

      // If I have reached the end of an image, then reset posterior probabilities (should be 10 for each image)
      if (row == 28) {


        ClassifyAnImage(posterior_probabilities, test_labels);
        row = 0;
        // count keeps track of what image we are on in the test images
        count++;
        std::fill(posterior_probabilities.begin(), posterior_probabilities.end(), 0);
      }
    }
  }

  void ClassifyAnImage(vector<double>& posterior_probabilities, vector<double>& test_labels) {
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

