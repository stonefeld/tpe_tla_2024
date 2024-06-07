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

Program* ProgramSemanticAction(CompilerState* compilerState, Title* title) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program* program = calloc(1, sizeof(Program));
	program->title = title;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	} else {
		compilerState->succeed = true;
	}
	return program;
}

Title* TitleSemanticAction(Constant* constant, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Title* title = calloc(1, sizeof(Title));
	title->constant = constant;
	title->tag = tag;
	title->type = TITLE;
	return title;
}

Title* EmptyTitleSemanticAction(Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Title* title = calloc(1, sizeof(Title));
	title->lonelyTag = tag;
	title->type = EMPTY_TITLE;
	return title;
}

Tag* Heading1SemanticAction(Constant* constant, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* heading1 = calloc(1, sizeof(Tag));
	heading1->constant = constant;
	heading1->constantTag = tag;
	heading1->type = HEADING_1;
	return heading1;
}

Tag* Heading2SemanticAction(Constant* constant, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* heading2 = calloc(1, sizeof(Tag));
	heading2->constant = constant;
	heading2->constantTag = tag;
	heading2->type = HEADING_2;
	return heading2;
}

Tag* Heading3SemanticAction(Constant* constant, Tag* tag){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* heading3 = calloc(1, sizeof(Tag));
	heading3->constant = constant;
	heading3->constantTag = tag;
	heading3->type = HEADING_3;
	return heading3;
}

Tag* PageSkipSemanticAction(Constant* constant, Tag* tag){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* pageSkip = calloc(1, sizeof(Tag));
	pageSkip->constant = constant;
	pageSkip->constantTag = tag;
	pageSkip->type = PAGE_SKIP;
	return pageSkip;
}

Tag* ImageSemanticAction(Constant* constant, Tag* tag){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* image = calloc(1, sizeof(Tag));
	image->constant = constant;
	image->constantTag = tag;
	image->type = IMAGE;
	return image;
}

Tag* CodeSemanticAction(Constant* constant, Tag* tag){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* code = calloc(1, sizeof(Tag));
	code->constant = constant;
	code->constantTag = tag;
	code->type = CODE;
	return code;
}

Tag* EscapeSemanticAction(Constant* constant, Tag* tag){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* escape = calloc(1, sizeof(Tag));
	escape->constant = constant;
	escape->constantTag = tag;
	escape->type = ESCAPE;
	return escape;
}

Tag* EquationSemanticAction(Constant* constant, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* equation = calloc(1, sizeof(Tag));
	equation->constant = constant;
	equation->constantTag = tag;
	equation->type = EQUATION;
	return equation;
}

Tag* UnorderedListSemanticAction(List* list, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* unorderedList = calloc(1, sizeof(Tag));
	unorderedList->list = list;
	unorderedList->listTag = tag;
	unorderedList->type = UNORDERED_LIST;
	return unorderedList;
}

Tag* OrderedListSemanticAction(List* list, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* orderedList = calloc(1, sizeof(Tag));
	orderedList->list = list;
	orderedList->listTag = tag;
	orderedList->type = ORDERED_LIST;
	return orderedList;
}

Tag* TableSemanticAction(Table* table, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* tableTag = calloc(1, sizeof(Tag));
	tableTag->table = table;
	tableTag->tableTag = tag;
	tableTag->type = TABLE;
	return tableTag;
}

Tag* BoldSemanticAction(Bold* bold, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* boldTag = calloc(1, sizeof(Tag));
	boldTag->bold = bold;
	boldTag->boldTag = tag;
	boldTag->type = BOLD;
	return boldTag;
}

Tag* BoldConstantSemanticAction(Constant* constant, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* boldTag = calloc(1, sizeof(Tag));
	boldTag->constant = constant;
	boldTag->constantTag = tag;
	boldTag->type = BOLD_CONSTANT;
	return boldTag;
}

Tag* ItalicSemanticAction(Italic* italic, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* italicTag = calloc(1, sizeof(Tag));
	italicTag->italic = italic;
	italicTag->italicTag = tag;
	italicTag->type = ITALIC;
	return italicTag;
}

Tag* ItalicConstantSemanticAction(Constant* constant, Tag* tag){ 
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* italicTag = calloc(1, sizeof(Tag));
	italicTag->constant = constant;
	italicTag->constantTag = tag;
	italicTag->type = ITALIC_CONSTANT;
	return italicTag;
}

Tag* UnderlineSemanticAction(Underline* underline, Tag* tag){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* underlineTag = calloc(1, sizeof(Tag));
	underlineTag->underline = underline;
	underlineTag->underlineTag = tag;
	underlineTag->type = UNDERLINE;
	return underlineTag;
}

