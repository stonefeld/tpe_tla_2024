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

typedef struct Text Text;
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
	BOLD_TEXT,
	BOLD,
	ITALIC_TEXT,
	ITALIC,
	UNDERLINE_TEXT,
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
	BOLD_ITALIC_TEXT,
	BOLD_UNDERLINE,
	BOLD_UNDERLINE_TEXT,
};

enum ItalicType {
	ITALIC_BOLD,
	ITALIC_BOLD_TEXT,
	ITALIC_UNDERLINE,
	ITALIC_UNDERLINE_TEXT,
};

enum UnderlineType {
	UNDERLINE_BOLD,
	UNDERLINE_BOLD_TEXT,
	UNDERLINE_ITALIC,
	UNDERLINE_ITALIC_TEXT,
};

enum TextType {
	STRING_TEXT,
	EMPTY_TEXT,
};

typedef enum TitleType TitleType;
typedef enum TagsType TagsType;
typedef enum TagType TagType;
typedef enum TextType TextType;
typedef enum ListType ListType;
typedef enum TableType TableType;
typedef enum BoldType BoldType;
typedef enum ItalicType ItalicType;
typedef enum UnderlineType UnderlineType;

struct Text {
	// TODO: Investigar esto
	union {
		Text *text;
	};
	char *value;
	TextType type;
};

struct BoldItalic {
	Text *text;
};

struct BoldUnderline {
	Text *text;
};

struct ItalicBold {
	Text *text;
};

struct ItalicUnderline {
	Text *text;
};

struct UnderlineBold {
	Text *text;
};

struct UnderlineItalic {
	Text *text;
};

struct Bold {
	union {
		BoldItalic *boldItalic;
		BoldUnderline *boldUnderline;
		Text *text;
	};
	BoldType type;
};

struct Italic {
	union {
		ItalicBold *italicBold;
		ItalicUnderline *italicUnderline;
		Text *text;
	};
	ItalicType type;
};

struct Underline {
	union {
		UnderlineBold *underlineBold;
		UnderlineItalic *underlineItalic;
		Text *text;
	};
	UnderlineType type;
};

struct List {
	union {
		struct {
			Text *text;
			List *item;
		};
		Text *lonelyText;
	};
	ListType type;
};

struct Table {
	union {
		struct {
			Text *text;
			Table *column;
		};
		Text *lonelyText;
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
		Text *text;
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
		Text *lonelyText;
		Tags *lonelyTags;
		struct {
			Text *text;
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
void freeText(Text *text);

#endif
