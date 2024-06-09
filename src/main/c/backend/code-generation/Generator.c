#include "Generator.h"

// TODO: CHEQUEAR ESTO
#include "../../frontend/syntactic-analysis/BisonParser.h"

/* MODULE INTERNAL STATE */

const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger* _logger = NULL;

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PRIVATE FUNCTIONS */

static void _generateProgram(Program* program);
static void _generateTitle(Title* title);
static void _generateTags(Tags* tags);
static void _generateTag(Tag* tag);
static void _generateList(List* list);
static void _generateTable(Table* table);
static void _generateBold(Bold* bold);
static void _generateBoldItalic(BoldItalic* boldItalic);
static void _generateBoldUnderline(BoldUnderline* boldUnderline);
static void _generateItalic(Italic* italic);
static void _generateItalicBold(ItalicBold* italicBold);
static void _generateItalicUnderline(ItalicUnderline* italicUnderline);
static void _generateUnderline(Underline* underline);
static void _generateUnderlineBold(UnderlineBold* underlineBold);
static void _generateUnderlineItalic(UnderlineItalic* underlineItalic);
static void _generateText(Text* text);

static void _generateEpilogue(const int value);
static void _generatePrologue(void);
static void _output(const char* const format, ...);

/**
 * Generates the output of the program.
 */
static void _generateProgram(Program* program) {
	_generateTitle(program->title);
}

/**
 * Generates the output of a title.
 */
static void _generateTitle(Title* title) {
	switch (title->type) {
		case TITLE:
			_output("%s", "\\title{");
			_generateText(title->text);
			_output("%s", "}\n\\author{}\n\\date{}\n\n\\begin{document}\n\n\\maketitle\n\n");
			_generateTags(title->tags);
			break;
		case NO_TITLE:
			_output("%s", "\\begin{document}\n");
			_generateTags(title->lonelyTags);
			break;
		case LONELY_TITLE:
			_output("%s", "\\title{");
			_generateText(title->lonelyText);
			_output("%s", "}\n\\author{}\n\\date{}\n\n\\begin{document}\n\n\\maketitle\n\n");
			break;
		default: logError(_logger, "The specified title type is unknown: %d", title->type); break;
	}
}

/**
 * Generates the output of tags.
 */
static void _generateTags(Tags* tags) {
	switch (tags->type) {
		case TAGS:
			_generateTag(tags->tag);
			_generateTags(tags->tags);
			break;
		case END_TAG: _generateTag(tags->endTag); break;
		default: logError(_logger, "The specified tags type is unknown: %d", tags->type); break;
	}
}

/**
 * Generates the output of a tag.
 */
static void _generateTag(Tag* tag) {
	switch (tag->type) {
		case HEADING_1:
			_output("%s", "\\section{");
			_generateText(tag->text);
			_output("%s", "}\n");
			break;
		case HEADING_2:
			_output("%s", "\\subsection{");
			_generateText(tag->text);
			_output("%s", "}\n");
			break;
		case HEADING_3:
			_output("%s", "\\subsubsection{");
			_generateText(tag->text);
			_output("%s", "}\n");
			break;
		case PAGE_SKIP: _output("%s", "\\newpage\n"); break;
		case IMAGE:
			_output("%s", "\\begin{center}\n\\includegraphics[width=0.75\\textwidth]{");
			_generateText(tag->text);
			_output("%s", "}\n\\end{center}\n");
			break;
		case CODE:
			_output("%s", "\\begin{minted}{text}\n");
			_generateText(tag->text);
			_output("%s", "\n\\end{minted}\n");
		case ESCAPE: _generateText(tag->text); break;
		case EQUATION:
			_output("%s%s%s", "\\[\n");
			_generateText(tag->text);
			_output("%s", "\\]\n");
		case ORDERED_LIST:
			_output("%s", "\\begin{enumerate}\n");
			_generateList(tag->list);
			_output("%s", "\\end{enumerate}\n");
			break;
		case UNORDERED_LIST:
			_output("%s", "\\begin{itemize}\n");
			_generateList(tag->list);
			_output("%s", "\\end{itemize}\n");
			break;
		case BOLD_TEXT:
			_output("%s", "\\textbf{");
			_generateText(tag->text);
			_output("}");
			break;
		case BOLD:
			_output("%s", "\\textbf{");
			_generateBold(tag->bold);
			_output("%s", "}");
			break;
		case ITALIC_TEXT:
			_output("%s", "\\textit{");
			_generateText(tag->text);
			_output("}");
			break;
		case ITALIC:
			_output("%s", "\\textit{");
			_generateItalic(tag->italic);
			_output("%s", "}");
			break;
		case UNDERLINE_TEXT:
			_output("%s", "\\underline{");
			_generateText(tag->text);
			_output("}");
			break;
		case UNDERLINE:
			_output("%s", "\\underline{");
			_generateUnderline(tag->underline);
			_output("%s", "}");
			break;
		case TABLE: break;
		case STRING_TAG: _output("%s ", tag->value); break;
		default: logError(_logger, "The specified tag type is unknown: %d", tag->type); break;
	}
}

