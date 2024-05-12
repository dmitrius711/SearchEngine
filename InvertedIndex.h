#include <iostream>
#include <vector>
#include <map>
#include <fstream>


struct Entry
{
    size_t doc_id = 0, count;

    bool operator ==(const Entry& other) const
    {
        return (doc_id == other.doc_id &&
                count == other.count);
    }

};

class InvertedIndex
{
public:
    InvertedIndex() = default;

    void UpdateDocumentBase(std::vector<std::string> input_docs)
    {
        for(int i = 0; i < input_docs.size(); i++)
        {
            docs.push_back(input_docs[i]);
        }
    }

    std::vector<Entry> GetWordCount(const std::string& word)
    {
        std::vector<Entry> listOfCount;
        for(int i = 0; i < docs.size(); i++)
        {
            if(docs[i] == word)
            {
               Entry detectedWord;
               detectedWord.doc_id = i;

               for(int j = i + 1; j < docs.size(); j++)
               {
                   if(docs[j] == word)
                   {
                       detectedWord.count += 1;
                   }
               }

               listOfCount.push_back(detectedWord);
               freqDictionary.emplace(word, listOfCount);
            }
        }
        return listOfCount;
    }

    std::string getWordFromDocs(int i)
    {
        return docs[i];
    }

    int getDocsSize()
    {
        return docs.size();
    }

    int getDocSize(int i)
    {
        return docs[i].size();
    }

    std::vector<Entry> GetEntry(std::string word)
    {
        return freqDictionary[word];
    }

private:
    std::map<std::string, std::vector<Entry>> freqDictionary;
    std::vector<std::string> docs;
};