#include <regex>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <signal.h>

//forward declarations
void user_loop();
void interpret_text(std::string textj);
int eval_dice(std::string text); 

void ctrl_c_handler(int s) {
    std::cout << std::endl;
    exit(s);
}

int main() {
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = ctrl_c_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    srand(time(NULL));
    user_loop();
    return 0;
}

std::regex r_dice("[0-9]*d([2468]|10|12|20|100)((\\+[0-9]+)|(\\-[0-9]+))?(r[0-9]+)?");
std::regex r_repeat_dice("r[0-9]+");
std::regex r_pos_mod_dice("\\+[0-9]+");
std::regex r_neg_mod_dice("\\-[0-9]+");

void user_loop() {
    std::string prev_inp = "";

    while(true) {
        std::string inp = "";
        std::cout << "> ";
        std::cin >> inp;
        if(inp == "exit") exit(0);
        else if(inp == "r") {
            std::cout << prev_inp << std::endl;
            interpret_text(prev_inp);
        } else {
            interpret_text(inp);
            prev_inp = inp;
        }
    }
}

void interpret_text(std::string text) {
    if(regex_match(text, r_dice)) {
        int repeat = 1, mod = 0;

        if(regex_search(text, r_repeat_dice)) {
            std::size_t rpos = text.find("r");

            if(rpos != std::string::npos) {
                repeat = std::stoi(text.substr(rpos+1,text.length()));
                text = text.substr(0,rpos);
            }
        }

        if(regex_search(text, r_pos_mod_dice)) {
            std::size_t mod_pos = text.find("+");

            if(mod_pos != std::string::npos) {
                mod = std::stoi(text.substr(mod_pos+1,text.length()));
                text = text.substr(0,mod_pos);
            }
        } else if(regex_search(text, r_neg_mod_dice)) {
            std::size_t mod_pos = text.find("-");

            if(mod_pos != std::string::npos) {
                mod = -std::stoi(text.substr(mod_pos+1,text.length()));
                text = text.substr(0,mod_pos);
            }
        }

        for(int c = 0; c < repeat; c++) {
            std::cout << eval_dice(text)+mod << std::endl;
        }
    } else {
      std::cout << "?" << std::endl;
    }
}

int eval_dice(std::string text) {
    int dpos = text.find("d");
    int a = 1;
    int b = std::stoi(text.substr(dpos+1,text.length()-1));

    if(text.substr(0,dpos) != "") {
        a = std::stoi(text.substr(0,dpos));
    }

    int sum = 0;
    for(int c = 0; c < a; c++) {
        sum += rand() % b + 1;
    }

    return sum;
}