Tag* UnderlineConstantSemanticAction(Constant* constant, Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* underlineTag = calloc(1, sizeof(Tag));
	underlineTag->constant = constant;
	underlineTag->constantTag = tag;
	underlineTag->type = UNDERLINE_CONSTANT;
	return underlineTag;
}

List* ItemSemanticAction(Constant* constant, List* item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List* list = calloc(1, sizeof(List));
	list->constant = constant;
	list->item = item;
	list->type = MULTIPLE_ITEMS;
	return list;
}

List* LonelyItemSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List* list = calloc(1, sizeof(List));
	list->lonelyConstant = constant;
	list->type = LONELY_ITEM;
	return list;
}

Table* CellSeparatorSemanticAction(Constant* constant, Table* column) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Table* table = calloc(1, sizeof(Table));
	table->constant = constant;
	table->column = column;
	table->type = MULTIPLE_COLUMNS;
	return table;
}

Table* LonelyCellSeparatorSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Table* table = calloc(1, sizeof(Table));
	table->lonelyConstant = constant;
	table->type = LONELY_COLUMN;
	return table;
}

Bold* BoldItalicConstantSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->constant = constant;
	bold->type = BOLD_ITALIC_CONSTANT;
	return bold;
}

Bold* BoldItalicSemanticAction(BoldItalic* boldItalic) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->boldItalic = boldItalic;
	bold->type = BOLD_ITALIC;
	return bold;
}

Bold* BoldUnderlineConstantSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->constant = constant;
	bold->type = BOLD_UNDERLINE_CONSTANT;
	return bold;
}

Bold* BoldUnderlineSemanticAction(BoldUnderline* boldUnderline) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->boldUnderline = boldUnderline;
	bold->type = BOLD_UNDERLINE;
	return bold;
}


BoldItalic* BoldItalicUnderlineSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BoldItalic* boldItalic = calloc(1, sizeof(BoldItalic));
	boldItalic->constant = constant;
	return boldItalic;
}

BoldUnderline* BoldUnderlineItalicSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BoldUnderline* boldUnderline = calloc(1, sizeof(BoldUnderline));
	boldUnderline->constant = constant;
	return boldUnderline;
}

Italic* ItalicBoldConstantSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->constant = constant;
	italic->type = ITALIC_BOLD_CONSTANT;
	return italic;
}

Italic* ItalicBoldSemanticAction(ItalicBold* italicBold) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->italicBold = italicBold;
	italic->type = ITALIC_BOLD;
	return italic;
}

Italic* ItalicUnderlineConstantSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->constant = constant;
	italic->type = ITALIC_UNDERLINE_CONSTANT;
	return italic;
}

Italic* ItalicUnderlineSemanticAction(ItalicUnderline* italicUnderline) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->italicUnderline = italicUnderline;
	italic->type = ITALIC_UNDERLINE;
	return italic;
}


ItalicBold* ItalicBoldUnderlineSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ItalicBold* italicBold = calloc(1, sizeof(ItalicBold));
	italicBold->constant = constant;
	return italicBold;
}

ItalicUnderline* ItalicUnderlineBoldSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ItalicUnderline* italicUnderline = calloc(1, sizeof(ItalicUnderline));
	italicUnderline->constant = constant;
	return italicUnderline;
}

Underline* UnderlineBoldConstantSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->constant = constant;
	underline->type = UNDERLINE_BOLD_CONSTANT;
	return underline;
}

Underline* UnderlineBoldSemanticAction(UnderlineBold* underlineBold) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->underlineBold = underlineBold;
	underline->type = UNDERLINE_BOLD;
	return underline;
}

Underline* UnderlineItalicConstantSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->constant = constant;
	underline->type = UNDERLINE_ITALIC_CONSTANT;
	return underline;
}

Underline* UnderlineItalicSemanticAction(UnderlineItalic* underlineItalic) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->underlineItalic = underlineItalic;
	underline->type = UNDERLINE_ITALIC;
	return underline;
}

UnderlineBold* UnderlineBoldItalicSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UnderlineBold* underlineBold = calloc(1, sizeof(UnderlineBold));
	underlineBold->constant = constant;
	return underlineBold;
}

UnderlineItalic* UnderlineItalicBoldSemanticAction(Constant* constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UnderlineItalic* underlineItalic = calloc(1, sizeof(UnderlineItalic));
	underlineItalic->constant = constant;
	return underlineItalic;
}

Constant* StringConstantSemanticAction(char* value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant* constant = calloc(1, sizeof(Constant));
	constant->value = value;
	constant->type = STRING_CONSTANT;
	return constant;
}

Constant* EmptyConstantSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant* constant = calloc(1, sizeof(Constant));
	constant->type = EMPTY_CONSTANT;
	return constant;
}