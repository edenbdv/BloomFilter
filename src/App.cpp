#include "BloomFilter.h"
#include "./Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include "IHash.h"
#include "ICommand.h"
#include "App.h"
#include "./Hashs/StdHash.h"
#include "./Hashs/DoubleStdHash.h"
#include "./Commands/AddUrlCommand.h"
#include "./Commands/ContainsUrlCommand.h"
#include <map>
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>




App::App() : bf(nullptr), menu(new Menu()),blacklist(new std::vector<std::string>())
{
    // initializing a commands map
    commands["1"] = new AddUrlCommand();
    commands["2"] = new ContainsUrlCommand();

    // Initialize hash functions vector
    hashFunctions.push_back(new StdHash());
    hashFunctions.push_back(new DoubleStdHash());
}


std::string App::receiveData(int client_sock)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer)); // Clear the buffer before receiving data

    // Receive data from the client
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);

    if (bytes_received < 0)
    {
        // Error receiving data
        perror("error receiving data from client");
        return ""; // Return empty string if there's an error
    }
    else if (bytes_received == 0)
    {
        // Connection closed by client
        return "_CONNECTION_CLOSED_"; // Return special value to indicate connection closed
    }

    buffer[bytes_received] = '\0'; // Null-terminate the received data
    std::string receivedData = std::string(buffer);
    return receivedData;
}


int App::initializeClient(int client_sock) {

    // Receive initial data from the client
    std::string initialInput = receiveData(client_sock);
    if (initialInput.empty())
    {
        // Error or connection closed by client
        return -1;
    }


    // Process the initial data
    this->bf = Initializebf(client_sock, initialInput);

   // Send a special string back to the client to indicate success
    std::string successMessage = "SUCCESS";
    send(client_sock, successMessage.c_str(), successMessage.size(), 0);



    handleMenu(client_sock);
}


std::string App::handleMenu(int client_sock) {
    std::vector<std::string> words;
    //std::vector<std::string> blacklist;

    // Enter an infinite loop to handle subsequent client commands
    while (true)
    {

        // Receive client command and URL
        std::string input = receiveData(client_sock);

        if (input == "_CONNECTION_CLOSED_")
        {
            // Connection closed by client
            close(client_sock);
            break;
        }
        else if (input.empty())
        {
            // Empty input received, continue waiting for commands
            continue;
        }

       
        // Process the client command and URL using the menu
        words = menu->splitInput(input);

        if (menu->validateInput(words))
        {
            menu->setTask(words[0]);
            menu->setURL(words[1]);

            // Execute the command
            std::string task = menu->getTask();
            std::string url = menu->getUrl();
            std::string isin = commands[task]->execute(url, *bf, *blacklist);
            // Print the result if the command is check(2)
            if (task == "2")
            {
                    // Send the result back to the client
                    send(client_sock, isin.c_str(), isin.size(), 0);

            } else if (task == "1")
            {   
                std::string successMessage = "SUCCESS";
                send(client_sock, successMessage.c_str(), successMessage.size(), 0);   
                    }

            // Clear task and URL for the next input
            menu->setTask("");
            menu->setURL("");
        }
        else
        {
            // Invalid input from client
            std::cerr << "Invalid input from client: " << input << std::endl;
                // Send error message to client
            std::string errorMessage = "INVALID_INPUT";
            send(client_sock, errorMessage.c_str(), errorMessage.size(), 0);
        }

    }
    return "";

   
}

void App::run()
{

    // create socket for server
    const int server_port = 5555;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("error creating socket");
        return;
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("error binding socket");
        return;
    }

    if (listen(sock, 5) < 0)
    {
        perror("error listening to a socket");
        return;
    }

    bool initialized = false;
    int client_sock;
    while (true)
    {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);


         if (!initialized) {
            // Accept a connection for initialization
            client_sock = accept(sock, (struct sockaddr *)&client_sin, &addr_len);
            if (client_sock < 0)
            {
                perror("Error accepting client");
                close(sock);
                return;
            }

            initializeClient(client_sock);

       
            initialized = true;
         } else {
            // Accept subsequent client connections after initialization
            client_sock = accept(sock, (struct sockaddr *)&client_sin, &addr_len);
            if (client_sock < 0)
            {
                perror("Error accepting client");
                continue;
            }

            // Start a new thread for handling client requests
            std::thread client_thread(&App::handleMenu, this, client_sock);
            client_thread.detach();
        }


        
    }
    close(sock);
}




BloomFilter *App::Initializebf(int client_sock, const std::string& initialInput)
{
    BloomFilter *bf = nullptr;
    int size;
    std::vector<IHash *> hashes;

    std::istringstream iss(initialInput);


    while (true)
    {

        // Read the first word as size
        if ((iss >> size) && size > 0)
        {

            // Read the rest of the line
            std::string restOfInput;
            std::getline(iss, restOfInput);

            // Pass the rest of the input
            hashes = InitializeHashes(restOfInput);

            // if hahses is not empty it means there was a valid input
            if (!hashes.empty())
            {   

                bf = new BloomFilter(size, hashes, commands);

               
                break;
            }
            // if first word of input cannot be converted to int
        }
      else
            {
                 // Invalid hash functions received from client
                // Send error message to client
                std::string errorMessage = "INVALID_INPUT";
                send(client_sock, errorMessage.c_str(), errorMessage.size(), 0);
            }
       

        // Receive input from the client socket
        std::string newInput = receiveData(client_sock);
        if (newInput.empty())
        {
            // Error or connection closed by client
            std::cerr << "Error: Empty input received from client." << std::endl;
            break;
        }


        // Update the input stream with the new input
        iss.clear(); // Clear any error flags
        iss.str(newInput); // Set the new input as the content of the stream



    }

    return bf;
}

std::vector<IHash *> App::InitializeHashes(const std::string &restOfInput)
{
    // Tokenize the rest of the input by spaces
    std::istringstream iss(restOfInput);
    std::vector<std::string> tokens;
    std::string numOfHash;
    std::vector<IHash *> hashes;

    while (iss >> numOfHash)
    {
        tokens.push_back(numOfHash);
    }

    for (int i = 0; i < tokens.size(); i++)
    {
        try
        {
            int tokenAsInt = std::stoi(tokens[i]); // Convert the token to an integer
            // if the input is smaller than the size of the vector of hashes that we initialized in the beginning and not 0
            if ((tokenAsInt <= getHashesSize()) && (tokenAsInt > 0))
            {
                hashes.push_back(hashFunctions[tokenAsInt - 1]);
            }
            else
            {
                hashes.clear();
                break; // Stop the loop if the token is out of bounds
            }
            // if word is not int
        }
        catch (const std::invalid_argument &e)
        {
            hashes.clear();
            break;
        }
    }
    return hashes;
}

int App::getHashesSize() const
{
    return hashFunctions.size();
}

App::~App()
{
    // Clean up memory
    for (auto &command : commands)
    {
        delete command.second;
    }
    commands.clear();

    for (auto &hashFunction : hashFunctions)
    {
        delete hashFunction;
    }
    hashFunctions.clear();

    delete blacklist;

}