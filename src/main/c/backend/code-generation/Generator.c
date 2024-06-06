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
static void _generateExpression(const unsigned int indentationLevel, Expression* expression);
static void _generateFactor(const unsigned int indentationLevel, Factor* factor);
static void _generateList(const unsigned int indentationLevel, List* list);
static void _generateTable(const unsigned int indentationLevel, Table* table);
static void _generateBold(const unsigned int indentationLevel, Bold* bold);
static void _generateBoldItalic(const unsigned int indentationLevel, BoldItalic* boldItalic);
static void _generateBoldUnderline(const unsigned int indentationLevel, BoldUnderline* boldUnderline);
static void _generateItalic(const unsigned int indentationLevel, Italic* italic);
static void _generateItalicBold(const unsigned int indentationLevel, ItalicBold* italicBold);
static void _generateItalicUnderline(const unsigned int indentationLevel, ItalicUnderline* italicUnderline);
static void _generateUnderline(const unsigned int indentationLevel, Underline* underline);
static void _generateUnderlineBold(const unsigned int indentationLevel, UnderlineBold* underlineBold);
static void _generateUnderlineItalic(const unsigned int indentationLevel, UnderlineItalic* underlineItalic);
static void _generateConstant(const unsigned int indentationLevel, Constant* constant);
static const char* _tokenToCharacter(const Token token);

static void _generateEpilogue(const int value);
static void _generatePrologue(void);
static char* _indentation(const unsigned int indentationLevel);
static void _output(const unsigned int indentationLevel, const char* const format, ...);

/**
 * Generates the output of the program.
 */
static void _generateProgram(Program* program) {
	_generateExpression(3, program->expression);
}

/**
 * Generates the output of an expression.
 */
static void _generateExpression(const unsigned int indentationLevel, Expression* expression) {
	_output(indentationLevel, "%s", "[ $E$, circle, draw, black!20\n");
	switch (expression->type) {
		case TOKEN_EXPRESSION:
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(expression->startToken),
			        "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, expression->constant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(expression->endToken),
			        "$, circle, draw, purple ]\n");
			_generateExpression(1 + indentationLevel, expression->expression);
			break;
		case FACTOR: _generateFactor(1 + indentationLevel, expression->factor); break;
		default: logError(_logger, "The specified expression type is unknown: %d", expression->type); break;
	}
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of a factor.
 */
static void _generateFactor(const unsigned int indentationLevel, Factor* factor) {
	_output(indentationLevel, "%s", "[ $F$, circle, draw, black!20\n");
	switch (factor->type) {
		case LIST:
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(factor->startListToken),
			        "$, circle, draw, purple ]\n");
			_generateList(1 + indentationLevel, factor->list);
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(factor->endListToken),
			        "$, circle, draw, purple ]\n");
			_generateFactor(1 + indentationLevel, factor->listFactor);
			break;
		case BOLD:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_START", "$, circle, draw, purple ]\n");
			_generateBold(1 + indentationLevel, factor->bold);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_END", "$, circle, draw, purple ]\n");
			_generateFactor(1 + indentationLevel, factor->boldFactor);
			break;
		case ITALIC:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_START", "$, circle, draw, purple ]\n");
			_generateItalic(1 + indentationLevel, factor->italic);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_END", "$, circle, draw, purple ]\n");
			_generateFactor(1 + indentationLevel, factor->italicFactor);
			break;
		case UNDERLINE:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_START", "$, circle, draw, purple ]\n");
			_generateUnderline(1 + indentationLevel, factor->underline);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_END", "$, circle, draw, purple ]\n");
			_generateFactor(1 + indentationLevel, factor->underlineFactor);
			break;
		case TABLE:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "TABLE_START", "$, circle, draw, purple ]\n");
			_generateTable(1 + indentationLevel, factor->table);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "TABLE_END", "$, circle, draw, purple ]\n");
			_generateFactor(1 + indentationLevel, factor->tableFactor);
			break;
		case TOKEN:
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(factor->startToken),
			        "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, factor->tokenConstant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(factor->endToken),
			        "$, circle, draw, purple ]\n");
			_generateFactor(1 + indentationLevel, factor->tableFactor);
			break;
		case CONSTANT: _generateConstant(1 + indentationLevel, factor->lonelyConstant); break;
		default: logError(_logger, "The specified factor type is unknown: %d", factor->type); break;
	}
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of a list.
 */
