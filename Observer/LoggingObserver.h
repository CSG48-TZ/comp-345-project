#pragma once
#include <list>
#include <string>
using namespace std;

class Iloggable {
public:
	Iloggable();
	virtual ~Iloggable();
	Iloggable(Iloggable* log);
	Iloggable& operator=(Iloggable& other);
	friend ostream& operator<<(ostream& out, Iloggable& const command);

	virtual string stringToLog() = 0;
};

class Observer {
public:
	virtual ~Observer();
	virtual void update(Iloggable* log) = 0;
	Observer& operator=(Observer& other);
	friend ostream& operator<<(ostream& out, Observer& const command);
protected:
	Observer();
	Observer(Observer* o);
};

class Subject {
public:
	Subject();
	Subject(Subject* s);
	Subject& operator=(Subject& other);
	friend ostream& operator<<(ostream& out, Subject& const command);
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
	LogObserver(LogObserver* l);
	LogObserver& operator=(LogObserver& other);
	friend ostream& operator<<(ostream& out, LogObserver& const command);

	void update(Iloggable* log);
private:
	Subject* _subject;
};

