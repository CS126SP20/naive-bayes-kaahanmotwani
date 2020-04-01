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

    /** This method calls on helper methods that train the model, then sends
     * the test images to classification.cc
     *
     * @param training_images_stream the images needed to train the model
     * @param training_labels_stream the images' corresponding labels
     */
    static void SetUp(ifstream& training_images_stream,
        ifstream& training_labels_stream);

  private:
    static constexpr int kNumDigits = 10;
    static constexpr int kImageSize = 28;
    static constexpr double k = .1;
    static constexpr double v = 2;

    /** This method does most of the calculation of the probabilities needed
     * to train the model. It does this by counting how many pixels are shaded,
     * given a class, for each image in the training set.
     *
     * @param training_images_stream the file stream of training images
     * @param training_labels_stream the file stream of training labels
     * @param pixel_probabilities the vector of pixel probabilities
     * @param occurrences the vector of occurrences for each digit
     */
    static void CalculateProbabilities(ifstream& training_images_stream,
                                       ifstream& training_labels_stream,
                                       vector< vector< vector<double> > >&
                                       pixel_probabilities,
                                       vector<int>& occurrences);

    /** This method takes the pixel probabilities and writes them to a file for
     * later use. It also calculates and adds the prior probabilities to
     * the file.
     *
     * @param pixel_probabilities the probabilities for each pixel in a class
     * @param occurrences the vector of occurrences for each digit
     */
    static void AddProbabilitiesToFile(vector< vector< vector<double> > >&
        pixel_probabilities, const vector<int>& occurrences,
        vector<double>& priors);

};

#endif  // NAIVEBAYES_TRAINER_H
