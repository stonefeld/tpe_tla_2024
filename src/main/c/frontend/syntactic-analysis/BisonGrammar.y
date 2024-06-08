%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	char * string;
	Token token;

	/** Non-terminals. */

	UnderlineItalic *underlineItalic;
	UnderlineBold *underlineBold;
	Underline *underline;

	ItalicUnderline *italicUnderline;
	ItalicBold *italicBold;
	Italic *italic;

	BoldUnderline *boldUnderline;
	BoldItalic *boldItalic;
	Bold *bold;

	Table *table;
	List *list;

	Constant * constant;
	Tag * tag;
	Tags * tags;
	Title * title;
	Program * program;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { freeConstant($$); } <constant>
%destructor { freeTitle($$); } <title>
%destructor { freeTag($$); } <tag>
%destructor { freeProgram($$); } <program>
*/

/** Terminals. */
%token <token> UNKNOWN
%token <string> STRING
%token <token> TITLE_END
%token <token> TITLE_START
%token <token> HEADING_1_END
%token <token> HEADING_1_START
%token <token> HEADING_2_END
%token <token> HEADING_2_START
%token <token> HEADING_3_END
%token <token> HEADING_3_START
%token <token> PAGE_SKIP_END
%token <token> PAGE_SKIP_START
%token <token> UNORDERED_LIST_END
%token <token> UNORDERED_LIST_START
%token <token> ORDERED_LIST_END
%token <token> ORDERED_LIST_START
%token <token> LIST_ITEM_END
%token <token> LIST_ITEM_START
%token <token> CELL_SEPARATOR_END
%token <token> CELL_SEPARATOR_START
%token <token> IMAGE_END
%token <token> IMAGE_START
%token <token> BOLD_END
%token <token> BOLD_START
%token <token> ITALIC_END
%token <token> ITALIC_START
%token <token> UNDERLINE_END
%token <token> UNDERLINE_START
%token <token> TABLE_END
%token <token> TABLE_START
%token <token> CODE_END
%token <token> CODE_START
%token <token> ESCAPE_END
%token <token> ESCAPE_START
%token <token> EQUATION_END
%token <token> EQUATION_START

/* %token <token> UNKNOWN */

/** Non-terminals. */
%type <constant> constant
%type <list> list
%type <bold> bold
%type <boldItalic> bold_italic
%type <boldUnderline> bold_underline
%type <italic> italic
%type <italicBold> italic_bold
%type <italicUnderline> italic_underline
%type <underline> underline
%type <underlineBold> underline_bold
%type <underlineItalic> underline_italic
%type <table> table
%type <tag> tag
%type <tags> tags
%type <title> title
%type <program> program

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */

/* %left STRING
%left UNDERLINE_START UNDERLINE_END
%left ITALIC_START ITALIC_END
%left BOLD_START BOLD_END
%left LIST_ITEM_START LIST_ITEM_END CELL_SEPARATOR_START CELL_SEPARATOR_END
%left TABLE_START TABLE_END UNORDERED_LIST_START UNORDERED_LIST_END ORDERED_LIST_START ORDERED_LIST_END
%left TITLE_START TITLE_END HEADING_1_START HEADING_1_END HEADING_2_START HEADING_2_END HEADING_3_START HEADING_3_END PAGE_SKIP_START PAGE_SKIP_END IMAGE_START IMAGE_END CODE_START CODE_END ESCAPE_START ESCAPE_END EQUATION_START EQUATION_END */

%%

program:
 	  title																					{ $$ = ProgramSemanticAction(currentCompilerState(), $1); }
	;

title:
		TITLE_START 			constant 			TITLE_END				tags			{ $$ = TitleSemanticAction($2, $4); }
	|	tags																				{ $$ = EmptyTitleSemanticAction($1); }
	;

tags:
		tag						tags														{ $$ = TagsSemanticAction($1, $2); }
	|	tag																					{ $$ = EndTagSemanticAction($1); }
	;

