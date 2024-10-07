#ifndef MENU_H
#define MENU_H
#include <string>
#include <vector>
#include "BloomFilter.h" 

class Menu {
public:
    // Constructor
    Menu();
    ~Menu();
    //void input(int client_sock);
    void setURL(const std::string& newUrl);
    void setTask(const std::string& newtask);
    // Getter methods
    std::string getUrl() const;
    std::string getTask() const;
    
    std::vector<std::string> splitInput(const std::string& input);
    bool validateInput(const std::vector<std::string>& strVector);

private:
    std::string url;
    std::string task;
};

#endif // MENU_H
    
