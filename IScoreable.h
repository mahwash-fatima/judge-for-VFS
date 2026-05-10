#ifndef ISCOREABLE_H
#define ISCOREABLE_H
 
class IScoreable {
public:
    // Compute and return the final score as an integer
    virtual int calcScore() = 0;
 
    virtual ~IScoreable() {}
};
 
#endif