/**
 * Generates the output of a list.
 */
static void _generateList(List* list) {
	switch (list->type) {
		case LONELY_ITEM:
			_output("%s", "\\item ");
			_generateText(list->lonelyText);
			_output("%s", "\n");
			break;
		case MULTIPLE_ITEMS:
			_output("%s", "\\item ");
			_generateText(list->lonelyText);
			_output("%s", "\n");
			_generateList(list->item);
			break;
		default: logError(_logger, "The specified list type is unknown: %d", list->type); break;
	}
}

/**
 * Generates the output of a table.
 */
static void _generateTable(Table* table) {
	// switch (table->type) {
	// 	case LONELY_COLUMN:
	// 		_output(1 + indentationLevel, "%s%s%s", "[ $", "CELL_SEPARATOR_START", "$, circle, draw, purple ]\n");
	// 		_generateText(1 + indentationLevel, table->lonelyText);
	// 		_output(1 + indentationLevel, "%s%s%s", "[ $", "CELL_SEPARATOR_END", "$, circle, draw, purple ]\n");
	// 		break;
	// 	case MULTIPLE_COLUMNS:
	// 		_output(1 + indentationLevel, "%s%s%s", "[ $", "CELL_SEPARATOR_START", "$, circle, draw, purple ]\n");
	// 		_generateText(1 + indentationLevel, table->text);
	// 		_output(1 + indentationLevel, "%s%s%s", "[ $", "CELL_SEPARATOR_END", "$, circle, draw, purple ]\n");
	// 		_generateTable(1 + indentationLevel, table->column);
	// 		break;
	// 	default: logError(_logger, "The specified table type is unknown: %d", table->type); break;
	// }
}

/**
 * Generates the output of a bold.
 */
static void _generateBold(Bold* bold) {
	switch (bold->type) {
		case BOLD_ITALIC:
			_output("%s", "\\textit{");
			_generateBoldItalic(bold->boldItalic);
			_output("%s", "}");
			break;
		case BOLD_ITALIC_TEXT:
			_output("%s", "\\textit{");
			_generateText(bold->text);
			_output("%s", "}");
			break;
		case BOLD_UNDERLINE:
			_output("%s", "\\underline{");
			_generateBoldUnderline(bold->boldUnderline);
			_output("%s", "}");
			break;
		case BOLD_UNDERLINE_TEXT:
			_output("%s", "\\underline{");
			_generateText(bold->text);
			_output("%s", "}");
			break;
		default: logError(_logger, "The specified bold type is unknown: %d", bold->type); break;
	}
}

/**
 * Generates the output of a boldItalic.
 */
static void _generateBoldItalic(BoldItalic* boldItalic) {
	_output("%s", "\\underline{");
	_generateText(boldItalic->text);
	_output("%s", "}");
}

/**
 * Generates the output of a boldUnderline.
 */
static void _generateBoldUnderline(BoldUnderline* boldUnderline) {
	_output("%s", "\\textit{");
	_generateText(boldUnderline->text);
	_output("%s", "}");
}

/**
 * Generates the output of an italic.
 */
