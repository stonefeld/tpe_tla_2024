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
	if (strcmp(lexicalAnalyzerContext->lexeme, "🤴") == 0) {
		token = isTitle ? TITLE_END : TITLE_START;
		isTitle = !isTitle;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "👴") == 0) {
		token = isHeading1 ? HEADING_1_END : HEADING_1_START;
		isHeading1 = !isHeading1;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "👨") == 0) {
		token = isHeading2 ? HEADING_2_END : HEADING_2_START;
		isHeading2 = !isHeading2;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "👶") == 0) {
		token = isHeading3 ? HEADING_3_END : HEADING_3_START;
		isHeading3 = !isHeading3;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "🐇") == 0) {
		token = isPageSkip ? PAGE_SKIP_END : PAGE_SKIP_START;
		isPageSkip = !isPageSkip;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "💥") == 0) {
		token = isUnorderedList ? UNORDERED_LIST_END : UNORDERED_LIST_START;
		isUnorderedList = !isUnorderedList;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "🔢") == 0) {
		token = isOrderedList ? ORDERED_LIST_END : ORDERED_LIST_START;
		isOrderedList = !isOrderedList;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "🎯") == 0) {
		token = isListItem ? LIST_ITEM_END : LIST_ITEM_START;
		isListItem = !isListItem;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "🤸‍♂️") == 0) {
		token = isCellSeparator ? CELL_SEPARATOR_END : CELL_SEPARATOR_START;
		isCellSeparator = !isCellSeparator;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "📷") == 0) {
		token = isImage ? IMAGE_END : IMAGE_START;
		isImage = !isImage;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "👨‍🦲") == 0) {
		token = isBold ? BOLD_END : BOLD_START;
		isBold = !isBold;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "🤌") == 0) {
		token = isItalic ? ITALIC_END : ITALIC_START;
		isItalic = !isItalic;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "📉") == 0) {
		token = isUnderline ? UNDERLINE_END : UNDERLINE_START;
		isUnderline = !isUnderline;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "📊") == 0) {
		token = isTable ? TABLE_END : TABLE_START;
		isTable = !isTable;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "💻") == 0) {
		token = isCode ? CODE_END : CODE_START;
		isCode = !isCode;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "👮‍♂️") == 0) {
		token = isEscaped ? ESCAPE_END : ESCAPE_START;
		isEscaped = !isEscaped;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "🤓") == 0) {
		token = isEquation ? EQUATION_END : EQUATION_START;
		isEquation = !isEquation;
	}
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
