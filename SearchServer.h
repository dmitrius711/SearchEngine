#include "InvertedIndex.h"

#include <unordered_set>


struct RelativeIndex
{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const
    {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};
class SearchServer
        {
public:

    SearchServer(InvertedIndex& idx) : _index(idx){ };

    std::vector<std::vector<RelativeIndex>> search(const
                                                   std::vector<std::string>& queries_input)
    {
        const int queriesInputSize = getQueriesInputSize(queries_input);

        std::vector<std::vector<RelativeIndex>> result;

        std::unordered_set<std::string> newList(queries_input.begin(), queries_input.end());
        std::copy(queries_input.begin(), queries_input.end(),
                  std::inserter(newList, newList.begin()));


        std::vector<std::vector<Entry>> wordsList;
        for(int i = 0; i < queriesInputSize; i++)
        {
            wordsList.push_back(_index.GetWordCount(queries_input[i]));


            for(int j = 0; j < wordsList.size(); j++)
            {
                if(wordsList[i][j].count < wordsList[i][j + 1].count)
                {
                    //сортируем слова по редкости поменять местами слова
                }

            }

        }

        for(int i = 0; i < _index.getDocsSize(); i++)
        {
            
        }

    }

    int getQueriesInputSize(std::vector<std::string> temp)
    {
        return temp.size();
    }
private:
    InvertedIndex _index;
};