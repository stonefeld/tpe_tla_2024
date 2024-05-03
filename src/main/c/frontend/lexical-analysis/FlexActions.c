#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

static bool isBold = false;
static bool isItalic = false;
static bool isUnderline = false;
static bool isTable = false;
static bool isCode = false;
static bool isEscaped = false;
static bool isEquation = false;

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

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

// void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
// 	if (_logIgnoredLexemes) {
// 		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
// 	}
// }

// void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
// 	if (_logIgnoredLexemes) {
// 		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
// 	}
// }

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

// Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
// 	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
// 	Token token;
// 	switch (lexicalAnalyzerContext->lexeme[0]) {
// 		case '-': token = SUB; break;
// 		case '*': token = MUL; break;
// 		case '/': token = DIV; break;
// 		case '+': token = ADD; break;
// 	}
// 	lexicalAnalyzerContext->semanticValue->token = token;
// 	return token;
// }

// Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
// 	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
// 	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
// 	return INTEGER;
// }

// Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
// 	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
// 	Token token;
// 	switch (lexicalAnalyzerContext->lexeme[0]) {
// 		case '(': token = OPEN_PARENTHESIS; break;
// 		case ')': token = CLOSE_PARENTHESIS; break;
// 	}
// 	lexicalAnalyzerContext->semanticValue->token = token;
// 	return token;
// }

Token SingleLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '🤴': token = TITLE; break;
		case '👴': token = HEADING_1; break;
		case '👨': token = HEADING_2; break;
		case '👶': token = HEADING_3; break;
		case '🐇': token = PAGE_SKIP; break;
		case '💥': token = UNORDERED_LIST; break;
		case '🔢': token = ORDERED_LIST; break;
		case '🤸‍♂️': token = CELL_SEPARATOR; break;
		case '📷': token = IMAGE; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;

}

Token DoubleLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '👨‍🦲': {
			token = isBold ? BOLD_END : BOLD_START;
			isBold = !isBold;
		} break;
		case '\U0001F90C':{
			token = isItalic ? ITALIC_END : ITALIC_START;
			isItalic = !isItalic;
		} break;
		case '📉':{
			token = isUnderline ? UNDERLINE_END : UNDERLINE_START;
			isUnderline = !isUnderline;			
		} break;
		case '📊':{
			token = isTable ? TABLE_END : TABLE_START;
			isTable = !isTable;
		} break;
		case '💻':{
			token = isCode ? CODE_END : CODE_START;
			isCode = !isCode;
		} break;
		case '👮‍♂️':{
			token = isEscaped ? ESCAPE_END : ESCAPE_START;
			isEscaped = !isEscaped;
		} break;
		case '🤓':{
			token = isEquation ? EQUATION_END : EQUATION_START;
			isEquation = !isEquation;
		} break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token StringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = lexicalAnalyzerContext->lexeme;
	return STRING;
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}