static void _generateList(const unsigned int indentationLevel, List* list) {
	_output(indentationLevel, "%s", "[ $L$, circle, draw, black!20\n");
	switch (list->type) {
		case LONELY_ITEM:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "LIST_ITEM_START", "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, list->lonelyConstant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "LIST_ITEM_END", "$, circle, draw, purple ]\n");
			break;
		case MULTIPLE_ITEMS:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "LIST_ITEM_START", "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, list->constant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "LIST_ITEM_END", "$, circle, draw, purple ]\n");
			_generateList(1 + indentationLevel, list->item);
			break;
		default: logError(_logger, "The specified list type is unknown: %d", list->type); break;
	}
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of a table.
 */
static void _generateTable(const unsigned int indentationLevel, Table* table) {
	_output(indentationLevel, "%s", "[ $T$, circle, draw, black!20\n");
	switch (table->type) {
		case LONELY_COLUMN:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "CELL_SEPARATOR_START", "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, table->lonelyConstant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "CELL_SEPARATOR_END", "$, circle, draw, purple ]\n");
			break;
		case MULTIPLE_COLUMNS:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "CELL_SEPARATOR_START", "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, table->constant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "CELL_SEPARATOR_END", "$, circle, draw, purple ]\n");
			_generateTable(1 + indentationLevel, table->column);
			break;
		default: logError(_logger, "The specified table type is unknown: %d", table->type); break;
	}
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of a bold.
 */
static void _generateBold(const unsigned int indentationLevel, Bold* bold) {
	_output(indentationLevel, "%s", "[ $B$, circle, draw, black!20\n");
	switch (bold->type) {
		case BOLD_ITALIC:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_START", "$, circle, draw, purple ]\n");
			_generateBoldItalic(1 + indentationLevel, bold->boldItalic);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_END", "$, circle, draw, purple ]\n");
			break;
		case BOLD_UNDERLINE:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_START", "$, circle, draw, purple ]\n");
			_generateBoldUnderline(1 + indentationLevel, bold->boldUnderline);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_END", "$, circle, draw, purple ]\n");
			break;
		case BOLD_CONSTANT:
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(bold->startToken),
			        "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, bold->constant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(bold->endToken),
			        "$, circle, draw, purple ]\n");
			break;
		default: logError(_logger, "The specified bold type is unknown: %d", bold->type); break;
	}
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of a boldItalic.
 */
static void _generateBoldItalic(const unsigned int indentationLevel, BoldItalic* boldItalic) {
	_output(indentationLevel, "%s", "[ $BI$, circle, draw, black!20\n");
	_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_START", "$, circle, draw, purple ]\n");
	_generateConstant(1 + indentationLevel, boldItalic->constant);
	_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_END", "$, circle, draw, purple ]\n");
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of a boldUnderline.
 */
static void _generateBoldUnderline(const unsigned int indentationLevel, BoldUnderline* boldUnderline) {
	_output(indentationLevel, "%s", "[ $BU$, circle, draw, black!20\n");
	_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_START", "$, circle, draw, purple ]\n");
	_generateConstant(1 + indentationLevel, boldUnderline->constant);
	_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_START", "$, circle, draw, purple ]\n");
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of an italic.
 */
static void _generateItalic(const unsigned int indentationLevel, Italic* italic) {
	_output(indentationLevel, "%s", "[ $I$, circle, draw, black!20\n");
	switch (italic->type) {
		case ITALIC_BOLD:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_START", "$, circle, draw, purple ]\n");
			_generateItalicBold(1 + indentationLevel, italic->italicBold);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_END", "$, circle, draw, purple ]\n");
			break;
		case ITALIC_UNDERLINE:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_START", "$, circle, draw, purple ]\n");
			_generateItalicUnderline(1 + indentationLevel, italic->italicUnderline);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_END", "$, circle, draw, purple ]\n");
			break;
		case ITALIC_CONSTANT:
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(italic->startToken),
			        "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, italic->constant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(italic->endToken),
			        "$, circle, draw, purple ]\n");
			break;
		default: logError(_logger, "The specified bold type is unknown: %d", italic->type); break;
	}
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of an italicBold.
 */
