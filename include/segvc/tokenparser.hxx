#pragma once

#include<segvc/util/datapipe.hxx>
#include<vector>
#include<segvc/tokens.hxx>
#include<segvc/expressions.hxx>

namespace segvc {

struct Tokenparser;

extern struct parser_eval_order_t {
	ExprPtr (segvc::Tokenparser::*eval_func)(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);
	std::vector< std::pair<Tokens::Type, OPE>> bindings;
} parser_eval_orders[];


struct Tokenparser {

	DataPipe<Token> *_input_pipe;
	std::shared_ptr<BlockStatement> stm_root;
	int _log_options;
	Token c_token;

	enum {
		EAT_INFO_EAT = 0b1,
		EAT_INFO_SKIP = 0b10,
	};

	void use(DataPipe<Token> &input_pipe);
	void use(std::shared_ptr<BlockStatement> stm_root);
	void use(int log_options);

	uint8_t getPVarT(const std::string& str);

	int eat(Tokens::Type ttype);
	int eatTyper(std::shared_ptr<Typer> c_typer, bool followAll);
	int eatDec(
		std::shared_ptr<BlockStatement> parent,
		DeclarationType dec_type
	);

	int eatFnDec(
		std::shared_ptr<BlockStatement> parent,
		DeclarationType dec_type
	);

	int eatFnParams(
		std::vector<
			std::pair<
				std::string,
				VariableEntry
		>> &params
	);

        int eatForStatement(
		std::shared_ptr<BlockStatement> parent,
		std::shared_ptr<BlockStatement> leadingBlock = nullptr
	);

        int eatWhileStatement(
		std::shared_ptr<BlockStatement> parent,
		std::shared_ptr<BlockStatement> leadingBlock = nullptr
	);

        int proc(std::shared_ptr<BlockStatement> parent, const bool _inline = true, const bool subscope = false);
        int proc_body(std::shared_ptr<BlockStatement> parent, Tokens::Type end_token = Tokens::TOK_SYS_EOF);
	int proc();

	ExprPtr eval_single(Tokens::Type till);
	std::shared_ptr<TupleExpression> eval_tuple(Tokens::Type till);
	ExprPtr eval(Tokens::Type till);

	ExprPtr evalPrimary(std::vector< std::pair<Tokens::Type, OPE>>&, int);

	ExprPtr evalUnaryPrefix(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);
	ExprPtr evalUnaryPostfix(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);

	ExprPtr evalBinaryLeftToRight(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);
	ExprPtr evalBinaryRightToLeft(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index);

	inline ExprPtr eval_order_exec(int index) {
		auto order = parser_eval_orders[index];
		return (this->*order.eval_func)(order.bindings, index);
	}
};

}
