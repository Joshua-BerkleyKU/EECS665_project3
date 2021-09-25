#include "ast.hpp"

namespace cshanty{

/*
doIndent is declared static, which means that it can 
only be called in this file (its symbol is not exported).
*/
static void doIndent(std::ostream& out, int indent){
	for (int k = 0 ; k < indent; k++){ out << "\t"; }
}

/*
In this code, the intention is that functions are grouped 
into files by purpose, rather than by class.
If you're used to having all of the functions of a class 
defined in the same file, this style may be a bit disorienting,
though it is legal. Thus, we can have
ProgramNode::unparse, which is the unparse method of ProgramNodes
defined in the same file as DeclNode::unparse, the unparse method
of DeclNodes.
*/


void ProgramNode::unparse(std::ostream& out, int indent){
	/* Oh, hey it's a for-each loop in C++!
	   The loop iterates over each element in a collection
	   without that gross i++ nonsense. 
	 */
	for (auto global : *myGlobals){
		/* The auto keyword tells the compiler
		   to (try to) figure out what the
		   type of a variable should be from 
		   context. here, since we're iterating
		   over a list of DeclNode *s, it's 
		   pretty clear that global is of 
		   type DeclNode *.
		*/
		global->unparse(out, indent);
	}
}

void VarDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myType->unparse(out, 0);
	out << " ";
	this->myId->unparse(out, 0);
	out << ";\n";
}

void FormalDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myType->unparse(out, 0);
	out << " ";
	this->myId->unparse(out, 0);
}

void IDNode::unparse(std::ostream& out, int indent){
	out << this->name;
}

void IntTypeNode::unparse(std::ostream& out, int indent){
	out << "int";
}

void BoolTypeNode::unparse(std::ostream& out, int indent){
	out << "bool";
}

void VoidTypeNode::unparse(std::ostream& out, int indent){
	out << "void";
}

void StringTypeNode::unparse(std::ostream& out, int indent){
	out << "string";
}

void RecordTypeNode::unparse(std::ostream& out, int indent){
	out << "record";
}

void NotNode::unparse(std::ostream& out, int indent){
	out << "not";
}

void NegNode::unparse(std::ostream& out, int indent){
	out << "neg";
}

void TrueNode::unparse(std::ostream& out, int indent){
	out << "true";
}

void FalseNode::unparse(std::ostream& out, int indent){
	out << "false";
}

void StrLitNode::unparse(std::ostream& out, int indent){
	out << this->stringVal;
}

void IntLitNode::unparse(std::ostream& out, int indent){
	out << this->numval;
}

void TimesNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " * ";
	this->rightNode->unparse(out, 0);
}

void PlusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " + ";
	this->rightNode->unparse(out, 0);
}

void OrNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " || ";
	this->rightNode->unparse(out, 0);
}

void NotEqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " != ";
	this->rightNode->unparse(out, 0);
}

void MinusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " - ";
	this->rightNode->unparse(out, 0);
}

void LessNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " < ";
	this->rightNode->unparse(out, 0);
}

void LessEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " <= ";
	this->rightNode->unparse(out, 0);
}

void GreaterNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " > ";
	this->rightNode->unparse(out, 0);
}

void GreaterEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " >= ";
	this->rightNode->unparse(out, 0);
}

void EqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " == ";
	this->rightNode->unparse(out, 0);
}

void DivideNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " / ";
	this->rightNode->unparse(out, 0);
}

void AndNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->leftNode->unparse(out, 0);
	out << " && ";
	this->rightNode->unparse(out, 0);
}

} // End namespace cshanty
