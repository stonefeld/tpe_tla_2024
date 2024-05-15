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
	Factor * factor;
	Expression * expression;
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
%destructor { freeExpression($$); } <expression>
%destructor { freeFactor($$); } <factor>
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
%type <expression> expression
%type <factor> factor
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
 	  expression																			{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

expression:
	  TITLE_START 				constant 			TITLE_END				expression		{ $$ = TokenExpressionSemanticAction(TITLE_START, TITLE_END, $2, $4); }
	| HEADING_1_START 			constant		 	HEADING_1_END			expression  	{ $$ = TokenExpressionSemanticAction(HEADING_1_START, HEADING_1_END, $2, $4); }
	| HEADING_2_START 			constant		 	HEADING_2_END			expression		{ $$ = TokenExpressionSemanticAction(HEADING_1_START, HEADING_1_END, $2, $4); }
	| HEADING_3_START 			constant		 	HEADING_3_END			expression		{ $$ = TokenExpressionSemanticAction(HEADING_1_START, HEADING_1_END, $2, $4); }
	| PAGE_SKIP_START 			constant		 	PAGE_SKIP_END			expression		{ $$ = TokenExpressionSemanticAction(PAGE_SKIP_START, PAGE_SKIP_END, $2, $4); }
	| IMAGE_START 				constant		 	IMAGE_END				expression		{ $$ = TokenExpressionSemanticAction(IMAGE_START, IMAGE_END, $2, $4); }
	| CODE_START 				constant		 	CODE_END				expression		{ $$ = TokenExpressionSemanticAction(CODE_START, CODE_END, $2, $4); }
	| ESCAPE_START 				constant		 	ESCAPE_END				expression		{ $$ = TokenExpressionSemanticAction(ESCAPE_START, ESCAPE_END, $2, $4); }
	| EQUATION_START 			constant		 	EQUATION_END			expression		{ $$ = TokenExpressionSemanticAction(EQUATION_START, EQUATION_END, $2, $4); }
	| factor																				{ $$ = FactorExpressionSemanticAction($1); }
	;

factor:
		UNORDERED_LIST_START 	list				UNORDERED_LIST_END		factor			{ $$ = ListFactorSemanticAction(UNORDERED_LIST_START, UNORDERED_LIST_END, $2, $4); }
	| ORDERED_LIST_START 		list	 			ORDERED_LIST_END		factor			{ $$ = ListFactorSemanticAction(ORDERED_LIST_START, ORDERED_LIST_END, $2, $4); }
	| BOLD_START 				bold	 			BOLD_END				factor			{ $$ = BoldFactorSemanticAction($2, $4); }
	| BOLD_START 				constant 			BOLD_END				factor			{ $$ = TokenFactorSemanticAction(BOLD_START, BOLD_END, $2, $4); }
	| ITALIC_START 				italic		 		ITALIC_END				factor			{ $$ = ItalicFactorSemanticAction($2, $4); }
	| ITALIC_START 				constant 			ITALIC_END				factor			{ $$ = TokenFactorSemanticAction(ITALIC_START, ITALIC_END, $2, $4); }
	| UNDERLINE_START 			underline	 		UNDERLINE_END			factor			{ $$ = UnderlineFactorSemanticAction($2, $4); }
	| UNDERLINE_START 			constant 			UNDERLINE_END			factor			{ $$ = TokenFactorSemanticAction(UNDERLINE_START, UNDERLINE_END, $2, $4); }
	| TABLE_START 				table				TABLE_END				factor			{ $$ = TableFactorSemanticAction($2, $4); }
	| constant 																				{ $$ = ConstantFactorSemanticAction($1); }
;

list:
		LIST_ITEM_START 		constant 			LIST_ITEM_END			list			{ $$ = ListSemanticAction($2, $4); }
	|	LIST_ITEM_START 		constant 			LIST_ITEM_END							{ $$ = LonelyListSemanticAction($2); }
;

table:
		CELL_SEPARATOR_START 	constant 			CELL_SEPARATOR_END		table			{ $$ = TableSemanticAction($2, $4); }
	|	CELL_SEPARATOR_START 	constant 			CELL_SEPARATOR_END						{ $$ = LonelyTableSemanticAction($2); }	
;

bold:
		ITALIC_START			constant					ITALIC_END					{ $$ = LonelyBoldSemanticAction(ITALIC_START, ITALIC_END, $2); }
	|	ITALIC_START 			bold_italic		 			ITALIC_END					{ $$ = ItalicFromBoldSemanticAction($2); }
	|	UNDERLINE_START			constant					UNDERLINE_END				{ $$ = LonelyBoldSemanticAction(UNDERLINE_START, UNDERLINE_END, $2); }
	|	UNDERLINE_START			bold_underline				UNDERLINE_END				{ $$ = UnderlineFromBoldSemanticAction($2); }
;

bold_italic:
		UNDERLINE_START			constant					UNDERLINE_END				{ $$ = LonelyBoldItalicSemanticAction($2); }
;

bold_underline:
		ITALIC_START 			constant					ITALIC_END					{ $$ = LonelyBoldUnderlineSemanticAction($2); }
;

italic:
		BOLD_START 				italic_bold 				BOLD_END					{ $$ = BoldFromItalicSemanticAction($2); }
	|	BOLD_START				constant					BOLD_START					{ $$ = LonelyItalicSemanticAction(BOLD_START, BOLD_END, $2); }
	|	UNDERLINE_START			italic_underline			UNDERLINE_END				{ $$ = UnderlineFromItalicSemanticAction($2); }
	|	UNDERLINE_START			constant					UNDERLINE_END				{ $$ = LonelyItalicSemanticAction(UNDERLINE_START, UNDERLINE_END, $2); }
;

italic_bold:
		UNDERLINE_START			constant					UNDERLINE_END				{ $$ = LonelyItalicBoldSemanticAction($2); }
;

italic_underline:
		BOLD_START 				constant					BOLD_END					{ $$ = LonelyItalicUnderlineSemanticAction($2); }
;

underline:
		BOLD_START 				underline_bold		 		BOLD_END					{ $$ = BoldFromUnderlineSemanticAction($2); }
	|	BOLD_START 				constant			 		BOLD_END					{ $$ = LonelyUnderlineSemanticAction(BOLD_START, BOLD_END, $2); }
	|	ITALIC_START			underline_italic			ITALIC_END					{ $$ = ItalicFromUnderlineSemanticAction($2); }
	|	ITALIC_START			constant					ITALIC_END					{ $$ = LonelyUnderlineSemanticAction(ITALIC_START, ITALIC_END, $2); }
;

underline_bold:
		ITALIC_START			constant					ITALIC_END					{ $$ = LonelyUnderlineBoldSemanticAction($2); }
;

underline_italic:
		BOLD_START 				constant					BOLD_END					{ $$ = LonelyUnderlineItalicSemanticAction($2);}
;

constant:
		STRING					constant												{ $$ = StringConstantSemanticAction($1, $2); }
    |                                                                                   { $$ = EmptyConstantSemanticAction();}
;

%%
