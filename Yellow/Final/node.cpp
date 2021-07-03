#include "node.h"
#include <iostream>
using namespace std;
bool EmptyNode::Evaluate(const Date& d, const string& ev) const {
	return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& new_cmp, const Date& new_date)
	: cmp(new_cmp), date(new_date) {}

bool DateComparisonNode::Evaluate(const Date& d, const string& ev) const {
	if (cmp == Comparison::Less) {
		return date > d;
	}
	else if (cmp == Comparison::LessOrEqual) {
		return date >= d;
	}
	else if (cmp == Comparison::Greater) {
		return date < d;
	}
	else if (cmp == Comparison::GreaterOrEqual) {
		return date <= d;
	}
	else if (cmp == Comparison::Equal) {
		return date == d;
	}
	else if (cmp == Comparison::NotEqual) {
		return date != d;
	}
	else {
		throw logic_error("Wrong comparison operator");
	}

}

EventComparisonNode::EventComparisonNode(const Comparison& new_cmp, const string& new_event)
	: cmp(new_cmp), event(new_event) {}


bool EventComparisonNode::Evaluate(const Date& d, const string& ev) const {
	if (cmp == Comparison::Equal) {
		return event == ev;
	}
	else if (cmp == Comparison::Greater) {
		return event < ev;
	}
	else if (cmp == Comparison::GreaterOrEqual) {
		return event <= ev;
	}
	else if (cmp == Comparison::Less) {
		return event > ev;
	}
	else if (cmp == Comparison::LessOrEqual) {
		return event >= ev;
	}
	else if (cmp == Comparison::NotEqual) {
		return event != ev;
	}
	else {
		throw logic_error("Wrong comparison operator");
	}

}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation& new_oper,
	const shared_ptr<Node>& new_left,
	const shared_ptr<Node>& new_right)
	: oper(new_oper), left(new_left), right(new_right) {}


bool LogicalOperationNode::Evaluate(const Date& d, const string& ev) const {
	if (oper == LogicalOperation::And) {
		return (left->Evaluate(d, ev) && right->Evaluate(d, ev));
	}
	else if (oper == LogicalOperation::Or) {
		return (left->Evaluate(d, ev) || right->Evaluate(d, ev));
	}
	else {
		throw logic_error("Wrong logic operator");
	}
}