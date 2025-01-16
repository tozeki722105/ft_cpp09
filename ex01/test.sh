#!/bin/bash

echo "case no_arg"
./RPN

echo "case arg_empty"
./RPN ""

echo "case arg_2over"
./RPN "0 2 - " "0 2 +"

echo "case 9over"
./RPN "12 1 +"

echo "case 9over_2"
./RPN "12 +"

echo "case in_alpha"
./RPN "2 a +"

echo "case last_space"
./RPN "2 1 + "

echo "case / 0"
./RPN "2 4 * 1 1 - /"

echo "case calc_stack_size_err"
./RPN "1 1 2 - * +"

echo "case final_stack_size_err"
./RPN "1 1 - 9"

echo "case INT_MIN calc"
./RPN "0 2 - 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 0 1 - /"

echo "case int overflow"
./RPN "8 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * *"
