#include "CommandProcessing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
using namespace std;

/*
	Following is implementation of Command class
*/
Command::Command() : commandName("Empty Command"), commandEffect("No Command") {}
Command::Command(const std::string& name) : commandName(name), commandEffect("") {}
Command::Command(const string& name, const std::string& effect) : commandName(name), commandEffect(effect) {}
Command::Command(const Command& anotherCommand) : commandName(anotherCommand.getCommandName()), commandEffect(anotherCommand.getCommandEffect()) {}
Command& Command::operator=(Command& other) {
	this->commandName = other.getCommandName();
	this->commandEffect = other.getCommandEffect();
	return *this;
}

ostream& operator<<(ostream& out, Command& command) {
	out <<command.getCommandName() << ", " << command.getCommandEffect() << endl;
	return out;
}

Command::~Command() {
	this->commandName = "";
	this->commandEffect = "";
}


/*
	Following is implementation of CommandProcessor class
*/
CommandProcessor::~CommandProcessor() {
	for (Command* command : this->commands) {
		delete command;
		command = NULL;
	}
}
void CommandProcessor::saveCommand(const string& input, const string& effect = "Null") {
	Command* newCommand = new Command(input, effect);
	this->commands.push_back(newCommand);
}
string CommandProcessor::readCommand() const {
	string command;
	// cout << "\nPlease Enter a command: ";
	getline(cin, command);
	return command;
}
Command* CommandProcessor::getCommand() {
	string command = this->readCommand();
	this->saveCommand(command);
	return this->commands.back();
}
string& CommandProcessor::valCommand(const string& command, const string& currentState) const {
	string nextState = "";
	if (command == "validatemap" && currentState == "maploaded") {
		nextState = "mapvalidated";
	}else if (command == "gamestart" && currentState == "playersadded") {
		nextState = "assignreinforcement";
	}else if (command == "replay" && currentState == "win") {
		nextState = "start";
	}else if (command == "quit" && currentState == "win") {
		nextState = "exit program";
	}else if (command == "loadmap" && (currentState == "maploaded" || currentState == "start")) {
		nextState = "maploaded";
	}
	else if (command == "addplayer" && (currentState == "mapvalidated" || currentState == "playersadded ")) {
		nextState = "playersadded";
	}

	return nextState;
}
string& CommandProcessor::validate(Command* const command, const string& currentState) {
	string commandName = command->getCommandName();
	istringstream iss(commandName);
	std::vector<std::string> result;
	std::string word;
	while (getline(iss, word, ' ')) {
		result.push_back(word);
	}
	string nextState = this->valCommand(result[0], currentState);
	if (nextState == "") {
		command->saveEffect("Error Message: Invalid command. ");
	}
	return nextState;
}


FileLineReader::FileLineReader() : fileName("default.txt"), myfile(fileName){
	while (!myfile.good()) {
		cout << fileName << " does not exist. Please input another file name:" << endl;
		cin >> fileName;
		myfile.open(fileName);
	}
}
FileLineReader::FileLineReader(string& fileName) {
	this->fileName = fileName;
	myfile.open(this->getFileName());
	while (!myfile.good()) {
		cout << fileName << " does not exist. Please input another file name:" << endl;
		cin >> fileName;
		myfile.open(fileName);
	}
}
FileLineReader::~FileLineReader() {
	this->fileName = "";
	if (this->myfile.is_open()) {
		this->myfile.close();
	}
}
string& FileLineReader::readLineFromFile() {
	string command = "";
	if (myfile.eof()) {
		cout << "All commands have been read. No new command can be read." << endl;
		myfile.close();
	}
	else {
		getline(myfile, command, '\n');
	}
	return command;
}


FileCommandProcessorAdapter::FileCommandProcessorAdapter() : CommandProcessor(){
	this->flr = new FileLineReader();
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string& fileName) {
	this->flr = new FileLineReader(fileName);
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter() {

}