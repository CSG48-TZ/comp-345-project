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
Observer::Observer(Observer* o) { (*this) = (*o); }
Observer::~Observer(){}
Observer& Observer::operator=(Observer& other) { 
	(*this) = other; 
	return (*this);
}
ostream& operator<<(ostream& out, Observer& command) {
	out << "An Observer created." << endl;
	return out;
}

/*
Implementation for Subject
*/
Subject::Subject() {
	this->_observers = new list<Observer*>;
}
Subject::Subject(Subject* sub) {
	this->_observers = sub->_observers;
}
Subject& Subject::operator=(Subject& other) {
	this->_observers = other._observers;
	return (*this);
}
ostream& operator<<(ostream& out, Subject& sub) {
	out << "The Subject has " << sub._observers->size() << " Observers." << endl;
	return out;
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
Iloggable::Iloggable(Iloggable* log) { (*this) = (*log); }
Iloggable& Iloggable::operator=(Iloggable& other) { 
	(*this) = other; 
	return (*this);
}
ostream& operator<<(ostream& out, Iloggable& command) {
	out << "An Iloggable created." << endl;
	return out;
}

/*
Implementation for LogObserver
*/
LogObserver::LogObserver(){
	this->_subject = NULL;
}

LogObserver::LogObserver(Subject* s) {
	this->_subject = s;
	_subject->attach(this);
}
LogObserver::~LogObserver() {
	this->_subject->detach(this);
}
LogObserver::LogObserver(LogObserver* l) {
	this->_subject = l->_subject;
}
LogObserver& LogObserver::operator=(LogObserver& other) {
	this->_subject = other._subject;
	return (*this);
}
ostream& operator<<(ostream& out, LogObserver& o) {
	out << "LogObserver related to Subject: " << (*o._subject) << endl;
	return out;
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
