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

typedef struct Table Table;
typedef struct List List;

typedef struct Constant Constant;
typedef struct Tag Tag;
typedef struct Tags Tags;
typedef struct Title Title;
typedef struct Program Program;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum TitleType {
	TITLE,
	NO_TITLE,
	LONELY_TITLE,
};

enum TagsType {
	TAGS,
	END_TAG,
};

enum TagType {
	HEADING_1,
	HEADING_2,
	HEADING_3,
	PAGE_SKIP,
	IMAGE,
	CODE,
	ESCAPE,
	EQUATION,
	ORDERED_LIST,
	UNORDERED_LIST,
	BOLD_CONSTANT,
	BOLD,
	ITALIC_CONSTANT,
	ITALIC,
	UNDERLINE_CONSTANT,
	UNDERLINE,
	TABLE,
	STRING_TAG,
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
	BOLD_ITALIC_CONSTANT,
	BOLD_UNDERLINE,
	BOLD_UNDERLINE_CONSTANT,
};

enum ItalicType {
	ITALIC_BOLD,
	ITALIC_BOLD_CONSTANT,
	ITALIC_UNDERLINE,
	ITALIC_UNDERLINE_CONSTANT,
};

enum UnderlineType {
	UNDERLINE_BOLD,
	UNDERLINE_BOLD_CONSTANT,
	UNDERLINE_ITALIC,
	UNDERLINE_ITALIC_CONSTANT,
};

enum ConstantType {
	STRING_CONSTANT,
	EMPTY_CONSTANT,
};

typedef enum TitleType TitleType;
typedef enum TagsType TagsType;
typedef enum TagType TagType;
typedef enum ConstantType ConstantType;
typedef enum ListType ListType;
typedef enum TableType TableType;
typedef enum BoldType BoldType;
typedef enum ItalicType ItalicType;
typedef enum UnderlineType UnderlineType;

struct Constant {
	// TODO: Investigar esto
	union {
		Constant *constant;
	};
	char *value;
	ConstantType type;
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
		Constant *constant;
	};
	BoldType type;
};

struct Italic {
	union {
		ItalicBold *italicBold;
		ItalicUnderline *italicUnderline;
		Constant *constant;
	};
	ItalicType type;
};

struct Underline {
	union {
		UnderlineBold *underlineBold;
		UnderlineItalic *underlineItalic;
		Constant *constant;
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

struct Tag {
	union {
		List *list;
		Table *table;
		Bold *bold;
		Italic *italic;
		Underline *underline;
		Constant *constant;
		char *value;
	};
	TagType type;
};

struct Tags {
	union {
		Tags *tags;
	};
	Tag *tag;
	TagsType type;
};

struct Title {
	union {
		Constant *lonelyConstant;
		Tags *lonelyTags;
		struct {
			Constant *constant;
			Tags *tags;
		};
	};
	TitleType type;
};

struct Program {
	Title *title;
};

/**
 * Node recursive destructors.
 */
void freeProgram(Program *program);
void freeTitle(Title *title);
void freeTags(Tags *tags);
void freeTag(Tag *tag);
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
