#include <iostream>
#include <vector>
#include <fstream>

#include "nlohmann/json.hpp"
#include "ProgrammExceptions.h"
#include "SearchServer.h"

std::string getPositionNumber(int number)
{
    std::string result;

    if (number < 10)
        result = "00" + std::to_string(number);
    else if (number < 100)
        result = "0" + std::to_string(number);
    else
        result = std::to_string(number);

    return result;
}

class ConverterJSON
{
public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments()
    {
        std::vector<std::string> textDocuments;
        std::ifstream config("config.json");

        if(config.is_open())
        {
            std::string tmp;

            while(config >> tmp)
            {
                textDocuments.push_back(tmp);
            }
            config.close();
        }

        else
        {
            if(config.bad() == true)
            {
                ConfigFileIsMissing error;
                throw error.what();
            }
            else if(config.eof())
            {
                ConfigFileIsEmpty error;
                throw error.what();
            }
        }
    }

    int GetResponsesLimit()
    {
        std::ifstream config("config.json");
        nlohmann::json dataConfig;

        if(config.is_open())
        {
            config >> dataConfig;
            config.close();
        }
        else
        {
            if(config.bad() == true)
            {
                ConfigFileIsMissing error;
                throw error.what();
            }
            else if(config.eof())
            {
                ConfigFileIsEmpty error;
                throw error.what();
            }
        }

        if(dataConfig["config"].contains("max_responses"))
        {
            return dataConfig["config"]["max_responses"];
        }
        else
        {
            return 5;
        }
    }

    std::vector<std::string> GetRequests()
    {
        std::vector<std::string> listOfRequests;
        std::ifstream requestFile("request.json");

        if(requestFile.is_open())
        {
            std::string tmp;

            while(requestFile >> tmp)
            {
                listOfRequests.push_back(tmp);
            }
            requestFile.close();
        }
        else
        {
            if(requestFile.bad() == true)
            {
                ConfigFileIsMissing error;
                throw error.what();
            }
            else if(requestFile.eof())
            {
                ConfigFileIsEmpty error;
                throw error.what();
            }
        }
    }

    void putAnswers(std::vector<std::vector<RelativeIndex>> &listOfAnswers)
    {
        std::ofstream answers("answer.json");
        nlohmann::json outAnswers;

        for (int i = 0; i < listOfAnswers.size(); i++) {
            std::string request = "request" + getPositionNumber(i + 1);

            if (listOfAnswers[i].empty())
                outAnswers["answers"][request]["result"] = false;
            else
                outAnswers["answers"][request]["result"] = true;

            for (int j = 0; j < listOfAnswers[i].size(); ++j) {
                std::string position = "position" + getPositionNumber(j + 1);
                outAnswers["answers"][request]["relevance"][position]["docid"] = listOfAnswers[i][j].doc_id;
                outAnswers["answers"][request]["relevance"][position]["rank"] = listOfAnswers[i][j].rank;
            }
        }

        answers << outAnswers;

        answers.close();
    }
};