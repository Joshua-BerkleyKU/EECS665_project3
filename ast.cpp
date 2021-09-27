#include "ast.hpp"

cshanty::ProgramNode::ProgramNode(std::list<DeclNode *> * globalsIn)
: ASTNode(new Position(0,0,0,0)), myGlobals(globalsIn){
	if (!globalsIn->empty()){
		myPos->expand(
			myGlobals->front()->pos(),
			myGlobals->back()->pos()
		);
	}
}

cshanty::RecordTypeDeclNode::RecordTypeDeclNode(Position * p, IDNode * Id, std::list<VarDeclNode *> * Variables)
: DeclNode(p), myId(Id), myGlobals(Variables){
	if (!variables->empty()){
		variables->expand(
			variables->front()->pos(),
			variables->back()->pos()
		);
	}
}
