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

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

TEXT [][a-zA-Z0-9*@&=+$/?%#_~|<>{}()'"\\!:;.,\-]+
CANA 👮‍♂️
NOCANA ^{CANA}+

%%

"🤴"									{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"👴"									{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"👨"									{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"👶"									{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"🐇"									{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"💥"									{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"🔢"									{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"🎯"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"🤸‍♂️"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"📷"									{ return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"👨‍🦲"									   { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"🤌"							         { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"📉"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"📊"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"💻"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"👮‍♂️"                                    { BEGIN(CANA); return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"🤓"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }


[[:space:]]+						    { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<CANA>"👮‍♂️"                             { BEGIN(INITIAL); return DoubleLexemeAction(createLexicalAnalyzerContext()); }
<CANA>{NOCANA}                             { return StringLexemeAction(createLexicalAnalyzerContext()); }
%%

#include "FlexExport.h"