static void _generateItalicBold(const unsigned int indentationLevel, ItalicBold* italicBold) {
	_output(indentationLevel, "%s", "[ $IB$, circle, draw, black!20\n");
	_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_START", "$, circle, draw, purple ]\n");
	_generateConstant(1 + indentationLevel, italicBold->constant);
	_output(1 + indentationLevel, "%s%s%s", "[ $", "UNDERLINE_END", "$, circle, draw, purple ]\n");
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of an italicUnderline.
 */
static void _generateItalicUnderline(const unsigned int indentationLevel, ItalicUnderline* italicUnderline) {
	_output(indentationLevel, "%s", "[ $IU$, circle, draw, black!20\n");
	_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_START", "$, circle, draw, purple ]\n");
	_generateConstant(1 + indentationLevel, italicUnderline->constant);
	_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_END", "$, circle, draw, purple ]\n");
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of an underline.
 */
static void _generateUnderline(const unsigned int indentationLevel, Underline* underline) {
	_output(indentationLevel, "%s", "[ $U$, circle, draw, black!20\n");
	switch (underline->type) {
		case UNDERLINE_BOLD:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_START", "$, circle, draw, purple ]\n");
			_generateUnderlineBold(1 + indentationLevel, underline->underlineBold);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_END", "$, circle, draw, purple ]\n");
			break;
		case UNDERLINE_ITALIC:
			_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_START", "$, circle, draw, purple ]\n");
			_generateUnderlineItalic(1 + indentationLevel, underline->underlineItalic);
			_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_END", "$, circle, draw, purple ]\n");
			break;
		case UNDERLINE_CONSTANT:
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(underline->startToken),
			        "$, circle, draw, purple ]\n");
			_generateConstant(1 + indentationLevel, underline->constant);
			_output(1 + indentationLevel, "%s%s%s", "[ $", _tokenToCharacter(underline->endToken),
			        "$, circle, draw, purple ]\n");
			break;
		default: logError(_logger, "The specified bold type is unknown: %d", underline->type); break;
	}
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of an underlineBold.
 */
static void _generateUnderlineBold(const unsigned int indentationLevel, UnderlineBold* underlineBold) {
	_output(indentationLevel, "%s", "[ $UB$, circle, draw, black!20\n");
	_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_START", "$, circle, draw, purple ]\n");
	_generateConstant(1 + indentationLevel, underlineBold->constant);
	_output(1 + indentationLevel, "%s%s%s", "[ $", "ITALIC_END", "$, circle, draw, purple ]\n");
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of an underlineItalic.
 */
static void _generateUnderlineItalic(const unsigned int indentationLevel, UnderlineItalic* underlineItalic) {
	_output(indentationLevel, "%s", "[ $UI$, circle, draw, black!20\n");
	_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_START", "$, circle, draw, purple ]\n");
	_generateConstant(1 + indentationLevel, underlineItalic->constant);
	_output(1 + indentationLevel, "%s%s%s", "[ $", "BOLD_END", "$, circle, draw, purple ]\n");
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of a constant.
 */
static void _generateConstant(const unsigned int indentationLevel, Constant* constant) {
	_output(indentationLevel, "%s", "[ $C$, circle, draw, black!20\n");
	switch (constant->type) {
		case STRING_CONSTANT:
			_output(1 + indentationLevel, "%s%s%s", "[ $", constant->value, "$, circle, draw ]\n");
			_generateConstant(1 + indentationLevel, constant->constant);
			break;
		case EMPTY_CONSTANT: _output(1 + indentationLevel, "%s", "[ $\\epsilon$, circle, draw ]\n"); break;
		default: logError(_logger, "The specified factor type is unknown: %d", constant->type); break;
	}
	_output(indentationLevel, "%s", "]\n");
}

/**
 * Converts and expression type to the proper character of the operation
 * involved, or returns '\0' if that's not possible.
 */
