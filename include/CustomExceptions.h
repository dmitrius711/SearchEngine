class exceptionConfigFileIsMissing
{
public:
    const char* what()
    {
        return "Config file is missing";
    }
};

class exceptionConfigFileIsEmpty
{
public:
    const char* what()
    {
        return "Config file is empty";
    }
};

class exceptionRequestsFileIsMissing
{
public:
    const char* what()
    {
        return "Requests file is missing";
    }
};

class exceptionRequestsFileIsEmpty
{
public:
    const char* what()
    {
        return "Requests file is empty";
    }
};

class exceptionAnswersFileNotOpen
{
public:
    const char* what()
    {
        return "answers.json cannot opened";
    }
};

class exceptionTxtFileIsMissing
{
public:
    const char* what()
    {
        return "file is missing";
    }
};
