//#include "MyBot.h"
#include <dpp/dpp.h>

#include <iostream>
#include "BOT_TOKEN.cpp"

int main()
{
	/* Create bot cluster */
	//dpp::cluster bot(BOT_TOKEN);

	dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

	/* Output simple log messages to stdout */
	bot.on_log(dpp::utility::cout_logger());

	/* Register slash command here in on_ready */
	bot.on_ready([&bot](const dpp::ready_t& event)
	{
		/* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
		if (dpp::run_once<struct register_bot_commands>())
		{
			std::vector<dpp::slashcommand> commands
			{
				{ "ping", "Ping pong!", bot.me.id }
			};

			bot.global_bulk_command_create(commands);
		}
	});

	// The event is fired when someone issues your commands
	bot.on_slashcommand([](const dpp::slashcommand_t& event) -> dpp::task<void>
	{
		if (event.command.get_command_name() == "ping")
		{
			co_await event.co_reply("Pong!");
		}
		co_return;
	});



	/* The event is fired when the bot detects a message in any server and any channel it has access to. */
	bot.on_message_create([&bot](const dpp::message_create_t& event)
	{
		// Checks if the author of the message is from the bot itself.
		if (event.msg.author.is_bot())
		{
			return;
		}
		// See if the message contains the phrase we want to check for.
		// If there's at least a single match, we reply with a message.
		// DOES NOT CHECK IF IT IS FROM THE BOT ITSELF.
		
		std::string ChkTs = "what the ink";

		if (event.msg.content.find(ChkTs) != std::string::npos)
		{
			event.reply("Nice try, but I know you said \"" + ChkTs + "\!""", true);
		}
	});

	/* Start the bot */
	bot.start(dpp::st_wait);

	return EXIT_SUCCESS;
}