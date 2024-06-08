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

Title* LonelyTitleSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Title* title = calloc(1, sizeof(Title));
	title->lonelyText = text;
	title->type = LONELY_TITLE;
	return title;
}

Title* TitleSemanticAction(Text* text, Tags* tags) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Title* title = calloc(1, sizeof(Title));
	title->text = text;
	title->tags = tags;
	title->type = TITLE;
	return title;
}

Title* EmptyTitleSemanticAction(Tags* tags) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Title* title = calloc(1, sizeof(Title));
	title->lonelyTags = tags;
	title->type = NO_TITLE;
	return title;
}

Tags* TagsSemanticAction(Tag* tag, Tags* tags) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tags* tagsList = calloc(1, sizeof(Tags));
	tagsList->tag = tag;
	tagsList->tags = tags;
	tagsList->type = TAGS;
	return tagsList;
}

Tags* EndTagSemanticAction(Tag* tag) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tags* tagsList = calloc(1, sizeof(Tags));
	tagsList->tag = tag;
	tagsList->type = END_TAG;
	return tagsList;
}

Tag* Heading1SemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* heading1 = calloc(1, sizeof(Tag));
	heading1->text = text;
	heading1->type = HEADING_1;
	return heading1;
}

Tag* Heading2SemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* heading2 = calloc(1, sizeof(Tag));
	heading2->text = text;
	heading2->type = HEADING_2;
	return heading2;
}

Tag* Heading3SemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* heading3 = calloc(1, sizeof(Tag));
	heading3->text = text;
	heading3->type = HEADING_3;
	return heading3;
}

Tag* PageSkipSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* pageSkip = calloc(1, sizeof(Tag));
	pageSkip->text = text;
	pageSkip->type = PAGE_SKIP;
	return pageSkip;
}

Tag* ImageSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* image = calloc(1, sizeof(Tag));
	image->text = text;
	image->type = IMAGE;
	return image;
}

Tag* CodeSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* code = calloc(1, sizeof(Tag));
	code->text = text;
	code->type = CODE;
	return code;
}

Tag* EscapeSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* escape = calloc(1, sizeof(Tag));
	escape->text = text;
	escape->type = ESCAPE;
	return escape;
}

Tag* EquationSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* equation = calloc(1, sizeof(Tag));
	equation->text = text;
	equation->type = EQUATION;
	return equation;
}

Tag* UnorderedListSemanticAction(List* list) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* unorderedList = calloc(1, sizeof(Tag));
	unorderedList->list = list;
	unorderedList->type = UNORDERED_LIST;
	return unorderedList;
}

Tag* OrderedListSemanticAction(List* list) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* orderedList = calloc(1, sizeof(Tag));
	orderedList->list = list;
	orderedList->type = ORDERED_LIST;
	return orderedList;
}

Tag* TableSemanticAction(Table* table) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* tableTag = calloc(1, sizeof(Tag));
	tableTag->table = table;
	tableTag->type = TABLE;
	return tableTag;
}

Tag* BoldSemanticAction(Bold* bold) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* boldTag = calloc(1, sizeof(Tag));
	boldTag->bold = bold;
	boldTag->type = BOLD;
	return boldTag;
}

Tag* BoldTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* boldTag = calloc(1, sizeof(Tag));
	boldTag->text = text;
	boldTag->type = BOLD_TEXT;
	return boldTag;
}

Tag* ItalicSemanticAction(Italic* italic) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* italicTag = calloc(1, sizeof(Tag));
	italicTag->italic = italic;
	italicTag->type = ITALIC;
	return italicTag;
}

Tag* ItalicTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* italicTag = calloc(1, sizeof(Tag));
	italicTag->text = text;
	italicTag->type = ITALIC_TEXT;
	return italicTag;
}

Tag* UnderlineSemanticAction(Underline* underline) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* underlineTag = calloc(1, sizeof(Tag));
	underlineTag->underline = underline;
	underlineTag->type = UNDERLINE;
	return underlineTag;
}

Tag* UnderlineTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* underlineTag = calloc(1, sizeof(Tag));
	underlineTag->text = text;
	underlineTag->type = UNDERLINE_TEXT;
	return underlineTag;
}

Tag* StringTagSemanticAction(char* value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tag* textTag = calloc(1, sizeof(Tag));
	textTag->value = value;
	textTag->type = STRING_TAG;
	return textTag;
}

