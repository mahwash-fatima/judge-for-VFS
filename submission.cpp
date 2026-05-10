#include "submission.h"
#include "helper.h"
#include "file.h"
#include <iostream>

Submission::Submission(int id, int uId, int pId, const char* code) {
    submissionId = id;
    userId = uId;
    problemId = pId;
    sourceCode = copyStr(code);
    result = Verdict::WA; 
    timestamp = 0;       
}

void Submission::setResult(Verdict v) {
    result = v;
}

Verdict Submission::getResult() const {
    return result;
}

int Submission::getProblemId() const {
    return problemId;
}

const char* Submission::getSourceCode() const {
    return sourceCode;
}

void Submission::save(Volume& vfs, const char* path) {
    char buffer[5000] = {0};
    sprintf(buffer, "%d|%d|%d|%d|%s", submissionId, userId, problemId, (int)result, sourceCode);

}

void Submission::load(Volume& vfs, const char* path) {}

Submission::~Submission() {
    delete[] sourceCode;
}