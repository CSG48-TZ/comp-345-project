#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Command {
private:
    string commandName;
    string commandEffect;

public:
    Command();
    Command(string name);
    Command(string name, string effect);
    Command(Command& anotherCommand);
    ~Command();
    Command& operator=(Command& other);
    friend ostream& operator<<(ostream& out, Command& const command);

    string getCommandName() const { return commandName; }
    string getCommandEffect() const { return commandEffect; }
    void saveEffect(const std::string& effect) { commandEffect = effect; }
    void saveName(const std::string& name) { commandName = name; }
};

class CommandProcessor {
private:
    vector<Command*> commands;
    void saveCommand(string input, string effect="Null");
    string readCommand() const;
    string valCommand(string command, string currentState) const;
public:
    ~CommandProcessor();
    string validate(Command* command, string currentState);
    Command* getCommand();
};

class FileLineReader {
private:
    string fileName;
    vector<string> commandsBuffer;
    int currentCommandIndex;
public:
    FileLineReader();
    FileLineReader(string fileName);
    ~FileLineReader();
    void readCommands(string fileName);
    string readLineFromFile();
    string getFileName() const { return fileName; }
};

class FileCommandProcessorAdapter : public CommandProcessor {
private:
    FileLineReader* flr;
    string readCommand() const;
public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(string fileName);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);
    ~FileCommandProcessorAdapter();
};