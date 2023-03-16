#include "CommandProcessing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

/*
	Following is implementation of Command class
*/
// Default Constructor
Command::Command() : commandName("Empty Command"), commandEffect("No Command") {}
// General Constructors
Command::Command(string name) : commandName(name), commandEffect("") {}
Command::Command(string name, string effect) : commandName(name), commandEffect(effect) {}
// Copy Constructor
Command::Command(Command* anotherCommand) : commandName(anotherCommand->getCommandName()), commandEffect(anotherCommand->getCommandEffect()) {}
// Assignment Operator
Command& Command::operator=(Command& other) {
	this->commandName = other.getCommandName();
	this->commandEffect = other.getCommandEffect();
	return *this;
}
// Insertion Operator
ostream& operator<<(ostream& out, Command& command) {
	out <<"Command: " << command.getCommandName() << "; \nCommand Effect: " << command.getCommandEffect() << endl;
	return out;
}
// Deconstructor
Command::~Command() {
	this->commandName = "";
	this->commandEffect = "";
}
// Accessor for commandName
string Command::getCommandName() const { return commandName; }
// Accessor for commandEffect
string Command::getCommandEffect() const { return commandEffect; }
// Mutator for commandEffect
void Command::saveEffect(const std::string& effect) { commandEffect = effect; }
// Mutator for commandName
void Command::saveName(const std::string& name) { commandName = name; }


/*
	Following is implementation of CommandProcessor class
*/
//Default Constructor
CommandProcessor::CommandProcessor() {}
// Copy Constructor
CommandProcessor::CommandProcessor(CommandProcessor* cmdPcs) {
	for (int i = 0; i < cmdPcs->commands.size(); i++) {
		Command* command = new Command(cmdPcs->commands[i]);
		this->commands.push_back(command);
	}
}
// Assignment Operator
CommandProcessor& CommandProcessor::operator= (CommandProcessor& another) {
	this->commands.clear();
	for (int i = 0; i < another.commands.size(); i++) {
		Command* command = new Command(another.commands[i]);
		this->commands.push_back(command);
	}
	return *this;
}
// Insertion Operator
ostream& operator<<(ostream& out, CommandProcessor& const cmdPcs) {
	out << "The commands in the command processor at the current stage shown as follows:";
	for (int i = 0; i < cmdPcs.commands.size(); i++) {
		out << "\n" << * (cmdPcs.commands[i]);
	}
	out << "\n" << endl;
	return out;
}
// Deconstructor
CommandProcessor::~CommandProcessor() {
	for (int i = 0; i < this->commands.size(); i++) {
		delete commands[i];
		commands[i] = NULL;
	}
	this->commands.clear();
}
// Add new command to the command processor
void CommandProcessor::saveCommand(string input, string effect) {
	Command* newCommand = new Command(input, effect);
	this->commands.push_back(newCommand);
}
// Read command line from the console
string CommandProcessor::readCommand() const {
	cout << "\nPlease Enter command or enter nothing to exit: ";
	string command;
	getline(cin, command);
	// Allow users to terminate the program by inputting E
	if (command == "E") {
		cout << "Terminated" << endl;
		exit(0);
	}
	return command;
}
// Provides a public method to other objects for using the command processor
Command* CommandProcessor::getCommand() {
	string command = this->readCommand();
	if (command == "") {
		return NULL;
	}else{
		this->saveCommand(command);
		return this->commands.back();
	}
	
}
// Validate if the command is valid at the current state and return the next state
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
// Check if the command is valid in the current game state. If the command is not valid, a corresponding error message should be saved in the effect of the command.
string CommandProcessor::validate(Command* command, string currentState) {
	// Extract and split the command details from the input line
	string commandName = command->getCommandName();
	istringstream iss(commandName);
	vector<string> result;
	string word;
	while (getline(iss, word, ' ')) {
		result.push_back(word);
	}
	string behavior = result[0];

	// Check the validaty of the command, get the next state, and save the effect
	string nextState = this->valCommand(behavior, currentState);
	if (nextState == "") {
		command->saveEffect("Error Message: Invalid command. ");
	}
	else {
		string effect = "The state of Game Engine change from " + currentState + " to " + nextState;
		command->saveEffect(effect);
	}
	return nextState;
}

/*
	Following is implementation of FileLineReader class
*/
// Default Constructor
FileLineReader::FileLineReader() : fileName("default.txt"), currentCommandIndex(0) { 
	this->readCommands(this->fileName); 
}
// General Constructor
FileLineReader::FileLineReader(string fileName) : fileName(fileName), currentCommandIndex(0) { 
	this->readCommands(this->fileName); 
}
// Copy Constructor
FileLineReader::FileLineReader(FileLineReader* flr) {
	this->fileName = flr->fileName;
	this->commandsBuffer.clear();
	for (int i = 0; i < flr->commandsBuffer.size(); i++) {
		this->commandsBuffer.push_back(flr->commandsBuffer[i]);
	}
	this->currentCommandIndex = flr->currentCommandIndex;
}
// Assignment Operator
FileLineReader& FileLineReader::operator=(FileLineReader& flr) {
	this->fileName = flr.fileName;
	this->commandsBuffer.clear();
	for (int i = 0; i < flr.commandsBuffer.size(); i++) {
		this->commandsBuffer.push_back(flr.commandsBuffer[i]);
	}
	this->currentCommandIndex = flr.currentCommandIndex;
	return *this;
}
// Contrutor Operator
ostream& operator<<(ostream& out, FileLineReader& const flr) {
	out << "Reading file: " << flr.fileName;
	out << "\nThe commands in the file are shown as follows:";
	for (int i = 0; i < flr.commandsBuffer.size(); i++) {
		out << "\n" << i << ". " << flr.commandsBuffer[i];
	}
	out << "\nCurrently, command No. " << flr.currentCommandIndex << " is reading by the file processor." << endl;
	return out;
}
// Deconstructor
FileLineReader::~FileLineReader() {
	this->fileName = "";
	this->commandsBuffer.clear();
	this->currentCommandIndex = 0;
}
// Read all commands from an existing file and store them to the buffer
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
// Allow a file processor to read commands line by line
string FileLineReader::readLineFromFile() {
	if (this->currentCommandIndex >= this->commandsBuffer.size()) {
		return ""; // Return empty string if all commands have been read
	}
	
	string command = this->commandsBuffer[this->currentCommandIndex];

	cout << "current command index" << currentCommandIndex << "; current command " << command << endl;

	this->currentCommandIndex++;
	return command;
}

/*
	Following is implementation of FileCommandProcessorAdapter class
*/
// Default Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter() : CommandProcessor(){
	this->flr = new FileLineReader();
}
// General Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* reader) : CommandProcessor() {
	this->flr = reader;
}
// Copy Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileCommandProcessorAdapter* other) : CommandProcessor() {
	this->flr = new FileLineReader(other->flr);
}
// Deconstructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
	delete flr;
	flr = NULL;
}
// Assignment Operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(FileCommandProcessorAdapter& other){
	this->flr = new FileLineReader(other.flr);
	return *this;
}
// Insertion Operator
ostream& operator<<(ostream& out, FileCommandProcessorAdapter& const fprs) {
	out << *(fprs.flr) << endl;
	return out;
}
// Override the readCommand() method in Command Processor
string FileCommandProcessorAdapter::readCommand() const {
	string command = this->flr->readLineFromFile();
	return command;
}

