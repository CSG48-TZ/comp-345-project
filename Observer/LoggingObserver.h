#pragma once
#include <list>
#include <string>
using namespace std;

class Iloggable {
public:
	Iloggable();
	virtual ~Iloggable();
	virtual string stringToLog() = 0;
};

class Observer {
public:
	virtual ~Observer();
	virtual void update(Iloggable* log) = 0;
protected:
	Observer();
};

class Subject {
public:
	Subject();
	virtual ~Subject();
	virtual void notify(Iloggable* o);
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
private:
	list<Observer*> *_observers;
};

class LogObserver : public Observer {
public:
	LogObserver();
	~LogObserver();
	LogObserver(Subject* s);
	void update(Iloggable* log);
private:
	Subject* _subject;
};

