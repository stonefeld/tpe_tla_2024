#include "AbstractSyntaxTree.h"

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

void releaseProgram(Program* program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		releaseExpression(program->expression);
		free(program);
	}
}

void releaseExpression(Expression* expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression != NULL) {
		switch (expression->type) {
			case MULTIPLE_EXPRESSIONS:
				releaseExpression(expression->leftExpression);
				releaseExpression(expression->rightExpression);
				break;
			case SIMPLE_EXPRESSION: releaseConstant(expression->constant); break;
			case FACTOR: releaseFactor(expression->factor); break;
		}
		free(expression);
	}
}

void releaseFactor(Factor* factor) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (factor != NULL) {
		switch (factor->type) {
			case LIST: releaseList(factor->list); break;
			case BOLD: releaseBold(factor->bold); break;
			case ITALIC: releaseItalic(factor->italic); break;
			case UNDERLINE: releaseUnderline(factor->underline); break;
			case TABLE: releaseTable(factor->table); break;
			case SIMPLE_FACTOR: releaseConstant(factor->constant); break;
		}
		free(factor);
	}
}

void releaseTable(Table* table) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (table != NULL) {
		switch (table->type) {
			case MULTIPLE_TABLES:
				releaseTable(table->leftTable);
				releaseTable(table->rightTable);
				break;
			case SIMPLE_TABLE: releaseConstant(table->constant); break;
		}
		free(table);
	}
}

void releaseList(List* list) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (list != NULL) {
		switch (list->type) {
			case MULTIPLE_LISTS:
				releaseList(list->leftList);
				releaseList(list->rightList);
				break;
			case SIMPLE_LIST: releaseConstant(list->constant); break;
		}
		free(list);
	}
}

void releaseBold(Bold* bold) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (bold != NULL) {
		switch (bold->type) {
			case BOLD_ITALIC: releaseBoldItalic(bold->boldItalic); break;
			case BOLD_UNDERLINE: releaseBoldUnderline(bold->boldUnderline); break;
			case BOLD_CONSTANT: releaseConstant(bold->constant); break;
		}
		free(bold);
	}
}

void releaseItalic(Italic* italic) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (italic != NULL) {
		switch (italic->type) {
			case ITALIC_BOLD: releaseItalicBold(italic->italicBold); break;
			case ITALIC_UNDERLINE: releaseItalicUnderline(italic->italicUnderline); break;
			case ITALIC_CONSTANT: releaseConstant(italic->constant); break;
		}
		free(italic);
	}
}

void releaseUnderline(Underline* underline) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (underline != NULL) {
		switch (underline->type) {
			case UNDERLINE_BOLD: releaseUnderlineBold(underline->underlineBold); break;
			case UNDERLINE_ITALIC: releaseUnderlineItalic(underline->underlineItalic); break;
			case UNDERLINE_CONSTANT: releaseConstant(underline->constant); break;
		}
		free(underline);
	}
}

void releaseBoldItalic(BoldItalic* boldItalic) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (boldItalic != NULL) {
		releaseConstant(boldItalic->constant);
		free(boldItalic);
	}
}

void releaseBoldUnderline(BoldUnderline* boldUnderline) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (boldUnderline != NULL) {
		releaseConstant(boldUnderline->constant);
		free(boldUnderline);
	}
}

void releaseItalicBold(ItalicBold* italicBold) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (italicBold != NULL) {
		releaseConstant(italicBold->constant);
		free(italicBold);
	}
}

void releaseItalicUnderline(ItalicUnderline* italicUnderline) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (italicUnderline != NULL) {
		releaseConstant(italicUnderline->constant);
		free(italicUnderline);
	}
}

void releaseUnderlineBold(UnderlineBold* underlineBold) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (underlineBold != NULL) {
		releaseConstant(underlineBold->constant);
		free(underlineBold);
	}
}

void releaseUnderlineItalic(UnderlineItalic* underlineItalic) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (underlineItalic != NULL) {
		releaseConstant(underlineItalic->constant);
		free(underlineItalic);
	}
}

void releaseConstant(Constant* constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
		free(constant);
	}
}