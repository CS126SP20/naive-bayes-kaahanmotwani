// Copyright (c) 2020 Kaahan Motwani. All rights reserved.

#include <bayes/trainer.h>
#include <gflags/gflags.h>

#include <cstdlib>
#include <string>

DEFINE_string(images, "", "The training images");
DEFINE_string(labels, "", "The training labels");

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, char** argv) {

  gflags::SetUsageMessage(
      "Greets you with your name. Pass --helpshort for options.");

  // Uses gFlags to parse command-line arguments into image & label streams
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  ifstream training_images_stream(FLAGS_images);
  ifstream training_labels_stream(FLAGS_labels);
  Trainer::SetUp(training_images_stream, training_labels_stream);

  return EXIT_SUCCESS;
}
