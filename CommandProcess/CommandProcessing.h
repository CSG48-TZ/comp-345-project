#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "../Observer/LoggingObserver.h"
using namespace std;

class Command : public Iloggable, public Subject{
private:
    string commandName;
    string commandEffect;

public:
    Command();
    Command(string name);
    Command(string name, string effect);
    Command(Command* anotherCommand);
    ~Command();
    Command& operator=(Command& other);
    friend ostream& operator<<(ostream& out, Command& const command);

    string getCommandName() const;
    string getCommandEffect() const;
    void saveEffect(const std::string& effect);
    void saveName(const std::string& name);
    string stringToLog();
};

class CommandProcessor : public Iloggable, public Subject {
private:
    vector<Command*> commands;
protected:
    void saveCommand(string input, string effect="Null");
    virtual string readCommand() const;
    string valCommand(string command, string currentState) const;
public:
    CommandProcessor();
    CommandProcessor(CommandProcessor* cmdPcs);
    CommandProcessor& operator=(CommandProcessor& other);
    friend ostream& operator<<(ostream& out, CommandProcessor& const command);
    virtual ~CommandProcessor();

    string validate(Command* command, string currentState);
    Command* getCommand();
    string stringToLog();
};

class FileLineReader {
private:
    string fileName;
    vector<string> commandsBuffer;
    int currentCommandIndex;
public:
    FileLineReader();
    FileLineReader(string fileName);
    FileLineReader(FileLineReader* flrder);
    FileLineReader& operator=(FileLineReader& other);
    friend ostream& operator<<(ostream& out, FileLineReader& const flr);
    ~FileLineReader();
    void readCommands(string fileName);
    string readLineFromFile();
    string getFileName() const { return fileName; }
};

class FileCommandProcessorAdapter : public CommandProcessor {
private:
    FileLineReader* flr;
protected:
    string readCommand() const;
public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(FileLineReader* reader);
    FileCommandProcessorAdapter(FileCommandProcessorAdapter* other);
    FileCommandProcessorAdapter& operator=(FileCommandProcessorAdapter& other);
    friend ostream& operator<<(ostream& out, FileCommandProcessorAdapter& const fprs);
    ~FileCommandProcessorAdapter();
};