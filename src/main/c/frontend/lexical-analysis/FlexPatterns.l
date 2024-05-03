%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */

/* %x MULTILINE_COMMENT */

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

/* "/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); } */
/* <MULTILINE_COMMENT>""				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); } */ */
/* <MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); } */
/* <MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); } */
/* <MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); } */

/* "-"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); } */
/* "*"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); } */
/* "/"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); } */
/* "+"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); } */

/* "("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); } */
/* ")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); } */

"🤴"									{ return SingleLexemeAction(createLexicalAnalyzerContext()); }
"👴"									{ return SingleLexemeAction(createLexicalAnalyzerContext()); }
"👨"									{ return SingleLexemeAction(createLexicalAnalyzerContext()); }
"👶"									{ return SingleLexemeAction(createLexicalAnalyzerContext()); }
"🐇"									{ return SingleLexemeAction(createLexicalAnalyzerContext()); }
"💥"									{ return SingleLexemeAction(createLexicalAnalyzerContext()); }
"🔢"									{ return SingleLexemeAction(createLexicalAnalyzerContext()); }
"🤸‍♂️"                                    { return SingleLexemeAction(createLexicalAnalyzerContext()); }
"📷"									{ return SingleLexemeAction(createLexicalAnalyzerContext()); }

"👨‍🦲"									   { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"\U0001F90C"							{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"📉"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"📊"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"💻"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"👮‍♂️"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"🤓"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }

[[:string:]]+						    { return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						    { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									    { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
