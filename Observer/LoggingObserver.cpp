#include "LoggingObserver.h"
#include <fstream>
#include <iostream>

namespace {
	const string FILE_NAME = "gamelog.txt";
}
/*
Implementation for Observer
*/
Observer::Observer(){}
Observer::~Observer(){}

/*
Implementation for Subject
*/
Subject::Subject() {
	this->_observers = new list<Observer*>;
}
Subject::~Subject() {
	delete _observers;
}
void Subject::attach(Observer* o) {
	this->_observers->push_back(o);
};
void Subject::detach(Observer* o) {
	this->_observers->remove(o);
};
void Subject::notify(Iloggable* log) {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update(log);
};

/*
Implementation for Iloggable
*/
Iloggable::Iloggable(){}
Iloggable::~Iloggable(){}

/*
Implementation for LogObserver
*/
LogObserver::LogObserver(){}
LogObserver::LogObserver(Subject* s) {
	this->_subject = s;
	_subject->attach(this);
}
LogObserver::~LogObserver() {
	delete _subject;
	this->_subject->detach(this);
}

void LogObserver::update(Iloggable* log) {
	string message = log->stringToLog();
	fstream file;
	file.open(FILE_NAME, ios::app);
	if (!file.is_open()) {
		cout << "Failed to open file!" << std::endl;
		exit(0);
	}
	cout << "Start writing {" << message << "} to the file " << FILE_NAME << endl;
	file << message << endl;
	file.close();
}
