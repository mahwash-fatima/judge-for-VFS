#ifndef VERDICT_H
#define VERDICT_H
 
// Verdict.h
// ─────────────────────────────────────────────
// Defines the possible outcomes of evaluating
// a user's code submission against test cases.
//
// Kept in its own file so IEvaluatable.h,
// Submission.h, and the UI can all include it
// without pulling in anything heavy.
// ─────────────────────────────────────────────
 
enum Verdict {
    AC,   // Accepted       — all test cases passed
    WA,   // Wrong Answer   — output didn't match expected
    CE,   // Compile Error  — code failed to compile
    TLE   // Time Limit     — reserved for future use
};
 
// Helper: convert Verdict to a readable string
// Used by the UI results screen
inline const char* verdictToString(Verdict v) {
    if (v == AC)  return "Accepted";
    if (v == WA)  return "Wrong Answer";
    if (v == CE)  return "Compilation Error";
    if (v == TLE) return "Time Limit Exceeded";
    return "Unknown";
}
 
#endif