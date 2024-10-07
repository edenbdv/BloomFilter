FROM gcc:latest

# Set the working directory inside the container
WORKDIR /usr/src/ex1

# copy src dir to where the docker is located in the container(WORKDIR)
#COPY ./src/ .
# Copy individual source files and headers
COPY ./src/ .


# Compile our code
RUN g++ -o ex1 ./Main.cpp \
                            ./App.cpp\
                            ./BloomFilter.cpp \
                            ./Hashs/StdHash.cpp \
                            ./Hashs/DoubleStdHash.cpp \
                            ./Commands/AddUrlCommand.cpp \
                            ./Commands/ContainsUrlCommand.cpp \
                            ./Menu.cpp 


EXPOSE 5555

#run the  new execute file
CMD ["./ex1"]
