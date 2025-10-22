#ifndef HELPER_H
#define HELPER_H

#include <dpp/dpp.h>
#include <string>

// Function declaration
dpp::task<std::string> get_quote(dpp::cluster& bot);
dpp::task<std::string> get_fact(dpp::cluster& bot);
dpp::task<std::string> get_cat_image(dpp::cluster& bot);
dpp::task<std::string> ask_gemini(dpp::cluster& bot, const std::string& prompt);

#endif