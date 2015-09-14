Start from 07 Sep 2015

Totally 1111 lines.

#Banking System

##Quick Start

Please compile "main.cpp"

This project using C++11 features.

For Windows users, change the constant in "constant.h" like:
...
//Windows
#define CLEAN "cls"
...
For OS X/Linux/Unix users, change the constant in "constant.h" like:
...
//UNIX/Linux/OS X
#define CLEAN "clear"
...

Example of compile command:

g++-4.9 main.cpp -std=c++11 -O3 -o bank

##File Structure
- main.cpp
    - please compile this file

- headers.h
    - manage all the headers used in the project

- stdc++.h
    -copid from gcc-4.9

- defination.h
    - declaration of classes

- class.cpp
    - codes of member functions of classes

- constant.h
    - some signs and environment dependent values

- interface.cpp
    - a interface example of using the project


##Class Structure
Bank {- Account {- CurrentDeposit - <- Deposit
                 \ FixedDeposit   /

Custom Object Member of Bank: Account
Custom Object Member of Account: CurrentDeposit & FixedDeposit
Derive Class of Deposit : CurrentDeposit & FixedDeposit

interfaceClass: member class of Bank

JoeyTeng
11 Sep 2015
