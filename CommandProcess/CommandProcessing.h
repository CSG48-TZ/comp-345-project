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
    Command(const string& name);
    Command(const string& name, const string& effect);
    Command(const Command& anotherCommand);
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
    void saveCommand(const string& input, const string& effect="Null");
    string& readCommand() const;
    string& valCommand(const string& command, const string& currentState) const;
public:
    ~CommandProcessor();
    string& validate(Command* const command, const string& currentState);
    Command* getCommand();
};

class FileLineReader {
private:
    string fileName;
    ifstream myfile;
public:
    FileLineReader();
    FileLineReader(string& fileName);
    string& readLineFromFile();
    string getFileName() const { return fileName; }
};

class FileCommandProcessorAdapter : public CommandProcessor {
private:
    FileLineReader* flr;
    string& readCommand() const;
public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(std::string& fileName);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);
};