static const char* _tokenToCharacter(const Token token) {
	switch (token) {
		case TITLE_START: return "TITLE_START";
		case TITLE_END: return "TITLE_END";
		case HEADING_1_START: return "HEADING_1_START";
		case HEADING_1_END: return "HEADING_1_END";
		case HEADING_2_START: return "HEADING_2_START";
		case HEADING_2_END: return "HEADING_2_END";
		case HEADING_3_START: return "HEADING_3_START";
		case HEADING_3_END: return "HEADING_3_END";
		case PAGE_SKIP_START: return "PAGE_SKIP_START";
		case PAGE_SKIP_END: return "PAGE_SKIP_END";
		case IMAGE_START: return "IMAGE_START";
		case IMAGE_END: return "IMAGE_END";
		case CODE_START: return "CODE_START";
		case CODE_END: return "CODE_END";
		case ESCAPE_START: return "ESCAPE_START";
		case ESCAPE_END: return "ESCAPE_END";
		case EQUATION_START: return "EQUATION_START";
		case EQUATION_END: return "EQUATION_END";
		case UNORDERED_LIST_START: return "UNORDERED_LIST_START";
		case UNORDERED_LIST_END: return "UNORDERED_LIST_END";
		case ORDERED_LIST_START: return "ORDERED_LIST_START";
		case ORDERED_LIST_END: return "ORDERED_LIST_END";
		case BOLD_START: return "BOLD_START";
		case BOLD_END: return "BOLD_END";
		case ITALIC_START: return "ITALIC_START";
		case ITALIC_END: return "ITALIC_END";
		case UNDERLINE_START: return "UNDERLINE_START";
		case UNDERLINE_END: return "UNDERLINE_END";
		case TABLE_START: return "TABLE_START";
		case TABLE_END: return "TABLE_END";
		case LIST_ITEM_START: return "LIST_ITEM_START";
		case LIST_ITEM_END: return "LIST_ITEM_END";
		case CELL_SEPARATOR_START: return "CELL_SEPARATOR_START";
		case CELL_SEPARATOR_END: return "CELL_SEPARATOR_END";
		default:
			logError(_logger, "The specified expression type cannot be converted into character: %d", token);
			return "\0";
	}
}

/**
 * Creates the epilogue of the generated output, that is, the final lines that
 * completes a valid Latex document.
 */
static void _generateEpilogue(const int value) {
	_output(0, "%s%d%s", "            [ $", value,
	        "$, circle, draw, blue ]\n"
	        "        ]\n"
	        "    \\end{forest}\n"
	        "\\end{document}\n\n");
}

/**
 * Creates the prologue of the generated output, a Latex document that renders
 * a tree thanks to the Forest package.
 *
 * @see https://ctan.dcc.uchile.cl/graphics/pgf/contrib/forest/forest-doc.pdf
 */
static void _generatePrologue(void) {
	_output(0, "%s",
	        "\\documentclass{standalone}\n\n"
	        "\\usepackage[utf8]{inputenc}\n"
	        "\\usepackage[T1]{fontenc}\n"
	        "\\usepackage{amsmath}\n"
	        "\\usepackage{forest}\n"
	        "\\usepackage{microtype}\n\n"
	        "\\begin{document}\n"
	        "    \\centering\n"
	        "    \\begin{forest}\n"
	        "        [ \\text{$=$}, circle, draw, purple\n");
}

/**
 * Generates an indentation string for the specified level.
 */
static char* _indentation(const unsigned int level) {
	return indentation(_indentationCharacter, level, _indentationSize);
}

/**
 * Outputs a formatted string to standard output.
 */
static void _output(const unsigned int indentationLevel, const char* const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	char* indentation = _indentation(indentationLevel);
	char* effectiveFormat = concatenate(2, indentation, format);
	vfprintf(stdout, effectiveFormat, arguments);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}

/** PUBLIC FUNCTIONS */

void generate(CompilerState* compilerState) {
	logDebugging(_logger, "Generating final output...");
	_generatePrologue();
	_generateProgram(compilerState->abstractSyntaxtTree);
	_generateEpilogue(compilerState->value);
	logDebugging(_logger, "Generation is done.");
}
