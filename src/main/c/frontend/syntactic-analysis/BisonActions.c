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

Expression* DoubleExpressionSemanticAction(Expression* leftExpression, Expression* rightExpression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression* expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = MULTIPLE_EXPRESSIONS;
	return expression;
}

Expression* LonelyExpressionSemanticAction(StartToken startToken, EndToken endToken, Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression* expression = calloc(1, sizeof(Expression));
	expression->startToken = startToken;
	expression->constant = constant;
	expression->endToken = endToken;
	expression->type = SIMPLE_EXPRESSION;
	return expression;
}

Expression* FactorExpressionSemanticAction(Factor* factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression* expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor* ListFactorSemanticAction(StartToken startToken, EndToken endToken, List* list) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* factor = calloc(1, sizeof(Factor));
	factor->startListToken = startToken;
	factor->list = list;
	factor->endListToken = endToken;
	factor->type = LIST;
	return factor;
}

Factor* LonelyFactorSemanticAction(StartToken startToken, EndToken endToken, Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* factor = calloc(1, sizeof(Factor));
	factor->startToken = startToken;
	factor->constant = constant;
	factor->endToken = endToken;
	factor->type = SIMPLE_FACTOR;
	return factor;
}

Factor* BoldFactorSemanticAction(Bold* bold) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* factor = calloc(1, sizeof(Factor));
	factor->bold = bold;
	factor->type = BOLD;
	return factor;
}

Factor* ItalicFactorSemanticAction(Italic* italic) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* factor = calloc(1, sizeof(Factor));
	factor->italic = italic;
	factor->type = ITALIC;
	return factor;
}

Factor* UnderlineFactorSemanticAction(Underline* underline) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* factor = calloc(1, sizeof(Factor));
	factor->underline = underline;
	factor->type = UNDERLINE;
	return factor;
}

Factor* TableFactorSemanticAction(Table* table) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor* factor = calloc(1, sizeof(Factor));
	factor->table = table;
	factor->type = TABLE;
	return factor;
}

List* LonelyListSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List* list = calloc(1, sizeof(List));
	list->constant = constant;
	list->type = SIMPLE_LIST;
	return list;
}

List* DoubleListSemanticAction(List* leftList, List* rightList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List* list = calloc(1, sizeof(List));
	list->leftList = leftList;
	list->rightList = rightList;
	list->type = MULTIPLE_LISTS;
	return list;
}

Table* LonelyTableSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Table* table = calloc(1, sizeof(Table));
	table->constant = constant;
	table->type = SIMPLE_TABLE;
	return table;
}

Table* DoubleTableSemanticAction(Table* leftTable, Table* rightTable) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Table* table = calloc(1, sizeof(Table));
	table->leftTable = leftTable;
	table->rightTable = rightTable;
	table->type = MULTIPLE_TABLES;
	return table;
}

Bold* LonelyBoldSemanticAction(StartToken startToken, EndToken endToken, Constant* constant) {
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

Italic* LonelyItalicSemanticAction(StartToken startToken, EndToken endToken, Constant* constant) {
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

Underline* LonelyUnderlineSemanticAction(StartToken startToken, EndToken endToken, Constant* constant) {
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