List* ItemSemanticAction(Text* text, List* item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List* list = calloc(1, sizeof(List));
	list->text = text;
	list->item = item;
	list->type = MULTIPLE_ITEMS;
	return list;
}

List* LonelyItemSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List* list = calloc(1, sizeof(List));
	list->lonelyText = text;
	list->type = LONELY_ITEM;
	return list;
}

Table* CellSeparatorSemanticAction(Text* text, Table* column) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Table* table = calloc(1, sizeof(Table));
	table->text = text;
	table->column = column;
	table->type = MULTIPLE_COLUMNS;
	return table;
}

Table* LonelyCellSeparatorSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Table* table = calloc(1, sizeof(Table));
	table->lonelyText = text;
	table->type = LONELY_COLUMN;
	return table;
}

Bold* BoldItalicTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->text = text;
	bold->type = BOLD_ITALIC_TEXT;
	return bold;
}

Bold* BoldItalicSemanticAction(BoldItalic* boldItalic) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->boldItalic = boldItalic;
	bold->type = BOLD_ITALIC;
	return bold;
}

Bold* BoldUnderlineTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->text = text;
	bold->type = BOLD_UNDERLINE_TEXT;
	return bold;
}

Bold* BoldUnderlineSemanticAction(BoldUnderline* boldUnderline) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bold* bold = calloc(1, sizeof(Bold));
	bold->boldUnderline = boldUnderline;
	bold->type = BOLD_UNDERLINE;
	return bold;
}

BoldItalic* BoldItalicUnderlineSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BoldItalic* boldItalic = calloc(1, sizeof(BoldItalic));
	boldItalic->text = text;
	return boldItalic;
}

BoldUnderline* BoldUnderlineItalicSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BoldUnderline* boldUnderline = calloc(1, sizeof(BoldUnderline));
	boldUnderline->text = text;
	return boldUnderline;
}

Italic* ItalicBoldTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->text = text;
	italic->type = ITALIC_BOLD_TEXT;
	return italic;
}

Italic* ItalicBoldSemanticAction(ItalicBold* italicBold) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->italicBold = italicBold;
	italic->type = ITALIC_BOLD;
	return italic;
}

Italic* ItalicUnderlineTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->text = text;
	italic->type = ITALIC_UNDERLINE_TEXT;
	return italic;
}

Italic* ItalicUnderlineSemanticAction(ItalicUnderline* italicUnderline) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Italic* italic = calloc(1, sizeof(Italic));
	italic->italicUnderline = italicUnderline;
	italic->type = ITALIC_UNDERLINE;
	return italic;
}

ItalicBold* ItalicBoldUnderlineSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ItalicBold* italicBold = calloc(1, sizeof(ItalicBold));
	italicBold->text = text;
	return italicBold;
}

ItalicUnderline* ItalicUnderlineBoldSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ItalicUnderline* italicUnderline = calloc(1, sizeof(ItalicUnderline));
	italicUnderline->text = text;
	return italicUnderline;
}

Underline* UnderlineBoldTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->text = text;
	underline->type = UNDERLINE_BOLD_TEXT;
	return underline;
}

Underline* UnderlineBoldSemanticAction(UnderlineBold* underlineBold) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->underlineBold = underlineBold;
	underline->type = UNDERLINE_BOLD;
	return underline;
}

Underline* UnderlineItalicTextSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->text = text;
	underline->type = UNDERLINE_ITALIC_TEXT;
	return underline;
}

Underline* UnderlineItalicSemanticAction(UnderlineItalic* underlineItalic) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Underline* underline = calloc(1, sizeof(Underline));
	underline->underlineItalic = underlineItalic;
	underline->type = UNDERLINE_ITALIC;
	return underline;
}

UnderlineBold* UnderlineBoldItalicSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UnderlineBold* underlineBold = calloc(1, sizeof(UnderlineBold));
	underlineBold->text = text;
	return underlineBold;
}

UnderlineItalic* UnderlineItalicBoldSemanticAction(Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UnderlineItalic* underlineItalic = calloc(1, sizeof(UnderlineItalic));
	underlineItalic->text = text;
	return underlineItalic;
}

Text* StringTextSemanticAction(char* value, Text* text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Text* newText = calloc(1, sizeof(Text));
	newText->value = value;
	newText->text = text;
	newText->type = STRING_TEXT;
	return newText;
}

Text* EmptyTextSemanticAction() {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Text* text = calloc(1, sizeof(Text));
	text->type = EMPTY_TEXT;
	return text;
}