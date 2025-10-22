Hellllooo!!!
This took a long time to setup...
Make sure you have everything correct in all the files. All you have to do is press (on windows) ctrl + s on the CMakeLists.txt and it will recompile the
entire project in CMAke. Then press build on the top ribbon thne build all. After build has completed then you can run the DiscordBotCPP.exe.

On the first compilation of the CMake it will take a long time. Just be patient.

If you want to change any CMake settings, go to Project -> (on the bottom) CMake settings for $(PROJECT_NAME).

Will update this on 10/22/25 @ 5:56PM to make it public on github.
Doing so will require me to reset my discord token and add the config file to .gitignore
To have the code not break if you decide to clone/fork the repo, you must make a config.cpp file in the /src folder.

And inside it place the '  const std::string BOT_TOKEN ="[your bot token]"  '

After that you are done!
