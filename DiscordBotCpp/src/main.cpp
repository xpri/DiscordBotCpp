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
				{ "ping", "Ping pong!", bot.me.id } //registers the command onto discord (?)
				,
				{ "embed", "I am testing commands.", bot.me.id }			// Must restart discord to work.
				,
				{ "quote", "Generate a random quote.", bot.me.id }
			};

			bot.global_bulk_command_create(commands);
		}
	});

	// The event is fired when someone issues your commands
	bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) -> dpp::task<void>			// You can only call one event.reply command once per slash command.
	{
		if (event.command.get_command_name() == "ping")
		{
			co_await event.co_reply("Pong!");
		}
		if (event.command.get_command_name() == "quote") {
			/* Reply to the user, but only let them see the response. */
			co_await event.co_reply(dpp::message("Hello! How are you today?").set_flags(dpp::m_ephemeral));			// Specifically the set_flags extension
		}
		else if (event.command.get_command_name() == "embed")
		{
			/* Create an embed */
			dpp::embed embed = dpp::embed()
				.set_color(dpp::colors::sti_blue)
				.set_title("Some name")
				.set_url("https://dpp.dev/")
				.set_author("Some name", "https://dpp.dev/", "https://dpp.dev/DPP-Logo.png")
				.set_description("Some description here")
				.set_thumbnail("https://dpp.dev/DPP-Logo.png")
				.add_field(
					"Regular field title",
					"Some value here"
				)
				.add_field(
					"Inline field title",
					"Some value here",
					true
				)
				.add_field(
					"Inline field title",
					"Some value here",
					true
				)
				.set_image("https://dpp.dev/DPP-Logo.png")
				.set_footer(
					dpp::embed_footer()
					.set_text("Some footer text here")
					.set_icon("https://dpp.dev/DPP-Logo.png")
				)
				.set_timestamp(time(0));

			/* Create a message with the content as our new embed. */
			dpp::message msg(event.command.channel_id, embed);

			/* Reply to the user with the message, containing our embed. */
			co_await event.co_reply(msg);


			/* Then send a follow-up message */
			bot.message_create(dpp::message(event.command.channel_id, "Did it give an embed?"));
		}
		else if (event.command.get_command_name() == "quote")
		{
			event.reply("Hello World!");
			co_await event.co_reply("PLACEHOLDER");
		}
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
			event.reply("Nice try, but I know you said \"" + ChkTs + "\"!", true);
		}
	});

	/* Start the bot */
	bot.start(dpp::st_wait);

	return EXIT_SUCCESS;
}