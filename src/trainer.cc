//
// Created by Kaahan Motwani on 3/29/20.
//

#include "bayes/trainer.h"



void Trainer::parse_stream(ifstream& training_images_stream,
                           ifstream& training_labels_stream) {

  vector<vector<vector<double>>> pixel_probabilities(28,
      vector<vector<double>>(28,vector<double>(10,0)));


  // populates vector with 0s
  vector<int> occurrences(kNumDigits, 0);

//  int occurrences[kNumDigits];
//  for (int& occurrence : occurrences) {
//    occurrence = 0;
//  }








  CalculateProbabilities(training_images_stream, training_labels_stream,
      pixel_probabilities, occurrences);

  AddProbabilitiesToFile(pixel_probabilities, occurrences);


  std::ifstream test_images_stream("data/testimages");
  std::ifstream test_labels_stream("data/testlabels");

  bayes::ReadModelData(test_images_stream, test_labels_stream);


  // cout << probabilities[0] << endl;

}

void Trainer::AddProbabilitiesToFile(vector< vector< vector<double> > >&
    pixel_probabilities, vector<int>& occurrences) {

  std::ofstream file("data/model_probabilities.csv");

  for (size_t i = 0; i < kNumDigits; i++) {
    for (size_t row = 0; row < kImageSize; row++) {
      for (size_t col = 0; col < kImageSize; col++) {
        // This represents the Laplace smoothed probabilities of each pixel
        // being shaded for a given class (digit)
        pixel_probabilities[row][col][i] =
            (k + pixel_probabilities[row][col][i]) / ((v * k) + occurrences[i]);

        file << pixel_probabilities[row][col][i];
        file << ", ";
      }
      file << endl;
    }
    file << endl;
  }

  vector<double> priors;

  //This correctly calculates the prior probabilities and adds them to the csv
  for (size_t i = 0; i < kNumDigits; i++) {
    priors.push_back(occurrences[i] / 5000.0);
    file << priors[i];
    file << ", ";
  }

  file.close();

}

double Trainer::CalculatePriors(ifstream& training_labels_stream, int index) {


}

void Trainer::CalculateProbabilities(ifstream& training_images_stream,
                                     ifstream& training_labels_stream,
                                     vector< vector< vector<double> > >&
                                         pixel_probabilities,
                                     vector<int>& occurrences) {
  string label_line;
  string image_line;
  int digit;

  while (std::getline(training_labels_stream, label_line)) {
    // Populates occurrences with how many times digits occur in training labels
    digit = std::stoi(label_line);
    occurrences[digit]++;

    int row = 0;

    // getting each line in the image that has 28 rows (lines)
    while (row < kImageSize && std::getline(training_images_stream, image_line)) {

      for (size_t col = 0; col < kImageSize; col++) {
        // getting each character (column) in the row (line)
        if (image_line[col] == '+' || image_line[col] == '#') {
          pixel_probabilities[row][col][digit]++;
          //count_of_shaded_pixels[row][col][digit]++;

        }
      }
      // to move on to the next line in the image
      row++;
    }
  }

}

