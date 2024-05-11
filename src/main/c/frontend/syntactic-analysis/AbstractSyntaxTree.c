#include "AbstractSyntaxTree.h"

#include <stdlib.h>

/* MODULE INTERNAL STATE */

static Logger* _logger = NULL;

void initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntxTree");
}

void shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PUBLIC FUNCTIONS */

void freeProgram(Program* program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		freeExpression(program->expression);
		free(program);
	}
}

void freeExpression(Expression* expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression != NULL) {
		switch (expression->type) {
			case TOKEN_EXPRESSION:
				freeConstant(expression->constant);
				freeExpression(expression->expression);
				break;
			case FACTOR: freeFactor(expression->factor); break;
		}
		free(expression);
	}
}

void freeFactor(Factor* factor) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (factor != NULL) {
		switch (factor->type) {
			case LIST:
				freeList(factor->list);
				freeFactor(factor->listFactor);
				break;
			case BOLD:
				freeBold(factor->bold);
				freeFactor(factor->boldFactor);
				break;
			case ITALIC:
				freeItalic(factor->italic);
				freeFactor(factor->italicFactor);
				break;
			case UNDERLINE:
				freeUnderline(factor->underline);
				freeFactor(factor->underlineFactor);
				break;
			case TABLE:
				freeTable(factor->table);
				freeFactor(factor->tableFactor);
				break;
			case TOKEN:
				freeConstant(factor->tokenConstant);
				freeFactor(factor->tokenFactor);
				break;
			case CONSTANT: freeConstant(factor->lonelyConstant); break;
		}
		free(factor);
	}
}

void freeTable(Table* table) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (table != NULL) {
		switch (table->type) {
			case MULTIPLE_COLUMNS:
				freeTable(table->column);
				freeConstant(table->constant);
				break;
			case LONELY_COLUMN: freeConstant(table->lonelyConstant); break;
		}
		free(table);
	}
}

void freeList(List* list) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (list != NULL) {
		switch (list->type) {
			case MULTIPLE_ITEMS:
				freeList(list->item);
				freeConstant(list->constant);
				break;
			case LONELY_ITEM: freeConstant(list->lonelyConstant); break;
		}
		free(list);
	}
}

void freeBold(Bold* bold) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (bold != NULL) {
		switch (bold->type) {
			case BOLD_ITALIC: freeBoldItalic(bold->boldItalic); break;
			case BOLD_UNDERLINE: freeBoldUnderline(bold->boldUnderline); break;
			case BOLD_CONSTANT: freeConstant(bold->constant); break;
		}
		free(bold);
	}
}

void freeItalic(Italic* italic) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (italic != NULL) {
		switch (italic->type) {
			case ITALIC_BOLD: freeItalicBold(italic->italicBold); break;
			case ITALIC_UNDERLINE: freeItalicUnderline(italic->italicUnderline); break;
			case ITALIC_CONSTANT: freeConstant(italic->constant); break;
		}
		free(italic);
	}
}

void freeUnderline(Underline* underline) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (underline != NULL) {
		switch (underline->type) {
			case UNDERLINE_BOLD: freeUnderlineBold(underline->underlineBold); break;
			case UNDERLINE_ITALIC: freeUnderlineItalic(underline->underlineItalic); break;
			case UNDERLINE_CONSTANT: freeConstant(underline->constant); break;
		}
		free(underline);
	}
}

void freeBoldItalic(BoldItalic* boldItalic) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (boldItalic != NULL) {
		freeConstant(boldItalic->constant);
		free(boldItalic);
	}
}

void freeBoldUnderline(BoldUnderline* boldUnderline) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (boldUnderline != NULL) {
		freeConstant(boldUnderline->constant);
		free(boldUnderline);
	}
}

void freeItalicBold(ItalicBold* italicBold) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (italicBold != NULL) {
		freeConstant(italicBold->constant);
		free(italicBold);
	}
}

void freeItalicUnderline(ItalicUnderline* italicUnderline) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (italicUnderline != NULL) {
		freeConstant(italicUnderline->constant);
		free(italicUnderline);
	}
}

void freeUnderlineBold(UnderlineBold* underlineBold) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (underlineBold != NULL) {
		freeConstant(underlineBold->constant);
		free(underlineBold);
	}
}

void freeUnderlineItalic(UnderlineItalic* underlineItalic) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (underlineItalic != NULL) {
		freeConstant(underlineItalic->constant);
		free(underlineItalic);
	}
}

void freeConstant(Constant* constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
		switch (constant->type) {
			case STRING_CONSTANT: free(constant->constant); break;
			case LONELY_STRING: break;
		}
		free(constant);
	}
}