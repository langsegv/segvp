#pragma once

#include <memory>
#include <cstdint>
#include <segvc/DeclarationEntry.hxx>

namespace segvc {

enum {
	VAR_UNDEFINED=0,

	/**
	*  These types basicly represents one bit.
	*  Even that doesn't make sense in clasical computing, these units can be applicable to quantum computing.
	*/
	VAR_U1,

	VAR_U8,
	VAR_I8,
	VAR_C8,

	VAR_U16,
	VAR_I16,
	VAR_C16,

	VAR_U32,
	VAR_I32,
	VAR_C32,
	VAR_F32,

	VAR_U64,
	VAR_I64,
	VAR_F64,

	VAR_U128,
	VAR_I128,
	VAR_F128,

	/**
	*  These two types going to have number of bits that equals to bits of the cpu architecture.
	*  eg. If cpu is x64, these numbers basicly be equals to u64 and i64.
	*/
	VAR_USIZE,
	VAR_ISIZE,

	VAR_BOOL,

	VAR_POINTER,
	VAR_ARRAY,
	VAR_FUN,
};

enum {
	SPEC_NDET = 0,
	SPEC_MUT,
	SPEC_INL,
	SPEC_EXT,
	SPEC_VOL,
};

struct Expression; // Pre definition
using ExprPtr = std::shared_ptr<Expression>;

struct Statement; // Pre definition
using StmPtr = std::shared_ptr<Statement>;

struct TypeEntry {
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
