#include "ConverterJSON.h"


int main()
{
    auto converter = ConverterJSON();
    auto invIndex = InvertedIndex();

    projectData project_data = converter.GetDataProject();
    std::cout << "Starting: " << project_data.name << std::endl;
    std::cout << "Version: " << project_data.version << std::endl;

    auto requests = converter.GetRequests();

    auto texts = converter.GetTextDocuments();
    invIndex.UpdateDocumentBase(texts);

    SearchServer searchEngine(invIndex);

    auto result = searchEngine.search(requests);
    converter.putAnswers(result);

    std::cout << "Search completed successfully." << std::endl;
}
