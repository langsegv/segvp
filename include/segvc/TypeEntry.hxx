#pragma once

#include <memory>
#include <cstdint>
#include <segvc/DeclarationEntry.hxx>

namespace segvc {

enum {
	VAR_UNDEFINED=0,
	VAR_TYPE,
	VAR_POINTER,
	VAR_ARRAY,
	VAR_FUN,
};

enum {
	SPEC_MUT = 0,
	SPEC_EXT,
	SPEC_VOL,
};

struct Expression; // Pre definition
using ExprPtr = std::shared_ptr<Expression>;

struct Statement; // Pre definition
using StmPtr = std::shared_ptr<Statement>;

struct TypeEntry {
	std::string name;
	ExprPtr sizer;
	uint8_t vtype;
	uint8_t spec;
	std::shared_ptr<TypeEntry> respect_typer;

	std::vector<std::pair<
		DeclarationEntry,
		ExprPtr
	>> func_params;
};

}
