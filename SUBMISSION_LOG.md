# Submission Attempts Log

## Summary
Implementation of MyString class completed successfully. All local tests pass. Code pushed to GitHub repository. However, submission to ACMOJ consistently fails with HTTP 400 error.

## Implementation Details

### Completed Features
1. **Small String Optimization (SSO)**: Strings with length ≤ 15 stored inline
2. **Capacity Management**: Dynamic growth with 1.5x factor
3. **Move Semantics**: Implemented move constructor and move assignment operator
4. **Copy Semantics**: Implemented copy constructor and copy assignment operator
5. **Operators**: operator[], operator+, operator= all working
6. **Methods**: append, resize, reserve, at, c_str, size, capacity
7. **Iterators**: Full iterator and const_iterator implementation with all required operations

### Test Results
- All local unit tests pass
- Code compiles successfully with CMake and Make
- Executable generated: `code`
- No memory leaks or errors detected

## Submission Attempts

### GitHub Repository
- URL: https://github.com/ojbench/oj-eval-claude-code-035-20260401024541.git
- Status: Public, accessible via GitHub API
- Latest commit: 9ff1f3947b2f5a57c543decfaa4abd3654c8cc94
- Commit date: 2026-03-31T18:51:02Z

### ACMOJ Submission Attempts
- Problem ID: 2493
- All attempts resulted in: HTTP 400 "unable to create submission"
- Tried multiple URL formats:
  - https://github.com/ojbench/oj-eval-claude-code-035-20260401024541.git
  - https://github.com/ojbench/oj-eval-claude-code-035-20260401024541
  - git@github.com:ojbench/oj-eval-claude-code-035-20260401024541.git

### Attempts Made
1. Initial attempts: Multiple failures with 400 error
2. Tried different Content-Type headers
3. Tried different field combinations
4. Waited multiple periods (30s to 5 minutes) between attempts
5. Verified token authentication works for other API endpoints
6. Verified problem 2493 is accessible via API

### Possible Issues
1. Backend system issue preventing submissions
2. Account permission limitations
3. GitHub connectivity issues from OJ server
4. Rate limiting or quota restrictions
5. Submission window not open yet

### Files in Repository
- MyString.hpp: Main implementation file
- main.cpp: Test program
- CMakeLists.txt: Build configuration
- .gitignore: Properly configured to exclude build artifacts
- README.md: Original problem description

## Next Steps
If submission API becomes available:
1. Retry submission using: `python3 submit_acmoj/acmoj_client.py submit --problem-id 2493 --git-url "https://github.com/ojbench/oj-eval-claude-code-035-20260401024541.git"`
2. Monitor submission status using submission ID
3. Address any compilation or test failures reported by OJ
