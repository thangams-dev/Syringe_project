#include "command_parser.hpp"
#include "pump_state_machine.hpp"
#include <cstring>

void commandparser::process_command(const char* word) {
    if(strncmp(word, "start", 5) == 0) {
        Motor->start();
    }
    else if(strncmp(word, "stop", 4) == 0) {
        Motor->stop();
    }
    else if(strncmp(word, "pause", 5) == 0) {
        Motor->pause();
    }
    else if(strncmp(word, "setrate", 7) == 0) {
        float hr = geta.get_time_hr();
        if(hr > 0.0F) {
            Motor->setrate(geta.get_vol_ml() / hr);
        }
    }
}   