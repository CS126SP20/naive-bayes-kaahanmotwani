// Copyright (c) 2020 Kaahan Motwani. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <bayes/trainer.h>
#include <gflags/gflags.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

// TODO(you): Change the code below for your project use case.

DEFINE_string(images, "", "The training images");
DEFINE_string(labels, "", "The training labels");

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, char** argv) {

//  if (argc > 2) {
//
//  } else {
//    cout << "You need to provide a Sudoku file through command line "
//            "arguments!"
//         << endl;
//    exit(0);
//  }
  gflags::SetUsageMessage(
      "Greets you with your name. Pass --helpshort for options.");

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  ifstream training_images_stream(FLAGS_images);
  ifstream training_labels_stream(FLAGS_labels);

  Trainer trainer;
  trainer.parse_stream(training_images_stream, training_labels_stream);




//  if (FLAGS_name.empty()) {
//    std::cerr << "Please provide a name via the --name flag." << std::endl;
//    return EXIT_FAILURE;
//  }

//  const std::string puncutation = FLAGS_happy ? "!" : ".";
//
//  std::cout << "Hello, " << FLAGS_name << puncutation << std::endl;
  return EXIT_SUCCESS;
}
