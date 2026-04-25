#pragma once

namespace segvc {

	inline void concat(std::shared_ptr<TypeEntry> start, std::shared_ptr<TypeEntry> end) {
		std::shared_ptr<TypeEntry> current_end = start;
		while(current_end->respect_typer) {
			current_end = current_end->respect_typer;
		}

		current_end->respect_typer = end;
	}

}
