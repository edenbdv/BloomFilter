# BloomFilter Project

First step in final project in Advanced Programming course BIU 2024

wiki: https://github.com/edenbdv/Facebook_clone-Server.git

## Overview

This project implements a Bloom Filter, a space-efficient probabilistic data structure used to test whether a given url is a member of a set. It is written in C++ and includes functionalities like adding URLs to the filter, checking if a URL is present, and handling false positives.

This Bloom Filter is used in the Facebook Clone project to prevent users from creating posts with forbidden URLs, improving security by blocking access to restricted or harmful content.
![image](https://github.com/user-attachments/assets/7525be06-a386-4cfa-ba91-df63d207130e)

![image](https://github.com/user-attachments/assets/6231f1c6-02b7-4311-b084-4ed1e5d62a32)


## Compilation

To compile the project, follow these steps:

```bash
git clone https://github.com/edenbdv/BloomFilter.git
cd BloomFilter
cd src
g++ -o main.exe Main.cpp BloomFilter.cpp App.cpp Menu.cpp IHash.h ICommand.h Hashs/StdHash.cpp Hashs/DoubleStdHash.cpp Commands/AddUrlCommand.cpp Commands/ContainsUrlCommand.cpp -pthread

```
*don't forget to adjust your CMakeLists file before the last step

## Running the Code

Once the project is compiled, you can run the executable to interact with the Bloom Filter. Follow these steps:

```bash
./main.exe
```

## Bloom Filter Input Instructions

The first line of input will initialize the Bloom filter size and hash functions. The input will be sent by the Facebook clone server as part of its operation. However, this Bloom filter can be utilized by any server, not just my Facebook-clone server. Below are examples of valid input formats:

- If the first line of input is `100 1`, this means the Bloom filter will have an array of size 100 bits and will utilize only one hash function, which is the built-in `std::hash`.

- If the input is `128 2`, this indicates that the Bloom filter has an array of size 128 bits, and one of the hash functions will perform `std::hash` twice.

- If the input is `256 2 1`, this specifies the use of two hash functions: one performing `std::hash` and the other performing `std::hash` twice.

After the Facebook clone server sends a valid input, it can interact with the menu by entering an option number (1 or 2) along with a URL:

- **Option 1**: Add the URL to the list of blacklisted URLs. For instance, entering `1 www.example.com` will add this URL to the blacklist.
- **Option 2**: Check whether the URL is already in the list of blacklisted URLs. For example, entering `2 www.example.com` will verify if this URL is blacklisted.



## Running the Tests
write these commands in the terminal:

```sudo apt-get update
sudo apt-get install libgtest-dev cmake 
cd path-to-repository’s-directory/BloomFilter
cmake -B build -S .
cmake --build build
ctest --test-dir build --output-on-failure
```

## Running through the Docker
write these commands in the terminal:

```sudo docker build -t ex1 .
sudo docker run ex1
```

## Dependencies

- CMake
- Google Test (for testing)

# Our Work Process

Our BloomFilter project follows an agile development process leveraging Test-Driven Development (TDD), the Red-Green-Refactor cycle, Jira for project management, and Docker for containerization.

## TDD and Red-Green-Refactor Cycle
Red Phase:
We wrote failing test cases outlining Bloom Filter functionality without writing the corresponding implementations.

Green Phase:
We wrote the minimum code to make tests pass.

Refactor Phase:
We refactored the code is for improved structure and maintainability.
Examples for refactoring that we did:

- Support mulitple types of hash functions
- Using Commands design pattern


## Jira for Project Management

Our sprint was set for 2 weeks. In it we created tasks and user stories anf divided them into Epics.
We assigned to each task one of the group members so he is responsible to execute it.

## Docker for Containerization

Docker ensures a uniform environment for the BloomFilter project, guaranteeing consistent execution across diverse machines and operating systems.
We first created a Dockerfile of our program in our local machine, and then we wrote CICD for every release version of the code to automatically push a dockerized
version of the code to a private repository on DockerHub.










