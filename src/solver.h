#include<z3.h>
#include<unordered_map>
#include"utils.h"
#include"expr.h"

#ifndef _SOLVER_H_
#define _SOLVER_H_

#ifndef LOG_PREFIX
#define LOG_PREFIX "solver"
#endif

namespace z3_solver {
	class Solver {
		public:
			Z3_context context;
			Z3_solver solver;
			Solver();
		private:
			static void error_handler(
				Z3_context ctx,
				Z3_error_code error
			) {
				err("Z3 Solver: %s\n",
					Z3_get_error_msg_ex(ctx,error));
			}
	};
	class TransVisitor : public symx::ExprVisitor {
		public:
			TransVisitor(
				const Solver *_solver,
				const symx::State &state
			);
			int visit(symx::refBytVec vec);
			int visit(symx::refBytMem mem);
			int visit(symx::refOperator oper);
			int visit(symx::refCond cond);
		private:
			const Solver *solver;
			const symx::State &state;
			Z3_sort bvsort1;
			Z3_sort bvsort4;
			std::unordered_map<symx::refExpr,Z3_ast> expr_ast;
	};
};

#endif