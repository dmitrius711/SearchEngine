#include "ConverterJSON.h"
#include "nlohmann/json.hpp"
#include "CustomExceptions.h"

projectData ConverterJSON::GetNameAndVersion()
{
    projectData projectData;
    std::ifstream configFile("..\\json_files\\config.json");
    nlohmann::json configJson;
    try
    {
        if(!configFile.is_open())
        {
            throw exceptionConfigFileIsMissing();
        }
    }
    catch(exceptionConfigFileIsMissing e)
    {
        std::cerr << e.what() << std::endl;
    }

    configFile >> configJson;

    try
    {
        if(configJson["config"].empty())
        {
            throw exceptionConfigFileIsEmpty();
        }
    }

    catch(exceptionConfigFileIsEmpty e)
    {
        std::cerr << e.what() << std::endl;
    }

    projectData.name = configJson["config"]["name"];
    projectData.version = configJson["config"]["version"];

    return projectData;
}

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::ifstream configFile("..\\json_files\\config.json");
    std::vector<std::string> listOfFiles;
    std::vector<std::string> fileContents;

    try
    {
        if(!configFile.is_open())
        {
            throw exceptionConfigFileIsMissing();
        }
    }
    catch(exceptionConfigFileIsMissing e)
    {
        std::cerr << e.what() << std::endl;
    }


    nlohmann::json files;

    configFile >> files;
    for(auto& i : files["files"])
    {
        listOfFiles.push_back(i);
    }

    for(auto& j : listOfFiles)
    {
        std::ifstream fileContent(j);
        try
        {
            if(!fileContent.is_open())
            {
                throw exceptionTxtFileIsMissing();
            }
        }
        catch(exceptionTxtFileIsMissing e)
        {
            std::cerr << j << " " << e.what() << std::endl;
        }

        std::string text;
        std::stringstream ss;
        while(std::getline(fileContent, text))  ss << text;
        fileContents.push_back(ss.str());
    }
    return fileContents;
}

int ConverterJSON::GetResponsesLimit()
{
   std::ifstream configFile("..\\json_files\\config.json");
   nlohmann::json configJson;

   try
   {
       if (!configFile.is_open())
       {
           throw exceptionConfigFileIsMissing();
       }
   }
   catch(exceptionConfigFileIsMissing e)
   {
       std::cerr << e.what() << std::endl;
   }

   configFile >> configJson;

   try
   {
       if(configJson["config"].empty())
       {
           throw exceptionConfigFileIsEmpty();
       }
   }

   catch(exceptionConfigFileIsEmpty e)
   {
       std::cerr << e.what() << std::endl;
   }

   if(!configJson["config"]["max_responses"].is_null() && configJson["config"]["max_responses"].is_number())
   {
       return configJson["config"]["max_responses"];
   }
   else
   {
       return 5;
   }
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::ifstream requestFile("..\\json_files\\requests.json");
    std::vector<std::string> result;

    try
    {
        if (!requestFile.is_open())
        {
            throw exceptionRequestsFileIsMissing();
        }
    }
    catch(exceptionRequestsFileIsMissing e)
    {
        std::cerr << e.what() << std::endl;
    }

    nlohmann::json requestJson;
    requestFile >> requestJson;

    try
    {
        if(requestJson["requests"].empty())
        {
            throw exceptionRequestsFileIsEmpty();
        }
    }

    catch(exceptionRequestsFileIsEmpty e)
    {
        std::cerr << e.what() << std::endl;
    }

    for(auto& r : requestJson["requests"])
    {
        result.push_back(r);
    }

    return result;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>> &answers)
{
    nlohmann::json ans;
    int ind = 1;
    std::ofstream answersFile("..\\json_files\\answers.json", std::ios::trunc);

    try
    {
        if (!answersFile.is_open())
        {
            throw exceptionAnswersFileNotOpen();
        }
    }

    catch(exceptionAnswersFileNotOpen e)
    {
        std::cerr << e.what() << std::endl;
    }

    for(const auto& i : answers)
    {
        nlohmann::json request;
        request["result"] = !i.empty();
        for (const auto& p: i)
        {
            nlohmann::json dict_pair;
            dict_pair["docid"] = p.doc_id;
            dict_pair["rank"] = p.rank;
            request["relevance"].push_back(dict_pair);
        }

        std::string name = "request00" + std::to_string(ind);
        ans[name] = request;
        ind++;
    }

    nlohmann::json file;
    file["answers"] = ans;

    answersFile << file.dump(4);
}
