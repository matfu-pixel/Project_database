#include "node.h"

Node::Node() = default;
EmptyNode::EmptyNode() = default;

bool EmptyNode::Evaluate(const Date date, const string event) {
    return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, Date date) : c(cmp), d(date) {
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string event) : c(cmp), e(event) {
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation cmp, shared_ptr<Node> left, shared_ptr<Node>right) : c(cmp), l(left), r(right) {
}

bool DateComparisonNode::Evaluate(const Date date, const string event) {
    switch (c) {
        case Comparison::Less:
            if (date < d) return true;
            else return false;
            break;
        case Comparison::LessOrEqual:
            if (date < d || date == d) return true;
            else return false;
            break;
        case Comparison::Greater:
            if (d < date) return true;
            else return false;
            break;
        case Comparison::GreaterOrEqual:
            if (d < date || d == date) return true;
            else return false;
            break;
        case Comparison::Equal:
            if (d == date) return true;
            else return false;
        case Comparison::NotEqual:
            if (d != date) return true;
            else return false;
    }
    return true;
}

bool EventComparisonNode::Evaluate(const Date date, const string event) {
	switch (c) {
		case Comparison::Less:
			if (event < e) return true;
			else return false;
			break;
		case Comparison::LessOrEqual:
			if (event < e || event == e) return true;
			else return false;
			break;
		case Comparison::Greater:
			if (e < event) return true;
			else return false;
			break;
		case Comparison::GreaterOrEqual:
			if (e < event || e == event) return true;
			else return false;
			break;
		case Comparison::Equal:
			if (e == event) return true;
			else return false;
		case Comparison::NotEqual:
			if (e != event) return true;
			else return false;
	    }
    return true;
}

bool LogicalOperationNode::Evaluate(const Date date, const string event) {
    if (c == LogicalOperation::And) {
        int a = l->Evaluate(date, event);
        int b = r->Evaluate(date, event);
        return (bool)(a & b);
    }
    else if (c == LogicalOperation::Or) {
        int a = l->Evaluate(date, event);
        int b = r->Evaluate(date, event);
        return (bool)(a | b);
    }
    return true;
}
