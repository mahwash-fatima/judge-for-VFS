#ifndef IEVALUATABLE_H
#define IEVALUATABLE_H 
#include "Verdict.h"
 
class IEvaluatable {
public:
    // Run the submission against all test cases
    // and return a Verdict (AC / WA / CE / TLE)
    virtual Verdict evaluate() = 0;
 
    virtual ~IEvaluatable() {}
};
 
#endif