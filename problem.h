#ifndef PROBLEM_H
#define PROBLEM_H

#include "IPersistable.h"
#include "IEvaluatable.h"
#include "DynamicArray.h"
#include "string.h"

enum class Difficulty { EASY = 1, MEDIUM, HARD, CHALLENGE, EXTREME };

class Problem : public IPersistable, public IEvaluatable {
private:
    int problemId;
    String title;
    String description;
    Difficulty difficulty;
    
    DynamicArray inputs; 
    DynamicArray expectedOutputs;

public:
    Problem(int id, const char* t, const char* desc, Difficulty diff);
    
    // Since DynamicArray stores void*, it won't call ~String() automatically
    ~Problem() {
        for (int i = 0; i < inputs.getCurrItems(); i++) {
            delete (String*)inputs.getIndex(i); // Manual cast and delete
        }
        for (int i = 0; i < expectedOutputs.getCurrItems(); i++) {
            delete (String*)expectedOutputs.getIndex(i);
        }
    }

    // IPersistable Interface: Interaction with your Volume and File classes
    void save(Volume& vfs, const char* path) override;
    void load(Volume& vfs, const char* path) override;
    
    // IEvaluatable Interface: To be called by the Judge logic
    Verdict evaluate() override;

    void addTestCase(const char* in, const char* out) {
        inputs.addItem(new String(in));
        expectedOutputs.addItem(new String(out));
    }

    Difficulty getDifficulty() const { return difficulty; }
    const char* getTitle() const { return title.getString(); }
};

#endif