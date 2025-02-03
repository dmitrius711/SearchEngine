# SearchEngine
#### Project for search texts in files.  


# What is a search engine?
#### This is a console application, searching and having the ability to configure through files of the format JSON
## The principle of operation.
#### 1. Before launching the application, the names of the files to be searched are specified in the configuration file.
#### 2. The search engine itself checks the files and indexes them so that it can later find the most relevant documents based on the search query.
#### 3. The request itself is set as a set of words in the request.json file.
#### 4. The query is converted to a list of words.
#### 5. The search engine searches for those documents that contain the words given in the requests.json file.
#### 6. The search results are sorted. The maximum number of responses is set in the config.json file.
#### 7. The result of the program is written to the answers.json file.







# What technologies are used?
#### The project uses the following list of technologies:
### [C++17](https://en.cppreference.com/w/cpp/17)
### [Cmake 3.28](https://cmake.org/)
### [nlohmann/json](https://github.com/nlohmann/json?ysclid=m6p24s1eqp789591412)
### [Google Tests](https://github.com/google/googletest?ysclid=m6p25nod2y333254595)

# How to start a project
#### 1. Download the project directly from GitHub.
#### 2. After you have downloaded the zip file of the project, unzip it to disk C or any other.
#### 3. Open the project in any IDE, such as [Visual Studio](https://visualstudio.microsoft.com/) or [Clion](https://www.jetbrains.com/clion/?ysclid=m6p2hmhyla280950481).
#### 4. Next, build the project using the Cmake file located in the project.
#### 5. The json_files folder contains a file for configuring the search engine, as well as a file containing queries; they can be edited at your discretion.
#### 6. After configuring the json files, you can run main.cpp , which is located in the root folder of the project.
#### 7. The results of the program are recorded in the answers json file, in the json files folder.
