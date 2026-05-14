#include <segvc/tokenparser.hxx>

namespace segvc {


	/** Evals binary expressions/operators from left to right recursively
	 *  @returns An Expression pointer, if it's null, next tokens can't be evaluated as expression
	 */
	ExprPtr Tokenparser::evalBinaryLeftToRight(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index) {
		ExprPtr main_expr = eval_order_exec(index + 1);

		bool continueIteration=!!main_expr;
		while(continueIteration) {
			continueIteration=false;
			for(auto [ttype, op]: bindings) {
				if(eat(ttype)) {
					main_expr = std::make_shared<BinaryExpression>(
						main_expr,
						op,
						eval_order_exec(index + 1));

					continueIteration=true;
					break; // break's not necessary but probably improve efficiency.
				}
			}
		}
		return main_expr;
	}

	/** Evals binary expressions/operators from right to left recursively
	 *  @returns An Expression pointer, if it's null, next tokens can't be evaluated as expression
	 */
	ExprPtr Tokenparser::evalBinaryRightToLeft(std::vector< std::pair<Tokens::Type, OPE>> &bindings, int index) {
		ExprPtr main_expr = eval_order_exec(index + 1);
		
		if(main_expr) {
			for(auto [ttype, op]: bindings) {
				if(eat(ttype)) {
					return std::make_shared<BinaryExpression>(
						main_expr,
						op,
						// TODO: Evualation requires recursion, I don't think that's going to be a problem but I'm planing to change the method
						evalBinaryRightToLeft(bindings, index));
				}
			}
		}
		return main_expr;
	}

}
