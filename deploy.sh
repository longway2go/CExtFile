#!/bin/bash

rm -rf source
mkdir source
cp CExtFile.h ./source
cp CExtFile.cpp ./source

./cleanProjectComments.sh
