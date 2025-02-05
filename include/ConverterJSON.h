#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "SearchEngine.h"

struct projectData
{
    std::string name; float version; int maxResponses;
};

class ConverterJSON{
public:
    ConverterJSON() = default;
    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    *       в config.json
    */
    std::vector<std::string> GetTextDocuments();
    /**
    * Метод считывает поле max_responses для определения предельного
    *  количества ответов на один запрос
    * @return
    */
    int GetResponsesLimit();
    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string> GetRequests();
    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    void putAnswers(const std::vector<std::vector<RelativeIndex>> &answers);
    /**
     * Метод получения названия проекта
     * @return возвращает название из поля name и версии из поля version
     */
    projectData GetDataProject();
};
