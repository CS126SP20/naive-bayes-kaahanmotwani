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

    string label_line;
    string image_line;


    // will be used to store posterior probabilities for each class for a single image
    vector<double> posterior_probabilities(kNumDigits, 0);



    int row = 0;


    // getting each line in the image that has 28 rows (lines)
    while (std::getline(test_images_stream, image_line)) {
      cout << image_line << endl;

      for (size_t col = 0; col < kImageSize; col++) {

        for (size_t digit = 0; digit < kNumDigits; digit++) {
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


      if (row == 28) {

//        for (size_t i = 0; i < kNumDigits; i++) {
//          posterior_probabilities[i] += log10(priors[i]);
//        }
        classify(posterior_probabilities);
        //count++;
        row = 0;
        std::fill(posterior_probabilities.begin(), posterior_probabilities.end(), 0);
      }
    }


  }

  void classify(vector<double>& posterior_probabilities) {
    vector<double> classified_images;
    double classified = 0;
    for (size_t i = 0; i < kNumDigits; i++) {
      if (posterior_probabilities[i] > posterior_probabilities[classified]) {
        classified = i;
      }
    }

    classified_images.push_back(classified);
    cout << classified_images[0] << endl;



  }
}  // namespace bayes

