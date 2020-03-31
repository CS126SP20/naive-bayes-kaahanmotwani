//
// Created by Kaahan Motwani on 3/29/20.
//

#include "bayes/trainer.h"



void Trainer::parse_stream(ifstream& training_images_stream,
                           ifstream& training_labels_stream) {

  vector< vector< vector<double>>> pixel_probabilities(kImageSize,
      vector<vector<double>>(kImageSize,
          vector<double>(kNumDigits,0)));

  // populates vector with 0s
  vector<int> occurrences(kNumDigits, 0);
  vector<double> priors;

  CalculateProbabilities(training_images_stream, training_labels_stream,
      pixel_probabilities, occurrences);

  AddProbabilitiesToFile(pixel_probabilities, occurrences, priors);


  std::ifstream test_images_stream("data/testimages");
  std::ifstream test_labels_stream("data/testlabels");

  bayes::ReadModelData(test_images_stream, test_labels_stream, priors);

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
    digit = std::stoi(label_line);
    // Populates occurrences with how many times digits occur in training labels
    occurrences[digit]++;

    int row = 0;
    // getting each line in the image that has 28 rows (lines)
    while (row < kImageSize && std::getline(training_images_stream,
                                            image_line)) {
      for (size_t col = 0; col < kImageSize; col++) {
        // getting each character (column) in the row (line)
        if (image_line[col] == '+' || image_line[col] == '#') {
          pixel_probabilities[row][col][digit]++;
        }
      }
      // to move on to the next line in the image
      row++;
    }
  }

}

void Trainer::AddProbabilitiesToFile(vector< vector< vector<double> > >&
    pixel_probabilities, vector<int>& occurrences, vector<double>& priors) {

  std::ofstream file("data/model_probabilities");

  for (size_t i = 0; i < kNumDigits; i++) {
    for (size_t row = 0; row < kImageSize; row++) {
      for (size_t col = 0; col < kImageSize; col++) {
        // This represents the Laplace smoothed probabilities of each pixel
        // being shaded for a given class (digit)
        pixel_probabilities[row][col][i] =
            (k + pixel_probabilities[row][col][i]) / ((v * k) + occurrences[i]);

        file << pixel_probabilities[row][col][i];
        file << " ";
      }
      file << endl;
    }
    file << endl;
  }

  // vector<double> priors;

  //This correctly calculates the prior probabilities and adds them to the csv
  for (size_t i = 0; i < kNumDigits; i++) {
    priors.push_back(occurrences[i] / 5000.0);
    file << priors[i];
    file << " ";
  }

  file.close();

}



