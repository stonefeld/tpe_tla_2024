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
		freeTitle(program->title);
		free(program);
	}
}

void freeTitle(Title* title) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (title != NULL) {
		switch (title->type) {
			case TITLE:
				freeConstant(title->constant);
				freeTags(title->tags);
				break;
			case EMPTY_TITLE:
				freeTags(title->tags);
				break;
		}
		free(title);
	}
}

void freeTags(Tags* tags) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tags != NULL) {
		switch (tags->type) {
			case TAGS:
				freeTags(tags->tags);
				freeTag(tags->tag);
				break;
			case END_TAG:
				freeTag(tags->tag);
				break;
		}
		free(tags);
	}
}

void freeTag(Tag* tag) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tag != NULL) {
		switch (tag->type) {
			case HEADING_1:
			case HEADING_2:
			case HEADING_3:
			case PAGE_SKIP:
			case IMAGE:
			case CODE:
			case ESCAPE:
			case EQUATION:
			case BOLD_CONSTANT:
			case ITALIC_CONSTANT:
			case UNDERLINE_CONSTANT:
				freeConstant(tag->constant);
				break;
			case STRING_TAG:
				free(tag->value);
				break;
			case ORDERED_LIST:
			case UNORDERED_LIST:
				freeList(tag->list);
				break;
			case TABLE:
				freeTable(tag->table);
				break;
			case BOLD:
				freeBold(tag->bold);
				break;
			case ITALIC:
				freeItalic(tag->italic);
				break;
			case UNDERLINE:
				freeUnderline(tag->underline);
				break;
		}
		free(tag);
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
			case LONELY_COLUMN:
				freeConstant(table->lonelyConstant);
				break;
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
			case LONELY_ITEM:
				freeConstant(list->lonelyConstant);
				break;
		}
		free(list);
	}
}

void freeBold(Bold* bold) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (bold != NULL) {
		switch (bold->type) {
			case BOLD_ITALIC:
				freeBoldItalic(bold->boldItalic);
				break;
			case BOLD_UNDERLINE:
				freeBoldUnderline(bold->boldUnderline);
				break;
			case BOLD_ITALIC_CONSTANT:
			case BOLD_UNDERLINE_CONSTANT:
				freeConstant(bold->constant);
				break;
		}
		free(bold);
	}
}

void freeItalic(Italic* italic) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (italic != NULL) {
		switch (italic->type) {
			case ITALIC_BOLD:
				freeItalicBold(italic->italicBold);
				break;
			case ITALIC_UNDERLINE:
				freeItalicUnderline(italic->italicUnderline);
				break;
			case ITALIC_BOLD_CONSTANT:
			case ITALIC_UNDERLINE_CONSTANT:
				freeConstant(italic->constant);
				break;
		}
		free(italic);
	}
}

void freeUnderline(Underline* underline) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (underline != NULL) {
		switch (underline->type) {
			case UNDERLINE_BOLD:
				freeUnderlineBold(underline->underlineBold);
				break;
			case UNDERLINE_ITALIC:
				freeUnderlineItalic(underline->underlineItalic);
				break;
			case UNDERLINE_BOLD_CONSTANT:
			case UNDERLINE_ITALIC_CONSTANT:
				freeConstant(underline->constant);
				break;
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
			case STRING_CONSTANT:
				free(constant->value);
				break;
			case EMPTY_CONSTANT:
				break;
		}
		free(constant);
	}
}