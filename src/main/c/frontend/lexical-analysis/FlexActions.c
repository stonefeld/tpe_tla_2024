#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger *_logger = NULL;
static boolean _logIgnoredLexemes = true;

static boolean isTitle = false;
static boolean isHeading1 = false;
static boolean isHeading2 = false;
static boolean isHeading3 = false;
static boolean isPageSkip = false;
static boolean isUnoerderedList = false;
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
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)", functionName, escapedLexeme,
	             lexicalAnalyzerContext->currentContext, lexicalAnalyzerContext->length, lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

void IgnoredLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

Token DoubleLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '🤴': {
			token = isTitle ? TITLE_END : TITLE_START;
			isTitle = !isTitle;
		} break;
		case '👴': {
			token = isHeading1 ? HEADING_1_END : HEADING_1_START;
			isHeading1 = !isHeading1;
		} break;
		case '👨': {
			token = isHeading2 ? HEADING_2_END : HEADING_2_START;
			isHeading2 = !isHeading2;
		} break;
		case '👶': {
			token = isHeading3 ? HEADING_3_END : HEADING_3_START;
			isHeading3 = !isHeading3;
		} break;
		case '🐇': {
			token = isPageSkip ? PAGE_SKIP_END : PAGE_SKIP_START;
			isPageSkip = !isPageSkip;
		} break;
		case '💥': {
			token = isUnoerderedList ? UNORDERED_LIST_END : UNORDERED_LIST_START;
			isUnoerderedList = !isUnoerderedList;
		} break;
		case '🔢': {
			token = isOrderedList ? ORDERED_LIST_END : ORDERED_LIST_START;
			isOrderedList = !isOrderedList;
		} break;
		case '🎯': {
			token = isListItem ? LIST_ITEM_END : LIST_ITEM_START;
			isListItem = !isListItem;
		} break;
		case '🤸‍♂️': {
			token = isCellSeparator ? CELL_SEPARATOR_END : CELL_SEPARATOR_START;
			isCellSeparator = !isCellSeparator;
		} break;
		case '📷': {
			token = isImage ? IMAGE_END : IMAGE_START;
			isImage = !isImage;
		} break;
		case '👨‍🦲': {
			token = isBold ? BOLD_END : BOLD_START;
			isBold = !isBold;
		} break;
		case '🤌': {
			token = isItalic ? ITALIC_END : ITALIC_START;
			isItalic = !isItalic;
		} break;
		case '📉': {
			token = isUnderline ? UNDERLINE_END : UNDERLINE_START;
			isUnderline = !isUnderline;
		} break;
		case '📊': {
			token = isTable ? TABLE_END : TABLE_START;
			isTable = !isTable;
		} break;
		case '💻': {
			token = isCode ? CODE_END : CODE_START;
			isCode = !isCode;
		} break;
		case '👮‍♂️': {
			token = isEscaped ? ESCAPE_END : ESCAPE_START;
			isEscaped = !isEscaped;
		} break;
		case '🤓': {
			token = isEquation ? EQUATION_END : EQUATION_START;
			isEquation = !isEquation;
		} break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token StringLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = lexicalAnalyzerContext->lexeme;
	return STRING;
}

Token UnknownLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}
