#ifndef APP_H
#define APP_H

#include "BloomFilter.h"
#include "Menu.h"
#include "IHash.h"
#include "ICommand.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class App {
private:
    std::map<std::string, ICommand*> commands;
    std::vector<IHash*> hashFunctions;
    BloomFilter* bf;
    std::vector<std::string>* blacklist;
    Menu* menu;


public:
    App();

    int getHashesSize() const;

    void run();

    BloomFilter* Initializebf(int client_sock, const std::string& initialInput);

    std::vector<IHash*> InitializeHashes(const std::string& restOfInput);

    std::string handleClient(int client_sock);

    std::string receiveData(int client_sock);

    //std::string initializeClient(int client_sock);

    int initializeClient(int client_sock);

    std::string handleMenu(int client_sock);


    ~App();

    //BloomFilter* getBloomFilter();

    //std::map<std::string, ICommand*> getCommands() const;

    //std::vector<IHash*> getHashFunctions() const;
};

#endif // APP_H
