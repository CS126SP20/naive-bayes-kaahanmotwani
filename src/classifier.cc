// Copyright 2020 Kaahan Motwani. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>

namespace bayes {
  int count = 0;
  void ReadModelData(ifstream& test_images_stream, ifstream& test_labels_stream, vector< vector< vector<double> > >&
  pixel_probabilities, vector<double> priors) {

    string label_line2;
    double value;
    vector<double> test_labels;
    while (std::getline(test_labels_stream, label_line2)) {
      value = std::stoi(label_line2);
      test_labels.push_back(value);

    }
    cout << test_labels[0] << endl;
    cout << test_labels[1] << endl;
    cout << test_labels[2] << endl;
    cout << test_labels[998] << endl;
    cout << test_labels[999] << endl;


    std::ifstream model_data("data/model_probabilities.csv");
    std::istream& input_stream = model_data;
    std::string line;

    string label_line;
    string image_line;


    // will be used to store posterior probabilities for each class for a single image
    vector<double> posterior_probabilities(kNumDigits, 0);
//    for (size_t i = 0; i < kNumDigits; i++) {
//      posterior_probabilities[i] += log10(priors[i]);
//    }


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


        classify(posterior_probabilities, test_labels);
        row = 0;
        // count keeps track of what image we are on in the test images
        count++;
        std::fill(posterior_probabilities.begin(), posterior_probabilities.end(), 0);
      }
    }


  }


  void classify(vector<double>& posterior_probabilities, vector<double>& test_labels) {
    //vector<double> classified_images;
    double classified = 0;
    for (size_t i = 0; i < kNumDigits; i++) {
      if (posterior_probabilities[i] > posterior_probabilities[classified]) {
        classified = i;
      }
    }

    //classified_images.push_back(classified);
    cout << classified << endl;


    if (classified == test_labels[count]) {
      cout << "correct" << endl;
    }

    
//    string label_line;
//    int value;
//    int count_of_while_loop = 0;
//    cout << count << endl;
//    while (std::getline(test_labels_stream, label_line)) {
//      value = std::stoi(label_line);
//      cout << count_of_while_loop << endl;
//      if (count_of_while_loop == count) {
//        cout << "reached" << endl;
//        if (value == classified) {
//          cout << "correct!" << endl;
//        }
//      }
//      count_of_while_loop++;
//    }

    //count++;
  }
}  // namespace bayes

