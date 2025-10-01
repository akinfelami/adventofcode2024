#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: ./setup_day.sh <day_number>"
  exit 1
fi

DAY=$1
DIR_NAME="day$DAY"

if [ -d "$DIR_NAME" ]; then
  echo "Directory $DIR_NAME already exists."
  exit 1
fi

mkdir "$DIR_NAME"
cp start_here "$DIR_NAME/part1.cpp"
cp start_here "$DIR_NAME/part2.cpp"

echo "Created directory $DIR_NAME with part1.cpp, part2.cpp and input.txt"