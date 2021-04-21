#! /bin/bash
rm bmp_test.bmp && ./miniRT scenes/bmp_test.rt --save && hexdump bmp_test.bmp
