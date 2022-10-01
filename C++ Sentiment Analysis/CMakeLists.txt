cmake_minimum_required(VERSION 3.15)
project(Assignment2_sentiment)

set(CMAKE_CXX_STANDARD 17)
# C++17 includes a library to work with the file system
# https://en.cppreference.com/w/cpp/filesystem


##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.
set (input01 "data/train_dataset_20k.csv")
set (input02 "data/test_dataset_10k.csv")
set (input03 "data/test_dataset_sentiment_10k.csv")

##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03)
    configure_file(${file} ${file} COPYONLY)
endforeach()

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

# Create the executable for sorting
add_executable(sentiment main.cpp DSString.cpp DSVector.h Twitter.cpp Twitter.h DataFrame.h Word.cpp Word.h)

set(CMAKE_VERBOSE_MAKEFILE OFF)

