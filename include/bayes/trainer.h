//
// Created by Kaahan Motwani on 3/29/20.
//

#ifndef NAIVEBAYES_TRAINER_H
#define NAIVEBAYES_TRAINER_H

#include <bayes/classifier.h>
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

    /**
    *
    * @param pixel_probabilities
    * @param occurrences
     */
    static void AddProbabilitiesToFile(vector< vector< vector<double> > >&
        pixel_probabilities, vector<int>& occurrences);

    static double CalculatePriors(ifstream& training_labels_stream, int index);

    /**
    *
    * @param training_images_stream
    * @param training_labels_stream
    * @param pixel_probabilities
    * @param occurrences
     */
    static void CalculateProbabilities(ifstream& training_images_stream,
                                      ifstream& training_labels_stream,
                                      vector< vector< vector<double> > >&
                                          pixel_probabilities,
                                      vector<int>& occurrences);
    static constexpr int kNumDigits = 10;
    static constexpr int kImageSize = 28;
    static constexpr double k = 1;
    static constexpr double v = 2;
};

#endif  // NAIVEBAYES_TRAINER_H
