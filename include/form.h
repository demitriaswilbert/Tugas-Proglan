#ifndef FILLFORM_H
#define FILLFORM_H

#include <bits/stdc++.h>
#include <regex>

class Form {
    const char* prompt;
    std::string* buf;
    const char* regex;
    public:
    Form(const char* prompt, std::string *buf, const char* regex = NULL) 
        : prompt(prompt), buf(buf), regex(regex) {}
    Form(const std::string& prompt, std::string *buf, const char* regex = NULL) 
        : prompt(prompt.c_str()), buf(buf), regex(regex) {}
    int eval();
};

bool fillSingle(Form form);
bool fillForm(std::vector<Form>& vForm);

#endif// FILLFORM_H