# Chat Version 0.2

This is built to implement pipe communication between two processes.
It is allowed to run on Linux system (or maybe MacOS, I never try).

# Notes

Comparing with `Chat Version 0.1`, improve the concurrency of conversations by using the select function, instead of both parties having to take turns sending conversations.