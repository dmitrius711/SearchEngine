
#include "ConverterJSON.h"
#include <unordered_set>
#include <algorithm>
#include <vector>


std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{
    auto results = std::vector<std::vector<RelativeIndex>>();

    projectData prData;

    std::vector<std::string> individualWords;

    for(auto &request : queries_input)
    {
        std::stringstream ss(request);
        std::string wordFromString;
        while (ss >> wordFromString)
        {
            individualWords.push_back(wordFromString);
        }

        std::unordered_set<std::string> makeUniqueWords(individualWords.begin(), individualWords.end());
        std::copy(individualWords.begin(), individualWords.end(),
                  std::inserter(makeUniqueWords, makeUniqueWords.begin()));

        std::vector<std::pair<std::string, size_t>> wordsCount;

        for (auto &word: individualWords)
        {
            auto frequencyWord = this->_index.GetWordCount(word);
            size_t sumWord = 0;

            for (const auto &entry: frequencyWord)
            {
                sumWord += entry.count;
            }
            auto wordCount = std::make_pair(word, sumWord);
            wordsCount.push_back(wordCount);
        }

        std::sort(wordsCount.begin(), wordsCount.end(),
                  [](std::pair<std::string, size_t> const &a, std::pair<std::string, size_t> const &b) {
                      return a.second < b.second;
                  });
        auto answer = std::vector<RelativeIndex>();

        if (wordsCount[0].second != 0)
        {
            std::map<size_t, std::vector<std::pair<std::string, size_t>>> docs;

            for (auto &[key, value]: wordsCount)
            {
                auto freqDictionary = this->_index.GetWordCount(key);

                for (const auto &entry: freqDictionary)
                {
                    if (docs.count(entry.doc_id) == 0) {
                        docs[entry.doc_id] = std::vector<std::pair<std::string, size_t>>();
                    }
                    docs[entry.doc_id].emplace_back(std::make_pair(key, entry.count));
                }
            }

            size_t maxAbsoluteRelevance = 0;

            std::map<size_t, size_t> relativeMap;

            for (auto i: docs)
            {
                size_t docAbsoluteRelevance = 0;

                for (auto j: i.second)
                {
                    docAbsoluteRelevance += j.second;
                }

                if (docAbsoluteRelevance > maxAbsoluteRelevance)
                {
                    maxAbsoluteRelevance = docAbsoluteRelevance;
                }

                relativeMap.insert({i.first, docAbsoluteRelevance});
            }


            for (auto &[key, value]: relativeMap)
            {
                auto relativeRelevance = RelativeIndex(key, (float) value / maxAbsoluteRelevance);

                answer.push_back(relativeRelevance);

                std::sort(answer.begin(), answer.end(),
                          [](RelativeIndex const &a, RelativeIndex const &b) { return a.rank > b.rank; });

                while (answer.size() > prData.maxResponses)
                {
                    answer.pop_back();
                }
            }
        }
        results.push_back(answer);
    }
    return results;
}
