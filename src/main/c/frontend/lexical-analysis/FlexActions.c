#include "FlexActions.h"

#include <string.h>

/* MODULE INTERNAL STATE */

static Logger *_logger = NULL;
static boolean _logIgnoredLexemes = true;

static boolean isTitle = false;
static boolean isHeading1 = false;
static boolean isHeading2 = false;
static boolean isHeading3 = false;
static boolean isPageSkip = false;
static boolean isUnorderedList = false;
static boolean isOrderedList = false;
static boolean isListItem = false;
static boolean isCellSeparator = false;
static boolean isImage = false;
static boolean isBold = false;
static boolean isItalic = false;
static boolean isUnderline = false;
static boolean isTable = false;
static boolean isCode = false;
static boolean isEscaped = false;
static boolean isEquation = false;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char *functionName, LexicalAnalyzerContext *lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char *functionName, LexicalAnalyzerContext *lexicalAnalyzerContext) {
	char *escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s, lexeme = %s   (context = %d, length = %d, line = %d)", functionName, escapedLexeme,
	             lexicalAnalyzerContext->lexeme, lexicalAnalyzerContext->currentContext, lexicalAnalyzerContext->length,
	             lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

void IgnoredLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

Token TitleLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isTitle ? TITLE_END : TITLE_START;
	isTitle = !isTitle;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token Heading1LexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isHeading1 ? HEADING_1_END : HEADING_1_START;
	isHeading1 = !isHeading1;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token Heading2LexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isHeading2 ? HEADING_2_END : HEADING_2_START;
	isHeading2 = !isHeading2;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token Heading3LexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isHeading3 ? HEADING_3_END : HEADING_3_START;
	isHeading3 = !isHeading3;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token PageSkipLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isPageSkip ? PAGE_SKIP_END : PAGE_SKIP_START;
	isPageSkip = !isPageSkip;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token UnorderedListLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isUnorderedList ? UNORDERED_LIST_END : UNORDERED_LIST_START;
	isUnorderedList = !isUnorderedList;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token OrderedListLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isOrderedList ? ORDERED_LIST_END : ORDERED_LIST_START;
	isOrderedList = !isOrderedList;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token ListItemLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isListItem ? LIST_ITEM_END : LIST_ITEM_START;
	isListItem = !isListItem;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token CellSeparatorLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isCellSeparator ? CELL_SEPARATOR_END : CELL_SEPARATOR_START;
	isCellSeparator = !isCellSeparator;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token ImageLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isImage ? IMAGE_END : IMAGE_START;
	isImage = !isImage;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token BoldLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isBold ? BOLD_END : BOLD_START;
	isBold = !isBold;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token ItalicLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isItalic ? ITALIC_END : ITALIC_START;
	isItalic = !isItalic;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token UnderlineLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isUnderline ? UNDERLINE_END : UNDERLINE_START;
	isUnderline = !isUnderline;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token TableLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isTable ? TABLE_END : TABLE_START;
	isTable = !isTable;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token CodeLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isCode ? CODE_END : CODE_START;
	isCode = !isCode;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token EscapedLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isEscaped ? ESCAPE_END : ESCAPE_START;
	isEscaped = !isEscaped;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token EquationLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token = isEquation ? EQUATION_END : EQUATION_START;
	isEquation = !isEquation;
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token StringLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = lexicalAnalyzerContext->lexeme;
	return STRING;
}

Token UnknownLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}
