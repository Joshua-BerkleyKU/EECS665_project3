#ifndef CSHANTYC_AST_HPP
#define CSHANTYC_AST_HPP

#include <ostream>
#include <list>
#include "tokens.hpp"

// **********************************************************************
// ASTnode class (base class for all other kinds of nodes)
// **********************************************************************

namespace cshanty{

/* You may find it useful to forward declare AST subclasses
   here so that you can use a class before it's full definition
*/
class DeclNode;
class TypeNode;
class StmtNode;
class IDNode;

class ASTNode{
public:
	ASTNode(Position * p) : myPos(p){ }
	virtual void unparse(std::ostream& out, int indent) = 0;
	Position * pos() { return myPos; }
	std::string posStr() { return pos()->span(); }
protected:
	Position * myPos;
};

/** 
* \class ProgramNode
* Class that contains the entire abstract syntax tree for a program.
* Note the list of declarations encompasses all global declarations
* which includes (obviously) all global variables and struct declarations
* and (perhaps less obviously), all function declarations
**/
class ProgramNode : public ASTNode{
public:
	ProgramNode(std::list<DeclNode *> * globalsIn) ;
	void unparse(std::ostream& out, int indent) override;
private:
	std::list<DeclNode * > * myGlobals;
};

class StmtNode : public ASTNode{
public:
	StmtNode(Position * p) : ASTNode(p){ }
	void unparse(std::ostream& out, int indent) override = 0;
};


/** \class DeclNode
* Superclass for declarations (i.e. nodes that can be used to 
* declare a struct, function, variable, etc).  This base class will 
**/
class DeclNode : public StmtNode{
public:
	DeclNode(Position * p) : StmtNode(p) { }
	void unparse(std::ostream& out, int indent) override = 0;
};

/**  \class ExpNode
* Superclass for expression nodes (i.e. nodes that can be used as
* part of an expression).  Nodes that are part of an expression
* should inherit from this abstract superclass.
**/
class ExpNode : public ASTNode{
protected:
	ExpNode(Position * p) : ASTNode(p){ }
};

class TrueNode : public ExpNode{
public:
	TrueNode(Position * p) : ExpNode(p){ }
};

class StrLitNode : public ExpNode{
public:
	StrLitNode(Position * p, std::string Val) 
	: ExpNode(p), stringVal(Val){ }
	void unparse(std::ostream& out, int indent);
private:
	std::string stringVal;
};

class UnaryExpNode : public ExpNode{
public:
	UnaryExpNode(Position * p, ExpNode * Expression) 
	: ExpNode(p), expression(Expression){ }
	void unparse(std::ostream& out, int indent);
private:
	ExpNode * expression;
};

class NegNode : public UnaryExpNode{
public:
	NegNode(Position * p, ExpNode * Expression) : UnaryExpNode(p), UnaryExpNode(Expression) { }
};

class NotNode  : public UnaryExpNode{
public:
	NotNode(Position * p, ExpNode * Expression) : UnaryExpNode(p), UnaryExpNode(Expression) { }
};

/**  \class TypeNode
* Superclass of nodes that indicate a data type. For example, in 
* the declaration "int a", the int part is the type node (a is an IDNode
* and the whole thing is a DeclNode).
**/
class TypeNode : public ASTNode{
protected:
	TypeNode(Position * p) : ASTNode(p){
	}
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
	//TODO: consider adding an isRef to use in unparse to 
	// indicate if this is a reference type
};

class LValNode : public ExpNode{
public:
	LValNode(Position * p) : ExpNode(p){}
	void unparse(std::ostream& out, int indent) override = 0;
};

class PostDecStmtNode : public StmtNode{
public:
	PostDecStmtNode(Position * p , LValNode * Variable) : StmtNode(p), variable(Variable) { }
	void unparse(std::ostream& out, int indent) override = 0;
	private:
	LValNode * variable;
};

class PostIncStmtNode : public StmtNode{
public:
	PostIncStmtNode(Position * p , LValNode * Variable) : StmtNode(p), variable(Variable) { }
	void unparse(std::ostream& out, int indent) override = 0;
	private:
	LValNode * variable;
};

class ReceiveStmtNode : public StmtNode{
public:
	ReceiveStmtNode(Position * p , LValNode * Variable) : StmtNode(p), variable(Variable) { }
	void unparse(std::ostream& out, int indent) override = 0;
	private:
	LValNode * variable;
};

class ReportStmtNode : public StmtNode{
public:
	ReportStmtNode(Position * p , ExpNode * Expression) : StmtNode(p), expression(Expression) { }
	void unparse(std::ostream& out, int indent) override = 0;
	private:
	ExpNode * expression;
};

class ReturnStmtNode : public StmtNode{
public:
	ReturnStmtNode(Position * p , ExpNode * Expression) : StmtNode(p), expression(Expression) { }
	void unparse(std::ostream& out, int indent) override = 0;
	private:
	ExpNode * expression;
};

class AssignExpNode : public StmtNode{
public:
	AssignExpNode(Position * p , ExpNode * Expression, LValNode * Variable) : StmtNode(p), expression(Expression), variable(Variable) { }
	void unparse(std::ostream& out, int indent) override = 0;
	private:
	LValNode * variable;
	ExpNode * expression;
};

/** An identifier. Note that IDNodes subclass
 * ExpNode because they can be used as part of an expression. 
**/

class IDNode : public LValNode{
public:
	IDNode(Position * p, std::string nameIn) 
	: LValNode(p), name(nameIn){ }
	void unparse(std::ostream& out, int indent);
private:
	/** The name of the identifier **/
	std::string name;
};

class RecordTypeNode : public LValNode{
public:
	RecordTypeNode(Position * p, IDNode * id, IDNode * name) 
	: LValNode(p), Id_being_accessed(id), Name_being_accessed(name){ }
	void unparse(std::ostream& out, int indent);
private:
	IDNode * Id_being_accessed;
	IDNode * Name_being_accessed;
};
 
/** A variable declaration. Note that this class is intended to 
 * represent a global or local variable of any type (including a struct
 * type. Note that this is not intended to represent a declaration of
 * a struct. In other words:
 * struct MyStruct { 
 *   int fieldA;
 * };
 * is NOT a VarDeclNode because it introduces a new datatype, not a new
 * variable (in this case, the example is a StructDeclNode).  * However,
 * struct MyStruct instance; *is* a VarDeclNode, since it introduces a 
 * new variable to the program. 
**/
class VarDeclNode : public DeclNode{
public:
	VarDeclNode(Position * p, TypeNode * type, IDNode * id) 
	: DeclNode(p), myType(type), myId(id){
	}
	void unparse(std::ostream& out, int indent);
private:
	TypeNode * myType;
	IDNode * myId;
};

class FormalDeclNode : public VarDeclNode{
public:
	FormalDeclNode(Position * p, TypeNode * type, IDNode * id) 
	: VarDeclNode(p), VarDeclNode(type), VarDeclNode(id){ }
	void unparse(std::ostream& out, int indent);
};

class RecordTypeNode : public DeclNode{
public:
	RecordTypeNode(Position * p, IDNode * id) 
	: DeclNode(p), myId(id){ }
	void unparse(std::ostream& out, int indent);
private:
	IDNode * myId;
};

//------------------------------------------------------------------------------------------------------------------------------------
//still need to add code for the list to work
//------------------------------------------------------------------------------------------------------------------------------------
class FnDeclNode : public DeclNode{
public:
	FnDeclNode(Position * p, TypeNode * type, IDNode * id,std::list<FormalDeclNode * > *  paramIn,std::list<StmtNode * > * funcBody) 
	: DeclNode(p), myType(type), myId(id){
	}
	void unparse(std::ostream& out, int indent);
private:
	TypeNode * myType;
	IDNode * myId;
	std::list<FormalDeclNode * > * parameters;
	std::list<StmtNode * > * functionBody;
};

class IntTypeNode : public TypeNode{
public:
	IntTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class BoolTypeNode : public TypeNode{
public:
	BoolTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class VoidTypeNode : public TypeNode{
public:
	VoidTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class StringTypeNode : public TypeNode{
public:
	StringTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class RecordTypeNode : public TypeNode{
public:
	StringTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

} //End namespace cshanty

#endif
