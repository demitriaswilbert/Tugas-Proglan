#include "include/form.h"

int Form::eval() {
    std::cout << prompt;
    std::fflush(stdin);
    std::getline(std::cin, *buf); 
    if (*buf == "kembali") {
        return 0;
    }
    if (regex == NULL) return 2;
    return (((int)std::regex_match(*buf, std::regex(regex))) + 1);
}

bool fillSingle(Form form) {
    while (true) {
        int result = form.eval();
        if(result == 2) 
            break;
        if(result == 1) 
            std::cout << "[ERROR] Format Salah!" << std::endl;
        if(result == 0) {
            std::cout << "Terbatalkan" << std::endl;
            return false;
        }
    }
    return true;
}

bool fillForm(std::vector<Form>& vForm) {
    for (Form& i : vForm) {
        if (!fillSingle(i))
            return false;
    }
    return true;
}