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
"🤌"							        { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"📉"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"📊"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"💻"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"👮‍♂️"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }
"🤓"                                    { return DoubleLexemeAction(createLexicalAnalyzerContext()); }

"\\.\\*"    						    { return StringLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						    { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									    { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
