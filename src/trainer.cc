//
// Created by Kaahan Motwani on 3/29/20.
//

#include "bayes/trainer.h"



void Trainer::parse_stream(ifstream& training_images_stream,
                           ifstream& training_labels_stream) {

  vector<vector<vector<double>>> pixel_probabilities;

  double priors[10];
  for (size_t i = 0; i < 10; i++) {
    priors[i] = CalculatePriors(training_images_stream, i);
  }

  
  const int k = 1;
  const int v = 2;

  int count = 0;


  //double model[][][][];
  string label_line;

  while (std::getline(training_labels_stream, label_line)) {
    int digit = std::stoi(label_line);

    // Passing in the digit that an image corresponds to
    PixelProbability(digit, training_images_stream);
  }



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
  int occurrences[10];
  for (int& occurrence : occurrences) {
    occurrence = 0;
  }

  string line;
  while (std::getline(training_labels_stream, line)) {
    int digit = std::stoi(line);
    occurrences[digit]++;
  }

  return log10(occurrences[index] / 5000.0);
}

