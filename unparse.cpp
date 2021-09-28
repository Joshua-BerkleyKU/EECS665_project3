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
	out << this->myId;
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
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " * ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void PlusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " + ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void OrNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " || ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void NotEqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " != ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void MinusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " - ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void LessNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " < ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void LessEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " <= ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void GreaterNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " > ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void GreaterEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " >= ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void EqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " == ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void DivideNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " / ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void AndNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->leftNode->unparse(out, 0);
	out << " && ";
	this->rightNode->unparse(out, 0);
	out << ")";
}

void AssignExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->variable->unparse(out, 0);
	out << " = ";
	this->expression->unparse(out, 0);
	out << "; \n";
}

void IndexNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->Id_being_accessed->unparse(out, 0);
	out << " [";
	this->field_Name_being_accessed->unparse(out, 0);
	out << "] ";
}

void CallStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->Function->unparse(out, 0);
}

void AssignStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->assignment->unparse(out, 0);
	
}

void PostDecStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->variable->unparse(out, 0);
	out << "--; \n";
}

void PostIncStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->variable->unparse(out, 0);
	out << "++; \n";
}

void ReceiveStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << " receive ";
	this->variable->unparse(out, 0);
	out << "; \n";
}

void ReportStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << " report ";
	this->expression->unparse(out, 0);
	out << "; \n";
}

void ReturnStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << " return ";
	this->expression->unparse(out, 0);
	out << "; \n";
}

void RecordTypeDeclNode::unparse(std::ostream& out, int indent) {
	doIndent(out, indent);
	out << "record ";
	this->myId->unparse(out, 0);
	out << " {\n";
	for (auto varDeclNode: *variables) {
		varDeclNode->unparse(out, indent);
	}
	out << "\n}\n";
}

void FnDeclNode::unparse(std::ostream& out, int indent) {
	doIndent(out, indent);
	this->myType->unparse(out, 0);
	out << " ";
	this->myId->unparse(out, 0);
	out << "(";
	if (!(parameters == nullptr))
	{
		out << parameters->size();
		for (auto param: *parameters)
		{
			// param->unparse(out, 0);
		}
	}
	out << ") {\n";
	for (auto stmt: *functionBody)
	{
		stmt->unparse(out, indent);
	}
	out << "\n}\n";
}

void IfStmtNode::unparse(std::ostream& out, int indent) {
	doIndent(out, indent);
	out << " if (";
	this->condition->unparse(out, 0); 
	out << ") {\n";
	for (auto stmt: *IfBody)
	{
		stmt->unparse(out, indent);
	}
	out << "\n}\n";
}

void IfElseStmtNode::unparse(std::ostream& out, int indent) {
	doIndent(out, indent);
	out << " if (";
	this->condition->unparse(out, 0); 
	out << ") {\n";
	for (auto stmt: *IfTrueBody)
	{
		stmt->unparse(out, indent);
	}
	out << "\n}\n else {\n";
	for (auto stmt: *IfFalseBody)
	{
		stmt->unparse(out, indent);
	}
	out << "\n}\n";
}

void WhileStmtNode::unparse(std::ostream& out, int indent) {
	doIndent(out, indent);
	out << " while ("; 
	this->condition->unparse(out, 0); 
	out << ") {\n";
	for (auto stmt: *WhileBody)
	{
		stmt->unparse(out, indent);
	}
	out << "\n}\n";
}

void CallExpNode::unparse(std::ostream& out, int indent) {
	doIndent(out, indent);
	this->nameFunc->unparse(out, 0); 
	out << "(";
	if (!(arguments == nullptr))
	{
		for (auto args: *arguments) {
			args->unparse(out, indent);
		}
	}
	out << ");";
}

} // End namespace cshanty
