#include <iostream>
#include <vector>
#include <sstream>
#include "Menu.h"
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>

// Constructor definition
Menu::Menu() : url(""), task("0") {
}

Menu::~Menu() {
    // unique_ptr will automatically manage the memory
}

//this method receives the input from the user and sends it to other methods for handling
// void Menu::input() {
//     std::vector<std::string> words;
//     do {      
//         std::string input;
//         std::getline(std::cin, input);
//         words = splitInput(input);

//         if(validateInput(words)) {
//             setTask(words[0]);
//             setURL(words[1]);   
//         } 
//         std::cin.clear();
//     } while(!validateInput(words));

// }



// void Menu::input(int client_sock) {
//     std::vector<std::string> words;
//     do {      
//         std::string input;
        
//         char buffer[1024];
//         ssize_t bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
//         if (bytes_received < 0) {
//             // Handle error
//             std::cerr << "Error receiving data from socket" << std::endl;
//             return;
//         }
//         buffer[bytes_received] = '\0'; // Null-terminate the received data
//         input = buffer;

//         words = splitInput(input);

//         if(validateInput(words)) {
//             setTask(words[0]);
//             setURL(words[1]);   
//         } 
//     } while(!validateInput(words));
// }



// Setter method definitions
void Menu::setURL(const std::string& newUrl) {
    this->url = newUrl;
}

void Menu::setTask(const std::string& newtask) {
    this->task = newtask;
}

// Getter method definitions
std::string Menu::getUrl() const {
    return url;
}

std::string Menu::getTask() const {
    return task;
}

//this method splits the line of input and returns an array of the args that were in the line
std::vector<std::string> Menu::splitInput(const std::string& input) {
    std::vector<std::string> result;
    std::istringstream iss(input);

    // Tokenize the string by spaces
    std::string word;
    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

//this method checks that the input is valid
bool Menu::validateInput(const std::vector<std::string>& strVector) {
    // Check if the vector is size 2
    if (strVector.size() != 2) {
        return false;
    }

    // Check if the first element is either "1" or "2"
    return (strVector[0] == "1" || strVector[0] == "2");
}

