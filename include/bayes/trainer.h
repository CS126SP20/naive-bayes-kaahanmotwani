//
// Created by Kaahan Motwani on 3/29/20.
//

#ifndef NAIVEBAYES_TRAINER_H
#define NAIVEBAYES_TRAINER_H

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::vector;

class Trainer {
 public:
   static void parse_stream(ifstream& training_images_stream,
        ifstream& training_labels_stream);

  private:
   static void PixelProbability(const int& digit, ifstream& training_images_stream);
   static double CalculatePriors(ifstream& training_labels_stream, int index);
   static void CalculateProbabilities(int count_of_shaded_pixels[28][28][10], int priors[10]);
};

#endif  // NAIVEBAYES_TRAINER_H
