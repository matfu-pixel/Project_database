#pragma once

#include <string>
#include "token.h"
#include <memory>
#include "date.h"
using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    And,
    Or
};

class Node {
public:
    Node();
    virtual ~Node() = default;
    virtual bool Evaluate(const Date, const string) = 0;
private:
};

class EmptyNode : public Node {
public:
    EmptyNode();
    bool Evaluate(const Date date, const string event) override;
private:
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, Date date);
    bool Evaluate(const Date date, const string event) override;
private:
    const Comparison c;
    const Date d;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, const string event);
    bool Evaluate(const Date date, const string event) override;
private:
    const Comparison c;
    const string e;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation cmp, shared_ptr<Node> left, shared_ptr<Node>right);
    bool Evaluate(const Date date, const string event) override;
private:
    const LogicalOperation c;
    shared_ptr<Node> l, r;
};
