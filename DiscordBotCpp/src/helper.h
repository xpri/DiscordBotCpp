#ifndef HELPER_H
#define HELPER_H

#include <dpp/dpp.h>
#include <string>

// Function declaration
dpp::task<std::string> get_quote(dpp::cluster& bot);

#endif