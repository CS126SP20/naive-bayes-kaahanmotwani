//
// Created by Kaahan Motwani on 3/29/20.
//

#include "bayes/trainer.h"



void Trainer::parse_stream(ifstream& training_images_stream,
                           ifstream& training_labels_stream) {
  const int kNumDigits = 10;
  vector<vector<vector<double>>> pixel_probabilities;

  // populates array with 0
  int occurrences[kNumDigits];
  for (int& occurrence : occurrences) {
    occurrence = 0;
  }



  const int k = 1;
  const int v = 2;



  string label_line;
  string image_line;

  const int kImageSize = 28;

  double count_of_shaded_pixels[kImageSize][kImageSize][kNumDigits] = {{{0}}};

  //cout << count_of_shaded_pixels[20][6][8] << endl;
  int digit;

  while (std::getline(training_labels_stream, label_line)) {

    // Populates occurrences with how many times digits occur in training labels
    digit = std::stoi(label_line);
    occurrences[digit]++;

    int count = 0;

    while (count < kImageSize && std::getline(training_images_stream, image_line)) {

      for (size_t i = 0; i < kImageSize; i++) {

        if (image_line[i] == '+' || image_line[i] == '#') {
          count_of_shaded_pixels[count][i][digit]++;

        }
      }
      count++;
    }
  }

  double priors[kNumDigits];


  for (size_t i = 0; i < kNumDigits; i++) {
    priors[i] = (occurrences[i] / 5000.0);
  }
  cout << priors[2] << endl;

  //CalculateProbabilities(count_of_shaded_pixels, priors);

  cout << count_of_shaded_pixels[16][8][2] << endl;

  for (size_t x = 0; x < kImageSize; x++) {
    for (size_t y = 0; y < kImageSize; y++) {
      for (size_t i = 0; i < kNumDigits; i++) {
        count_of_shaded_pixels[x][y][i] = count_of_shaded_pixels[x][y][i] / occurrences[i];
      }
    }
  }

  cout << count_of_shaded_pixels[16][8][2] << endl;

}

void Trainer::PixelProbability(const int& digit,
    ifstream& training_images_stream) {

  string image_line;

  while (std::getline(training_images_stream, image_line)) {

    int num_shaded = 0;
    for (size_t i = 0; i < 28; i++) {
      if (image_line[i] == '+' || image_line[i] == '#') {
        num_shaded++;

      }
    }

  }
}

double Trainer::CalculatePriors(ifstream& training_labels_stream, int index) {


}

void Trainer::CalculateProbabilities(int count_of_shaded_pixels[28][28][10], int priors[10]) {


}

