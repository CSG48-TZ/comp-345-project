#include "CommandProcessing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

/*
	Following is implementation of Command class
*/
Command::Command() : commandName("Empty Command"), commandEffect("No Command") {}
Command::Command(string name) : commandName(name), commandEffect("") {}
Command::Command(string name, string effect) : commandName(name), commandEffect(effect) {}
Command::Command(Command& anotherCommand) : commandName(anotherCommand.getCommandName()), commandEffect(anotherCommand.getCommandEffect()) {}
Command& Command::operator=(Command& other) {
	this->commandName = other.getCommandName();
	this->commandEffect = other.getCommandEffect();
	return *this;
}

ostream& operator<<(ostream& out, Command& command) {
	out <<"Command: " << command.getCommandName() << "; \nCommand Effect: " << command.getCommandEffect() << endl;
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
	for (int i = 0; i < this->commands.size(); i++) {
		delete commands[i];
		commands[i] = NULL;
	}
	this->commands.clear();
}
void CommandProcessor::saveCommand(string input, string effect) {
	Command* newCommand = new Command(input, effect);
	this->commands.push_back(newCommand);
}
string CommandProcessor::readCommand() const {
	string command;
	getline(cin, command);
	if (command == "E") {
		cout << "Terminated" << endl;
		exit(0);
	}
	return command;
}
Command* CommandProcessor::getCommand() {
	string command = this->readCommand();
	if (command == "") {
		return NULL;
	}else{
		this->saveCommand(command);
		return this->commands.back();
	}
	
}
string CommandProcessor::valCommand(string command, string currentState) const {
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
string CommandProcessor::validate(Command* command, string currentState) {
	string commandName = command->getCommandName();
	istringstream iss(commandName);
	vector<string> result;
	string word;
	while (getline(iss, word, ' ')) {
		result.push_back(word);
	}
	string nextState = this->valCommand(result[0], currentState);
	if (nextState == "") {
		command->saveEffect("Error Message: Invalid command. ");
	}
	else {
		string effect = "The state of Game Engine change from " + currentState + " to " + nextState;
		command->saveEffect(effect);
	}
	return nextState;
}


FileLineReader::FileLineReader() : fileName("default.txt"), currentCommandIndex(0) { 
	this->readCommands(this->fileName); 
}
FileLineReader::FileLineReader(string fileName) : fileName(fileName), currentCommandIndex(0) { 
	this->readCommands(this->fileName); 
}
FileLineReader::~FileLineReader() {
	this->fileName = "";
	this->commandsBuffer.clear();
	this->currentCommandIndex = 0;
}

void FileLineReader::readCommands(string fileName) {
	ifstream myfile;
	
	myfile.open(fileName);

	if (myfile.fail()) {
		cout << "File not found" << endl;
		exit(0);
	}

	while (!myfile.eof()) {
		string command;
		getline(myfile, command, '\n');
		this->commandsBuffer.push_back(command);
	}
	myfile.close();
}

string FileLineReader::readLineFromFile() {
	if (this->currentCommandIndex >= this->commandsBuffer.size()) {
		return ""; // Return empty string if all commands have been read
	}
	
	string command = this->commandsBuffer[this->currentCommandIndex];

	cout << "current command index" << currentCommandIndex << "; current command " << command << endl;

	this->currentCommandIndex++;
	return command;
}


FileCommandProcessorAdapter::FileCommandProcessorAdapter() : CommandProcessor(){
	this->flr = new FileLineReader();
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string fileName) {
	this->flr = new FileLineReader(fileName);
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other) {
	this->flr = other.flr;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
	delete flr;
	flr = NULL;
}

string FileCommandProcessorAdapter::readCommand() const {
	string command = this->flr->readLineFromFile();
	return command;
}

