#include <iostream>
#include <dpp/dpp.h>
#include <nlohmann/json.hpp>

#include "helper.h"

// Function to fetch quote
dpp::task<std::string> get_quote(dpp::cluster& bot)
{
    // Make API request - similar to requests.get()
    dpp::http_request_completion_t result = co_await bot.co_request(
        "https://zenquotes.io/api/random",
        dpp::m_get
    );

    if (result.status == 200)
    {
        try
        {
            // Parse JSON
            auto json_data = nlohmann::json::parse(result.body);

            // Extract quote and author
            std::string quote = json_data[0]["q"].get<std::string>();
            std::string author = json_data[0]["a"].get<std::string>();

            // Combine quote and author
            co_return quote + " -" + author;
        }
        catch (const std::exception& e) {
            co_return "Error parsing quote: " + std::string(e.what());
        }
    }
    else {
        co_return "Failed to fetch quote. API returned: " + std::to_string(result.status);
    }
}
dpp::task<std::string> get_fact(dpp::cluster& bot)
{
    dpp::http_request_completion_t result = co_await bot.co_request(
        "https://uselessfacts.jsph.pl/api/v2/facts/random",
        dpp::m_get
    );

    if (result.status == 200)
    {
        try
        {
            // Parses
            auto json_data = nlohmann::json::parse(result.body);
            // Detects text from json
            std::string fact = json_data["text"].get<std::string>();
            co_return fact;
        }
        catch (const std::exception& e) {
            co_return "Error parsing fact: " + std::string(e.what());
        }
    }
    else {
        co_return "Failed to fetch fact. API returned: " + std::to_string(result.status);
    }
}
dpp::task<std::string> get_cat_image(dpp::cluster& bot)
{
    dpp::http_request_completion_t result = co_await bot.co_request(
        "https://api.thecatapi.com/v1/images/search",
        dpp::m_get
    );

    if (result.status == 200) {
        try {
            auto json_data = nlohmann::json::parse(result.body);
            // The API returns an array, so we get the first element
            std::string image_url = json_data[0]["url"].get<std::string>();
            co_return image_url;
        }
        catch (const std::exception& e) {
            co_return "Error parsing cat image: " + std::string(e.what());
        }
    }
    else {
        co_return "Failed to fetch cat image. API returned: " + std::to_string(result.status);
    }
}
//dpp::task<std::string> ask_gemini(dpp::cluster& bot, const std::string& prompt)
//{
//    // Put code here
//}