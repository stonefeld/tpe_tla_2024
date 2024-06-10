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
%x CANA
%x CODE

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

TEXT [][a-zA-Z0-9*@&=+$/?%#_~|<>{}()'"\\!:;.,\-]+
CANA 👮‍♂️
NOCANA [^👮‍♂️ \n]+
CODE 💻
NOCODE [^💻 \n]+

%%

"🤴"									{ return TitleLexemeAction(createLexicalAnalyzerContext()); }
"👴"									{ return Heading1LexemeAction(createLexicalAnalyzerContext()); }
"👨"									{ return Heading2LexemeAction(createLexicalAnalyzerContext()); }
"👶"									{ return Heading3LexemeAction(createLexicalAnalyzerContext()); }
"🐇"									{ return PageSkipLexemeAction(createLexicalAnalyzerContext()); }
"💥"									{ return UnorderedListLexemeAction(createLexicalAnalyzerContext()); }
"🔢"									{ return OrderedListLexemeAction(createLexicalAnalyzerContext()); }
"🎯"                                    { return ListItemLexemeAction(createLexicalAnalyzerContext()); }
"🤸‍♂️"                                    { return CellSeparatorLexemeAction(createLexicalAnalyzerContext()); }
"📷"									{ return ImageLexemeAction(createLexicalAnalyzerContext()); }
"👨‍🦲"									   { return BoldLexemeAction(createLexicalAnalyzerContext()); }
"🤌"							        { return ItalicLexemeAction(createLexicalAnalyzerContext()); }
"📉"                                    { return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
"📊"                                    { return TableLexemeAction(createLexicalAnalyzerContext()); }
"💻"                                    { BEGIN(CODE); return CodeLexemeAction(createLexicalAnalyzerContext()); }
"👮‍♂️"                                    { BEGIN(CANA); return EscapedLexemeAction(createLexicalAnalyzerContext()); }

<CANA>"👮‍♂️"                              { BEGIN(INITIAL); return EscapedLexemeAction(createLexicalAnalyzerContext()); }
<CANA>[\n]+                             { return StringLexemeAction(createLexicalAnalyzerContext()); }
<CANA>[ ]+						        { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<CANA>{NOCANA}                          { return StringLexemeAction(createLexicalAnalyzerContext()); }

<CODE>"💻"                              { BEGIN(INITIAL); return CodeLexemeAction(createLexicalAnalyzerContext()); }
<CODE>[\n]+                             { return StringLexemeAction(createLexicalAnalyzerContext()); }
<CODE>[ ]+						        { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<CODE>{NOCODE}                          { return StringLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						    { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
{TEXT}									{ return StringLexemeAction(createLexicalAnalyzerContext()); }
.                                       { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"