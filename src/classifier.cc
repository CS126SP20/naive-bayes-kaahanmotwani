// Copyright 2020 Kaahan Motwani. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>

namespace bayes {
  void ReadModelData(ifstream& test_images_stream, ifstream& test_labels_stream, vector< vector< vector<double> > >&
  pixel_probabilities, vector<double> priors) {

    std::ifstream model_data("data/model_probabilities.csv");
    std::istream& input_stream = model_data;
    std::string line;

    // These nested while loops will find out the pixels that are shaded
    // in the test images in order to classify them
    double count_of_shaded_pixels[kImageSize][kImageSize][kNumDigits] = {{{0}}};
    string label_line;
    string image_line;
    //int digit;
    bool shaded;

    // will be used to store posterior probabilities for each class for a single image
    vector<double> posterior_probabilities(kNumDigits, 1);

    //while (std::getline(test_labels_stream, label_line)) {

      // Populates occurrences with how many times digits occur in training labels
      //digit = std::stoi(label_line);
      //occurrences[digit]++;



    int row = 0;

    // getting each line in the image that has 28 rows (lines)
    while (row < kImageSize && std::getline(test_images_stream, image_line)) {
      cout << image_line << endl;

      for (size_t col = 0; col < kImageSize; col++) {

        for (size_t digit = 0; digit < kNumDigits; digit++) {
          // getting each character (column) in the row (line)
          if (image_line[col] == '+' || image_line[col] == '#') {
            shaded = true;
            posterior_probabilities[digit] += log10(pixel_probabilities[row][col][digit]);
            // If it's shaded, get the probability at that pixel for each class, and then take the log of it
            // count_of_shaded_pixels[row][col][digit]++;

          } else {
            shaded = false;
            posterior_probabilities[digit] += log10(1 - pixel_probabilities[row][col][digit]);
            // if the space is empty, check for the inverse
          }
        }
      }
      // to move on to the next line in the image
      row++;
    }

    std::cout << posterior_probabilities[1] << std::endl;
    std::cout << posterior_probabilities[2] << std::endl;
    std::cout << posterior_probabilities[3] << std::endl;
    std::cout << posterior_probabilities[4] << std::endl;
    std::cout << posterior_probabilities[5] << std::endl;
    std::cout << posterior_probabilities[6] << std::endl;
    std::cout << posterior_probabilities[7] << std::endl;
    std::cout << posterior_probabilities[8] << std::endl;
    std::cout << posterior_probabilities[9] << std::endl;
    std::cout << posterior_probabilities[0] << std::endl;
    //}


    double class_probabilities[kNumDigits];
    while (std::getline(model_data, line)) {

      std::vector<std::string> results;

      // This set of nested for loops correctly calculates
      for (size_t i = 0; i < kNumDigits; i++) {
        class_probabilities[i] = 0;
        for (size_t x = 0; x < kImageSize; x++) {
          for (size_t y = 0; y < kImageSize; y++) {
            class_probabilities[i] += log10(count_of_shaded_pixels[x][y][i]);
          }
        }
        //class_probabilities[i] += log10(priors[i]);
      }
    }

  }
}  // namespace bayes

