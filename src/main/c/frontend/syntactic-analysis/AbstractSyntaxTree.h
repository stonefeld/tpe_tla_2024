#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include <stdlib.h>

#include "../../shared/Logger.h"

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */
typedef struct UnderlineItalic UnderlineItalic;
typedef struct UnderlineBold UnderlineBold;
typedef struct Underline Underline;

typedef struct ItalicUnderline ItalicUnderline;
typedef struct ItalicBold ItalicBold;
typedef struct Italic Italic;

typedef struct BoldUnderline BoldUnderline;
typedef struct BoldItalic BoldItalic;
typedef struct Bold Bold;

typedef struct Constant Constant;
typedef struct Table Table;
typedef struct List List;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum StartToken {
	TITLE_START,
	HEADING_1_START,
	HEADING_2_START,
	HEADING_3_START,
	PAGE_SKIP_START,
	UNORDERED_LIST_START,
	ORDERED_LIST_START,
	LIST_ITEM_START,
	CELL_SEPARATOR_START,
	IMAGE_START,
	BOLD_START,
	ITALIC_START,
	UNDERLINE_START,
	TABLE_START,
	CODE_START,
	ESPACE_START,
	EQUATION_START,
};
typedef enum StartToken StartToken;

enum EndToken {
	TITLE_END,
	HEADING_1_END,
	HEADING_2_END,
	HEADING_3_END,
	PAGE_SKIP_END,
	UNORDERED_LIST_END,
	ORDERED_LIST_END,
	LIST_ITEM_END,
	CELL_SEPARATOR_END,
	IMAGE_END,
	BOLD_END,
	ITALIC_END,
	UNDERLINE_END,
	TABLE_END,
	CODE_END,
	ESPACE_END,
};
typedef enum EndToken EndToken;

enum ExpressionType {
	TOKEN_EXPRESSION,
	FACTOR,
};

enum FactorType {
	LIST,
	BOLD,
	ITALIC,
	UNDERLINE,
	TABLE,
	TOKEN,
	CONSTANT,
};

enum ListType {
	LONELY_ITEM,
	MULTIPLE_ITEMS,
};

enum TableType {
	LONELY_COLUMN,
	MULTIPLE_COLUMNS,
};

enum BoldType {
	BOLD_ITALIC,
	BOLD_UNDERLINE,
	BOLD_CONSTANT,
};

enum ItalicType {
	ITALIC_BOLD,
	ITALIC_UNDERLINE,
	ITALIC_CONSTANT,
};

enum UnderlineType {
	UNDERLINE_BOLD,
	UNDERLINE_ITALIC,
	UNDERLINE_CONSTANT,
};

typedef enum BoldType BoldType;
typedef enum ItalicType ItalicType;
typedef enum UnderlineType UnderlineType;
typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;
typedef enum ListType ListType;
typedef enum TableType TableType;

struct Constant {
	const char *value;
};

struct BoldItalic {
	Constant *constant;
};

struct BoldUnderline {
	Constant *constant;
};

struct ItalicBold {
	Constant *constant;
};

struct ItalicUnderline {
	Constant *constant;
};

struct UnderlineBold {
	Constant *constant;
};

struct UnderlineItalic {
	Constant *constant;
};

struct Bold {
	union {
		BoldItalic *boldItalic;
		BoldUnderline *boldUnderline;
		struct {
			StartToken startToken;
			Constant *constant;
			EndToken endToken;
		};
	};
	BoldType type;
};

struct Italic {
	union {
		ItalicBold *italicBold;
		ItalicUnderline *italicUnderline;
		struct {
			StartToken startToken;
			Constant *constant;
			EndToken endToken;
		};
	};
	ItalicType type;
};

struct Underline {
	union {
		UnderlineBold *underlineBold;
		UnderlineItalic *underlineItalic;
		struct {
			StartToken startToken;
			Constant *constant;
			EndToken endToken;
		};
	};
	UnderlineType type;
};

struct List {
	union {
		struct {
			Constant *constant;
			List *item;
		};
		Constant *lonelyConstant;
	};
	ListType type;
};

struct Table {
	union {
		struct {
			Constant *constant;
			Table *column;
		};
		Constant *lonelyConstant;
	};
	TableType type;
};

struct Factor {
	union {
		struct {
			StartToken startListToken;
			List *list;
			EndToken endListToken;
			Factor *listFactor;
		};
		struct {
			Bold *bold;
			Factor* boldFactor;
		};
		struct {
			Italic *italic;
			Factor* italicFactor;
		};
		struct {
			Underline *underline;
			Factor* underlineFactor;
		};
		struct {
			Table *table;
			Factor* tableFactor;
		};
		struct {
			StartToken startToken;
			Constant *tokenConstant;
			EndToken endToken;
			Factor *tokenFactor;
		};
		Constant *lonelyConstant;
	};
	FactorType type;
};

struct Expression {
	union {
		Factor *factor;
		struct {
			StartToken startToken;
			Constant *constant;
			EndToken endToken;
			Expression *expression;
		};
	};
	ExpressionType type;
};

struct Program {
	Expression *expression;
};

/**
 * Node recursive destructors.
 */
void freeProgram(Program *program);
void freeExpression(Expression *expression);
void freeFactor(Factor *factor);
void freeList(List *list);
void freeTable(Table *table);
void freeBold(Bold *bold);
void freeItalic(Italic *italic);
void freeUnderline(Underline *underline);
void freeBoldItalic(BoldItalic *boldItalic);
void freeBoldUnderline(BoldUnderline *boldUnderline);
void freeItalicBold(ItalicBold *italicBold);
void freeItalicUnderline(ItalicUnderline *italicUnderline);
void freeUnderlineBold(UnderlineBold *underlineBold);
void freeUnderlineItalic(UnderlineItalic *underlineItalic);
void freeConstant(Constant *constant);

#endif
