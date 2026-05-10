#include "problem.h"
#include "file.h"
#include "volume.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

Problem::Problem(int id, const char* t, const char* desc, Difficulty diff) 
    : problemId(id), title(t), description(desc), difficulty(diff) {}

void Problem::save(Volume& vfs, const char* path) {
    // 1. Serialization
    char* buffer = new char[5000]; 
    int offset = 0;

    sprintf(buffer, "%d|%s|%s|%d", problemId, title.getString(), description.getString(), (int)difficulty);

    // 2. VFS Interaction
    User* systemUser = vfs.getUser(0);
    File* problemFile = new File((char*)path, systemUser, (char*)"system", buffer);
    problemFile->updateContent(buffer);

    delete[] buffer;
}

void Problem::load(Volume& vfs, const char* path) {}

Verdict Problem::evaluate() {
    const char* tempSource = "temp_code.cpp";
    const char* tempExec = "./temp_bin";
    const char* tempOutput = "temp_out.txt";

    // 1. Template Injection (Mental Note: Code usually comes from a Submission object)
    
    // 2. Compilation via System Call
    char compileCmd[100];
    sprintf(compileCmd, "g++ %s -o %s 2> compile_errors.txt", tempSource, tempExec);
    
    int compileResult = system(compileCmd);
    if (compileResult != 0) {
        return Verdict::CE; // Compilation Error
    }

    // 3. Execution against test cases
    for (int i = 0; i < inputs.getCurrItems(); i++) {
        String* input = (String*)inputs.getIndex(i);
        String* expected = (String*)expectedOutputs.getIndex(i);
        
        char runCmd[512];
        sprintf(runCmd, "echo \"%s\" | %s > %s", input->getString(), tempExec, tempOutput);
        system(runCmd);

        // 4. Comparison
        ifstream actualFile(tempOutput);
        if (!actualFile.is_open()) return Verdict::WA;

        char actualContent[1024] = {0};
        actualFile.getline(actualContent, 1024);
        actualFile.close();

        String actualStr(actualContent);
        
        if (!(actualStr == *expected)) {
            remove(tempExec); 
            remove(tempOutput);
            return Verdict::WA; 
        }
    }

    // 5. Cleanup 
    remove(tempSource);
    remove("temp_bin");
    remove(tempOutput);
    remove("compile_errors.txt");

    return Verdict::AC; 
}