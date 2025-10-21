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

    if (result.status == 200) {
        try {
            // Parse JSON - similar to response.json()
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