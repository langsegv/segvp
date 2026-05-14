#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace segvc {

	void Tokenparser::use(DataPipe<Token> &input_pipe) {
		_input_pipe = &input_pipe;
	}

	void Tokenparser::use(DataPipe<Symbol> &symbol_output_pipe) {
		_symbol_output_pipe = &symbol_output_pipe;
	}

	void Tokenparser::use(std::shared_ptr<BlockStatement> _stm_root) {
		stm_root = _stm_root;
	}

	void Tokenparser::use(int log_options) {
		_log_options = log_options;;
	}

}
