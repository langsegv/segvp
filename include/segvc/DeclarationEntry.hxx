#pragma once

#include <string>

namespace segvc {

	struct TypeEntry;
	struct Expression;

	using ExprPtr = std::shared_ptr<Expression>;

	struct DeclarationEntry {
		enum class Type {
			parent,
			individual
		} type;
		std::string name;
		std::shared_ptr<TypeEntry> typer;
		std::vector<std::unique_ptr<DeclarationEntry>> childs;
	};

}