tag:
	  HEADING_1_START 			constant		 	HEADING_1_END						  	{ $$ = Heading1SemanticAction($2); }
	| HEADING_2_START 			constant		 	HEADING_2_END							{ $$ = Heading2SemanticAction($2); }
	| HEADING_3_START 			constant		 	HEADING_3_END							{ $$ = Heading3SemanticAction($2); }
	| PAGE_SKIP_START 			constant		 	PAGE_SKIP_END							{ $$ = PageSkipSemanticAction($2); }
	| IMAGE_START 				constant		 	IMAGE_END								{ $$ = ImageSemanticAction($2); }
	| CODE_START 				constant		 	CODE_END								{ $$ = CodeSemanticAction($2); }
	| ESCAPE_START 				constant		 	ESCAPE_END								{ $$ = EscapeSemanticAction($2); }
	| EQUATION_START 			constant		 	EQUATION_END							{ $$ = EquationSemanticAction($2); }
	| UNORDERED_LIST_START 		list				UNORDERED_LIST_END						{ $$ = UnorderedListSemanticAction($2); }
	| ORDERED_LIST_START 		list	 			ORDERED_LIST_END						{ $$ = OrderedListSemanticAction($2); }
	| BOLD_START 				bold	 			BOLD_END								{ $$ = BoldSemanticAction($2); }
	| BOLD_START 				constant 			BOLD_END								{ $$ = BoldConstantSemanticAction($2); }
	| ITALIC_START 				italic		 		ITALIC_END								{ $$ = ItalicSemanticAction($2); }
	| ITALIC_START 				constant 			ITALIC_END								{ $$ = ItalicConstantSemanticAction($2); }
	| UNDERLINE_START 			underline	 		UNDERLINE_END							{ $$ = UnderlineSemanticAction($2); }
	| UNDERLINE_START 			constant 			UNDERLINE_END							{ $$ = UnderlineConstantSemanticAction($2); }
	| TABLE_START 				table				TABLE_END								{ $$ = TableSemanticAction($2); }
	| STRING																				{ $$ = StringTagSemanticAction($1); }
	;

list:
		LIST_ITEM_START 		constant 			LIST_ITEM_END			list			{ $$ = ItemSemanticAction($2, $4); }
	|	LIST_ITEM_START 		constant 			LIST_ITEM_END							{ $$ = LonelyItemSemanticAction($2); }
;

table:
		CELL_SEPARATOR_START 	constant 			CELL_SEPARATOR_END		table			{ $$ = CellSeparatorSemanticAction($2, $4); }
	|	CELL_SEPARATOR_START 	constant 			CELL_SEPARATOR_END						{ $$ = LonelyCellSeparatorSemanticAction($2); }	
;

bold:
		ITALIC_START			constant					ITALIC_END					{ $$ = BoldItalicConstantSemanticAction($2); }
	|	ITALIC_START 			bold_italic		 			ITALIC_END					{ $$ = BoldItalicSemanticAction($2); }
	|	UNDERLINE_START			constant					UNDERLINE_END				{ $$ = BoldUnderlineConstantSemanticAction($2); }
	|	UNDERLINE_START			bold_underline				UNDERLINE_END				{ $$ = BoldUnderlineSemanticAction($2); }
;

bold_italic:
		UNDERLINE_START			constant					UNDERLINE_END				{ $$ = BoldItalicUnderlineSemanticAction($2); }
;

bold_underline:
		ITALIC_START 			constant					ITALIC_END					{ $$ = BoldUnderlineItalicSemanticAction($2); }
;

italic:
		BOLD_START 				italic_bold 				BOLD_END					{ $$ = ItalicBoldSemanticAction($2); }
	|	BOLD_START				constant					BOLD_START					{ $$ = ItalicBoldConstantSemanticAction($2); }
	|	UNDERLINE_START			italic_underline			UNDERLINE_END				{ $$ = ItalicUnderlineSemanticAction($2); }
	|	UNDERLINE_START			constant					UNDERLINE_END				{ $$ = ItalicUnderlineConstantSemanticAction($2); }
;

italic_bold:
		UNDERLINE_START			constant					UNDERLINE_END				{ $$ = ItalicBoldUnderlineSemanticAction($2); }
;

italic_underline:
		BOLD_START 				constant					BOLD_END					{ $$ = ItalicUnderlineBoldSemanticAction($2); }
;

underline:
		BOLD_START 				underline_bold		 		BOLD_END					{ $$ = UnderlineBoldSemanticAction($2); }
	|	BOLD_START 				constant			 		BOLD_END					{ $$ = UnderlineBoldConstantSemanticAction($2); }
	|	ITALIC_START			underline_italic			ITALIC_END					{ $$ = UnderlineItalicSemanticAction($2); }
	|	ITALIC_START			constant					ITALIC_END					{ $$ = UnderlineItalicConstantSemanticAction($2); }
;

underline_bold:
		ITALIC_START			constant					ITALIC_END					{ $$ = UnderlineBoldItalicSemanticAction($2); }
;

underline_italic:
		BOLD_START 				constant					BOLD_END					{ $$ = UnderlineItalicBoldSemanticAction($2);}
;

constant:
		STRING																			{ $$ = StringConstantSemanticAction($1); }
    |                                                                                   { $$ = EmptyConstantSemanticAction();}
;

%%
