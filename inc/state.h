#ifndef _STATE_H_
#define _STATE_H_

#include<memory>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<string>

#include"utils.h"
#include"expr.h"
#include"vm.h"

namespace symx {
    using namespace symx;

    class ProgCtr {
	public:
	    const uint64_t rawpc;
	    const int mode;
	    ProgCtr(const uint64_t _rawpc,const int _mode)
		: rawpc(_rawpc),mode(_mode) {}
	    bool operator==(const ProgCtr &other) const {
		return rawpc == other.rawpc && mode == other.mode;
	    }
    };
    class BaseState : public std::enable_shared_from_this<BaseState> {
	public:
	    refExpr mem;
	    std::vector<refExpr> reg;
	    std::vector<refCond> flag;
    };
    class State : public BaseState {
	public:
	    const ProgCtr pc;
	    const refAddrSpace as;
	    std::vector<refBytVec> symbol;
	    std::unordered_set<refCond> constr;
	    //std::unordered_set<refMemRecord> select_set;
	    //std::vector<refMemRecord> store_seq;

	    State(const ProgCtr &_pc,const refAddrSpace &_as)
		: pc(_pc),as(_as) {}
    };
    class Block : public BaseState {
	public:
	    const ProgCtr pc;
	    refExpr next_insmd;
	    std::vector<std::string> discode;
	    Block(const ProgCtr &_pc) : pc(_pc) {};
    };

    int state_executor(Context *ctx);

/*
class BuildVisitor : public ExprVisitor {
	public:
		BuildVisitor(const refState &_state) : state(_state) {}
		refExpr get_expr(const refExpr &expr);
		refCond get_cond(const refCond &cond);
		int get_mem_record(
			std::unordered_set<refMemRecord> *selset,
			std::vector<refMemRecord> *strseq);
		int pre_visit(const refBytVec &vec);
		int pre_visit(const refBytMem &mem);
		int pre_visit(const refOperator &oper);
		int pre_visit(const refCond &cond);
		int post_visit(const refBytVec &vec);
		int post_visit(const refBytMem &mem);
		int post_visit(const refOperator &oper);
		int post_visit(const refCond &cond);
	private:
		const refState state;
		std::unordered_map<refExpr,refExpr> expr_map;
		std::unordered_map<refCond,refCond> cond_map;
		std::unordered_set<refMemRecord> select_set;
		std::vector<refMemRecord> store_seq;
};
class FixVisitor : public ExprVisitor {
	public:
		FixVisitor(
			const AddrSpace &_addrsp,
			const std::unordered_map<refExpr,uint64_t> &_var
		) : addrsp(_addrsp),var(_var) {}
		bool get_fix(const refExpr &expr);
		int pre_visit(const refBytVec &vec);
		int pre_visit(const refBytMem &mem);
		int pre_visit(const refOperator &oper);
		int pre_visit(const refCond &cond);
		int post_visit(const refBytVec &vec);
		int post_visit(const refBytMem &mem);
		int post_visit(const refOperator &oper);
		int post_visit(const refCond &cond);
	private:
		const AddrSpace &addrsp;
		const std::unordered_map<refExpr,uint64_t> &var;
		std::unordered_map<refExpr,bool> fix_expr;
*/
};
namespace std {
    template<> struct hash<symx::ProgCtr> {
	std::size_t operator()(const symx::ProgCtr &key) const {
	    return (key.rawpc << 8) | key.mode;
	}
    };
}

/*
class TransVisitor : public ExprVisitor {};

refBlock state_create_block(Context *ctx,const ProgCtr &pc);

*/

#endif