static void _generateItalic(Italic* italic) {
	switch (italic->type) {
		case ITALIC_BOLD:
			_output("%s", "\\textbf{");
			_generateItalicBold(italic->italicBold);
			_output("%s", "}");
			break;
		case ITALIC_BOLD_TEXT:
			_output("%s", "\\textbf{");
			_generateText(italic->text);
			_output("%s", "}");
			break;
		case ITALIC_UNDERLINE:
			_output("%s", "\\underline{");
			_generateItalicUnderline(italic->italicUnderline);
			_output("%s", "}");
			break;
		case ITALIC_UNDERLINE_TEXT:
			_output("%s", "\\underline{");
			_generateText(italic->text);
			_output("%s", "}");
			break;
		default: logError(_logger, "The specified italic type is unknown: %d", italic->type); break;
	}
}

/**
 * Generates the output of an italicBold.
 */
static void _generateItalicBold(ItalicBold* italicBold) {
	_output("%s", "\\underline{");
	_generateText(italicBold->text);
	_output("%s", "}");
}

/**
 * Generates the output of an italicUnderline.
 */
static void _generateItalicUnderline(ItalicUnderline* italicUnderline) {
	_output("%s", "\\textbf{");
	_generateText(italicUnderline->text);
	_output("%s", "}");
}

/**
 * Generates the output of an underline.
 */
static void _generateUnderline(Underline* underline) {
	switch (underline->type) {
		case UNDERLINE_BOLD:
			_output("%s", "\\textbf{");
			_generateUnderlineBold(underline->underlineBold);
			_output("%s", "}");
			break;
		case UNDERLINE_BOLD_TEXT:
			_output("%s", "\\textbf{");
			_generateText(underline->text);
			_output("%s", "}");
			break;
		case UNDERLINE_ITALIC:
			_output("%s", "\\textit{");
			_generateUnderlineItalic(underline->underlineItalic);
			_output("%s", "}");
			break;
		case ITALIC_UNDERLINE_TEXT:
			_output("%s", "\\textit{");
			_generateText(underline->text);
			_output("%s", "}");
			break;
		default: logError(_logger, "The specified underline type is unknown: %d", underline->type); break;
	}
}

/**
 * Generates the output of an underlineBold.
 */
static void _generateUnderlineBold(UnderlineBold* underlineBold) {
	_output("%s", "\\textit{");
	_generateText(underlineBold->text);
	_output("%s", "}");
}

/**
 * Generates the output of an underlineItalic.
 */
static void _generateUnderlineItalic(UnderlineItalic* underlineItalic) {
	_output("%s", "\\textbf{");
	_generateText(underlineItalic->text);
	_output("%s", "}");
}

/**
 * Generates the output of a text.
 */
static void _generateText(Text* text) {
	switch (text->type) {
		case STRING_TEXT:
			_output("%s ", text->value);
			_generateText(text->text);
			break;
		case EMPTY_TEXT: break;
		default: logError(_logger, "The specified text type is unknown: %d", text->type); break;
	}
}

/**
 * Creates the prologue of the generated output, a Latex document that renders
 * a tree thanks to the Forest package.
 *
 * @see https://ctan.dcc.uchile.cl/graphics/pgf/contrib/forest/forest-doc.pdf
 */
static void _generatePrologue(void) {
	_output("%s", "\\documentclass{article}\n\n\\usepackage{minted}\n\n");
}

/**
 * Creates the epilogue of the generated output, that is, the final lines that
 * completes a valid Latex document.
 */
static void _generateEpilogue(const int value) {
	_output("%s", "\n\\end{document}\n");
}

/**
 * Outputs a formatted string to standard output.
 */
static void _output(const char* const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	char* effectiveFormat = concatenate(1, format);
	vfprintf(stdout, effectiveFormat, arguments);
	free(effectiveFormat);
	va_end(arguments);
}

/** PUBLIC FUNCTIONS */

void generate(CompilerState* compilerState) {
	logDebugging(_logger, "Generating Prologue...");
	_generatePrologue();
	logDebugging(_logger, "Prologue generated. Generating Program...");
	_generateProgram(compilerState->abstractSyntaxtTree);
	logDebugging(_logger, "Program generated. Generating Epilogue...");
	_generateEpilogue(compilerState->value);
	logDebugging(_logger, "Generation is done.");
}
