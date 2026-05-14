#pragma once
#include <string>

#include "expressions.hxx"

struct Symbol {
    std::shared_ptr<segvc::TypeEntry> valueType;
    segvc::DeclarationType declType;
    std::string name;
};
