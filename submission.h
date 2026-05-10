#ifndef SUBMISSION_H
#define SUBMISSION_H

#include "problem.h" 
#include "IPersistable.h"

class Submission : public IPersistable {
private:
    int submissionId;
    int userId;
    int problemId;
    char* sourceCode;
    Verdict result;
    int timestamp;

public:
    Submission(int id, int uId, int pId, const char* code);
    ~Submission();

    void setResult(Verdict v);
    Verdict getResult() const;

    int getProblemId() const;
    const char* getSourceCode() const;

    void save(Volume& vfs, const char* path) override;
    void load(Volume& vfs, const char* path) override;
};

#endif