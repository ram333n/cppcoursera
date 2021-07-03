#pragma once
#include "date.h"
#include <memory>

using namespace std;

enum class LogicalOperation {
	Or,
	And
};


enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

class Node {
public:
	virtual bool Evaluate(const Date& d, const string& ev) const = 0;
};


class EmptyNode : public Node {
public:
	bool Evaluate(const Date& d, const string& ev) const;
};


class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& new_cmp, const Date& new_date);
	bool Evaluate(const Date& d, const string& ev) const;

private:
	const Comparison cmp;
	const Date date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& new_cmp, const string& new_event);

	bool Evaluate(const Date& d, const string& ev) const;

private:
	const Comparison cmp;
	const string event;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& new_oper, const shared_ptr<Node>& new_left, const shared_ptr<Node>& new_right);

	bool Evaluate(const Date& d, const string& ev) const;
private:
	const shared_ptr<Node> left, right;
	const LogicalOperation oper;
};


