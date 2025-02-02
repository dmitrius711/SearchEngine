#include "InvertedIndex.h"


void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs)
{
    for(const auto & input_doc : input_docs)
    {
        docs.push_back(input_doc);
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word)
{
    std::vector<Entry> result;

    for(int i = 0; i < docs.size(); i++)
    {
        Entry wordEntry;
        wordEntry.doc_id = i;

        std::stringstream ss(docs[i]);
        while(!ss.eof())
        {
            std::string wordTmp;
            ss >> wordTmp;
            if(wordTmp == word)
            {
                wordEntry.count++;
            }
        }

        if(wordEntry.count != 0)
        {
            result.push_back(wordEntry);
        }

    }

    return result;
}
