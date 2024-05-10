#include "BisonActions.h"

#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger* _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char* functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char* functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

Program* ExpressionProgramSemanticAction(CompilerState* compilerState, Expression* expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program* program = calloc(1, sizeof(Program));
	program->expression = expression;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	} else {
		compilerState->succeed = true;
	}
	return program;
}

Expression* TokenExpressionSemanticAction(Token startToken, Token endToken, Constant* contantant, Expression* expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression* tokenExpression = calloc(1, sizeof(Expression));
	tokenExpression->startToken = startToken;
	tokenExpression->constant = contantant;
	tokenExpression->endToken = endToken;
	tokenExpression->expression = expression;
	tokenExpression->type = TOKEN_EXPRESSION;
	return tokenExpression;
}

Expression* FactorExpressionSemanticAction(Factor* factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression* factorExpression = calloc(1, sizeof(Expression));
	factorExpression->factor = factor;
	factorExpression->type = FACTOR;
	return factorExpression;
}

Factor* ListFactorSemanticAction(Token startToken, Token endToken, List* list, Factor* factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* listFactor = calloc(1, sizeof(Factor));
	listFactor->startListToken = startToken;
	listFactor->list = list;
	listFactor->endListToken = endToken;
	listFactor->listFactor = factor;
	listFactor->type = LIST;
	return listFactor;

}

Factor* TokenFactorSemanticAction(Token startToken, Token endToken, Constant* constant, Factor *factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* tokenFactor = calloc(1, sizeof(Factor));
	tokenFactor->startToken = startToken;
	tokenFactor->tokenConstant = constant;
	tokenFactor->endToken = endToken;
	tokenFactor->tokenFactor = factor;
	tokenFactor->type = TOKEN;
	return tokenFactor;

}

Factor* BoldFactorSemanticAction(Bold* bold, Factor* factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* boldFactor = calloc(1, sizeof(Factor));
	boldFactor->bold = bold;
	boldFactor->boldFactor = factor;
	boldFactor->type = BOLD;
	return boldFactor;
}

Factor* ItalicFactorSemanticAction(Italic* italic, Factor* factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* italicFactor = calloc(1, sizeof(Factor));
	italicFactor->italic = italic;
	italicFactor->italicFactor = factor;
	italicFactor->type = ITALIC;
	return italicFactor;
}

Factor* UnderlineFactorSemanticAction(Underline* underline, Factor* factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* underlineFactor = calloc(1, sizeof(Factor));
	underlineFactor->underline = underline;
	underlineFactor->underlineFactor = factor;
	underlineFactor->type = UNDERLINE;
	return underlineFactor;
}

Factor* TableFactorSemanticAction(Table* table, Factor* factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* tableFactor = calloc(1, sizeof(Factor));
	tableFactor->table = table;
	tableFactor->tableFactor = factor;
	tableFactor->type = TABLE;
	return tableFactor;
}

Factor* ConstantFactorSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* constantFactor = calloc(1, sizeof(Factor));
	constantFactor->lonelyConstant = constant;
	constantFactor->type = CONSTANT;
	return constantFactor;
}

List* ListSemanticAction(Constant* constant, List* item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List* list = calloc(1, sizeof(List));
	list->constant = constant;
	list->item = item;
	list->type = MULTIPLE_ITEMS;
	return list;
}

List* LonelyListSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List* list = calloc(1, sizeof(List));
	list->lonelyConstant = constant;
	list->type = LONELY_ITEM;
	return list;
}

Table* TableSemanticAction(Constant* constant, Table* column) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Table* table = calloc(1, sizeof(Table));
	table->constant = constant;
	table->column = column;
	table->type = MULTIPLE_COLUMNS;
	return table;
}

Table* LonelyTableSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Table* table = calloc(1, sizeof(Table));
	table->lonelyConstant = constant;
	table->type = LONELY_COLUMN;
	return table;
}

Bold* LonelyBoldSemanticAction(Token startToken, Token endToken, Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->startToken = startToken;
	bold->constant = constant;
	bold->endToken = endToken;
	bold->type = BOLD_CONSTANT;
	return bold;
}

Bold* ItalicFromBoldSemanticAction(BoldItalic* boldItalic) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->boldItalic = boldItalic;
	bold->type = BOLD_ITALIC;
	return bold;
}

Bold* UnderlineFromBoldSemanticAction(BoldUnderline* boldUnderline) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->boldUnderline = boldUnderline;
	bold->type = BOLD_UNDERLINE;
	return bold;
}

BoldItalic* LonelyBoldItalicSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BoldItalic* boldItalic = calloc(1, sizeof(BoldItalic));
	boldItalic->constant = constant;
	return boldItalic;
}

BoldUnderline* LonelyBoldUnderlineSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BoldUnderline* boldUnderline = calloc(1, sizeof(BoldUnderline));
	boldUnderline->constant = constant;
	return boldUnderline;
}

Italic* LonelyItalicSemanticAction(Token startToken, Token endToken, Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->startToken = startToken;
	italic->constant = constant;
	italic->endToken = endToken;
	italic->type = ITALIC_CONSTANT;
	return italic;
}

Italic* BoldFromItalicSemanticAction(ItalicBold* italicBold) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->italicBold = italicBold;
	italic->type = ITALIC_BOLD;
	return italic;
}

Italic* UnderlineFromItalicSemanticAction(ItalicUnderline* italicUnderline) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->italicUnderline = italicUnderline;
	italic->type = ITALIC_UNDERLINE;
	return italic;
}

ItalicBold* LonelyItalicBoldSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ItalicBold* italicBold = calloc(1, sizeof(ItalicBold));
	italicBold->constant = constant;
	return italicBold;
}

ItalicUnderline* LonelyItalicUnderlineSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ItalicUnderline* italicUnderline = calloc(1, sizeof(ItalicUnderline));
	italicUnderline->constant = constant;
	return italicUnderline;
}

Underline* LonelyUnderlineSemanticAction(Token startToken, Token endToken, Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->startToken = startToken;
	underline->constant = constant;
	underline->endToken = endToken;
	underline->type = UNDERLINE_CONSTANT;
	return underline;
}

Underline* BoldFromUnderlineSemanticAction(UnderlineBold* underlineBold) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->underlineBold = underlineBold;
	underline->type = UNDERLINE_BOLD;
	return underline;
}

Underline* ItalicFromUnderlineSemanticAction(UnderlineItalic* underlineItalic) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->underlineItalic = underlineItalic;
	underline->type = UNDERLINE_ITALIC;
	return underline;
}

UnderlineBold* LonelyUnderlineBoldSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UnderlineBold* underlineBold = calloc(1, sizeof(UnderlineBold));
	underlineBold->constant = constant;
	return underlineBold;
}

UnderlineItalic* LonelyUnderlineItalicSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UnderlineItalic* underlineItalic = calloc(1, sizeof(UnderlineItalic));
	underlineItalic->constant = constant;
	return underlineItalic;
}

Constant* StringConstantSemanticAction(const char* value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant* constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}