#pragma once

#include <string>
#include <memory>
#include <vector>
#include <shared_mutex>

#include <segvc/TypeEntry.hxx>
#include <segvc/irvalue.hxx>
#include <segvc/DeclarationEntry.hxx>

namespace segvc {

enum class OPE {
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,

	SHL,
	SHR,

	TER, // ternary, x ? 1 : 0

	EQEQ,
	NEQ,
	AND,
	OR,
	ANDAND,
	OROR,

	XOR,

	ASSIGN, // =
	ASSADD, // +=
	ASSSUB, // -=
	ASSMUL, // *=
	ASSDIV, // /=
	ASSMOD, // %=
	ASSAND, // &=
	ASSOR,  // |=
	ASSXOR, // ^=
	ASSSHL, // <<=
	ASSSHR, // >>=
	ASSSWAP,// <>

	SHIFTL, // <<
	SHIFTR, // >>

	COMLT,  // <
	COMRT,  // >
	COMLTE, // <=
	COMRTE, // >=
	RANGEI, // ..
	RANGEE, // ..=

	// Unary Operators
	ADDR, // &x
	DEREF, // *x
	NOT, // !
	NEG, // ~x
	INCB, // ++x
	INCA, // x++
	DECB, // --x
	DECA, // x--
	POSITIVE, // +x
	NEGATIVE, // -x

	COMMA // <Expression>, <Expression>       see: https://en.wikipedia.org/wiki/Comma_operator
};

struct ExpressionVisitor;
struct StatementVisitor;

struct Expression {
	std::shared_mutex mutex;
	virtual ~Expression() = default;
	virtual std::unique_ptr<IRValue> accept(ExpressionVisitor& v) = 0;
};

using ExprPtr = std::shared_ptr<Expression>;

struct BinaryExpression : public Expression {
	ExprPtr left, right;
	OPE op;

	BinaryExpression(ExprPtr left, OPE op, ExprPtr right);

	std::unique_ptr<IRValue> accept(ExpressionVisitor& v) override;
};

struct TupleExpression : public Expression {
	std::vector<ExprPtr> expressions;
	std::unique_ptr<IRValue> accept(ExpressionVisitor& v) override;
};

struct UnaryExpression : public Expression {
        ExprPtr te;
        OPE op;
	ExprPtr param;

        UnaryExpression(ExprPtr te, OPE op);

        std::unique_ptr<IRValue> accept(ExpressionVisitor& v) override;
};

enum class LiteralType {
	LIT_NUMBER,
	LIT_CHAR,
	LIT_STRING
};

struct LiteralExpression : public Expression {
	LiteralType ltype;
	std::string value;

	LiteralExpression(LiteralType ltype, std::string value);

        std::unique_ptr<IRValue> accept(ExpressionVisitor& v) override;
};

struct VariableExpression : public Expression {
	std::string name;

	VariableExpression(std::string name);

        std::unique_ptr<IRValue> accept(ExpressionVisitor& v) override;
};


/**
 *  Using for reaching members with ' . ' or ' -> ' operator
 *  eg.
 *     let foo Foo
 *     foo.bar();
 */
struct MemberExpression : public VariableExpression {
	bool isPointer;
	ExprPtr parent;

	MemberExpression(ExprPtr parent, std::string name);

        std::unique_ptr<IRValue> accept(ExpressionVisitor& v) override;
};

/**
 *  Using for reaching elements through array and map
 *  eg.
 *     let mymap hashmap<string, int>
 *     map["foo"] = bar
 */
struct SubscriptExpression : public Expression {
	ExprPtr parent;
	ExprPtr index;

	SubscriptExpression(ExprPtr parent, ExprPtr index);

        std::unique_ptr<IRValue> accept(ExpressionVisitor& v) override;
};

struct FunctionCallExpression : public Expression {
	ExprPtr function;
	std::shared_ptr<TupleExpression> params;

	FunctionCallExpression(ExprPtr func, std::shared_ptr<TupleExpression> params);

	std::unique_ptr<IRValue> accept(ExpressionVisitor& v) override;
};

struct Statement {
	std::shared_mutex mutex;
	virtual ~Statement() = default;
	virtual void accept(StatementVisitor& v) = 0;
};

using StmPtr = std::shared_ptr<Statement>;

enum DeclarationType {
	UNDEFINED = 0,
	CONST,
	STATIC
};

struct DeclarationStatement : Statement {
	DeclarationType dec_type;

	std::unique_ptr<DeclarationEntry> entry;

	ExprPtr master_initializer;

	void accept(StatementVisitor& v) override;
};

struct BlockStatement : public Statement {
	std::vector<StmPtr> childs;

	void accept(StatementVisitor& v) override;
};

struct FunctionDeclarationStatement : Statement {
        std::string name;
		DeclarationType dec_type;
        std::shared_ptr<TypeEntry> type_spec;
        std::shared_ptr<BlockStatement> body;

	/*
	 *  The reason we don't use map<string, ...> or unordered_map is because
	 * we should initialize the parameters in right order and also empty named (non-usable padding parameters)
	 * can exist multiple times.
	 *
	 *  We'll should catch multiple variables that has non-empty but same names and throw errors
	 * at ast visitor stages but not in the parser stage
	 *
	 * NOTE: Empty named parameters exist and would be used for backwards compability.
	 *  eg. First function accept string and string's size but then you relaize you can find length of the string with loops (but Yes, bad practice for some cases)
	 *  eg. External source call's a function with extra parameters but you only need some of the parameters
	 */
	std::vector<std::pair<
			DeclarationEntry,
			ExprPtr
		>> params;

        void accept(StatementVisitor& v) override;
};

struct ExpressionStatement : public Statement {
	ExprPtr expr;

	void accept(StatementVisitor& v) override;
};

struct IfStatement : public Statement {
	ExprPtr condition;
	StmPtr body;

	void accept(StatementVisitor& v) override;
};

struct WhileStatement : public IfStatement {
	ExprPtr condition;

	StmPtr lead, body, trail;

	void accept(StatementVisitor& v) override;
};

struct BasicForStatement : public Statement {
	std::shared_ptr<BlockStatement> init;

	StmPtr lead, body, trail;

	virtual void accept(StatementVisitor& v) override = 0;
};

struct ForStatement : public BasicForStatement {
	ExprPtr condition;
	StmPtr update;

	void accept(StatementVisitor& v) override;
};

struct ForEachStatement : public BasicForStatement {
	ExprPtr iterable;

	void accept(StatementVisitor& v) override;
};

struct ReturnStatement : public Statement {
	ExprPtr expr;

	void accept(StatementVisitor& v) override;
};

}
