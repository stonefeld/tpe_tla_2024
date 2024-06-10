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

/* %x Contexts */
%x CANA
%x CODE

%x UNORDEREDLIST
%x ORDEREDLIST
%x TABLE

%x BOLD
%x BOLDITALIC
%x BOLDITALICUNDERLINE
%x BOLDUNDERLINE
%x BOLDUNDERLINEITALIC

%x ITALIC
%x ITALICBOLD
%x ITALICBOLDUNDERLINE
%x ITALICUNDERLINE
%x ITALICUNDERLINEBOLD

%x UNDERLINE
%x UNDERLINEBOLD
%x UNDERLINEBOLDITALIC
%x UNDERLINEITALIC
%x UNDERLINEITALICBOLD


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

UNORDEREDLIST 💥
NOUNORDEREDLIST [^💥🎯 \n]+
ORDEREDLIST 🔢
NOORDEREDLIST [^🔢🎯 \n]+
TABLE 📊
NOTABLE [^📊🤸‍♂️ \n]+

BOLD 👨‍🦲
ITALIC 🤌
UNDERLINE 📉
NOBOLDITALICUNDERLINE [^👨‍🦲🤌📉\n]+

%%

"🤴"                                            { return TitleLexemeAction(createLexicalAnalyzerContext()); }
"👴"                                            { return Heading1LexemeAction(createLexicalAnalyzerContext()); }
"👨"                                            { return Heading2LexemeAction(createLexicalAnalyzerContext()); }
"👶"                                            { return Heading3LexemeAction(createLexicalAnalyzerContext()); }
"🐇"                                            { return PageSkipLexemeAction(createLexicalAnalyzerContext()); }
"💥"                                            { BEGIN(UNORDEREDLIST);return UnorderedListLexemeAction(createLexicalAnalyzerContext()); }
"🔢"                                            { BEGIN(ORDEREDLIST); return OrderedListLexemeAction(createLexicalAnalyzerContext()); }
"📊"                                            { BEGIN(TABLE); return TableLexemeAction(createLexicalAnalyzerContext()); }
"📷"                                            { return ImageLexemeAction(createLexicalAnalyzerContext()); }
"👨‍🦲"                                            { BEGIN(BOLD);return BoldLexemeAction(createLexicalAnalyzerContext()); }
"🤌"                                            { BEGIN(ITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
"📉"                                            { BEGIN(UNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
"💻"                                            { BEGIN(CODE); return CodeLexemeAction(createLexicalAnalyzerContext()); }
"👮‍♂️"                                            { BEGIN(CANA); return EscapedLexemeAction(createLexicalAnalyzerContext()); }

<CANA>"👮‍♂️"                                      { BEGIN(INITIAL); return EscapedLexemeAction(createLexicalAnalyzerContext()); }
<CANA>[\n]+                                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
<CANA>[ ]+                                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<CANA>{NOCANA}                                  { return StringLexemeAction(createLexicalAnalyzerContext()); }

<CODE>"💻"                                      { BEGIN(INITIAL); return CodeLexemeAction(createLexicalAnalyzerContext()); }
<CODE>[\n ]+                                    { return StringLexemeAction(createLexicalAnalyzerContext()); }
<CODE>{NOCODE}                                  { return StringLexemeAction(createLexicalAnalyzerContext()); }

<UNORDEREDLIST>"💥"                             { BEGIN(INITIAL); return UnorderedListLexemeAction(createLexicalAnalyzerContext()); }
<UNORDEREDLIST>"🎯"                             { return ListItemLexemeAction(createLexicalAnalyzerContext()); }
<UNORDEREDLIST>[[:space:]]                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNORDEREDLIST>{NOUNORDEREDLIST}                { return StringLexemeAction(createLexicalAnalyzerContext()); }

<ORDEREDLIST>"🔢"                               { BEGIN(INITIAL); return OrderedListLexemeAction(createLexicalAnalyzerContext()); }
<ORDEREDLIST>"🎯"                               { return ListItemLexemeAction(createLexicalAnalyzerContext()); }
<ORDEREDLIST>[[:space:]]                        { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ORDEREDLIST>{NOORDEREDLIST}                    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<TABLE>"📊"                                     { BEGIN(INITIAL); return TableLexemeAction(createLexicalAnalyzerContext()); }
<TABLE>"🤸‍♂️"                                     { return CellSeparatorLexemeAction(createLexicalAnalyzerContext()); }
<TABLE>[[:space:]]                              { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<TABLE>{NOTABLE}                                { return StringLexemeAction(createLexicalAnalyzerContext()); }

<BOLD>"👨‍🦲"                                      { BEGIN(INITIAL); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>"🤌"                                      { BEGIN(BOLDITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>"📉"                                      { BEGIN(BOLDUNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>[\n]+                                     { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>{NOBOLDITALICUNDERLINE}                   { return StringLexemeAction(createLexicalAnalyzerContext()); }

<BOLDITALIC>"🤌"                                { BEGIN(BOLD); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALIC>"📉"                                { BEGIN(BOLDITALICUNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALIC>[\n]+                               { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALIC>{NOBOLDITALICUNDERLINE}             { return StringLexemeAction(createLexicalAnalyzerContext()); }

<BOLDITALICUNDERLINE>"📉"                       { BEGIN(BOLDITALIC); return UnderlineLexemeAction(createLexicalAnalyzerContext());  }
<BOLDITALICUNDERLINE>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALICUNDERLINE>{NOBOLDITALICUNDERLINE}    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<BOLDUNDERLINE>"📉"                             { BEGIN(BOLD); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINE>"🤌"                             { BEGIN(BOLDUNDERLINEITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINE>[\n]+                            { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINE>{NOBOLDITALICUNDERLINE}          { return StringLexemeAction(createLexicalAnalyzerContext()); }

<BOLDUNDERLINEITALIC>"🤌"                       { BEGIN(BOLDUNDERLINE); return ItalicLexemeAction(createLexicalAnalyzerContext());  }
<BOLDUNDERLINEITALIC>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINEITALIC>{NOBOLDITALICUNDERLINE}    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<ITALIC>"🤌"                                    { BEGIN(INITIAL); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>"👨‍🦲"                                    { BEGIN(ITALICBOLD); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>"📉"                                    { BEGIN(ITALICUNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>[\n]+                                   { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>{NOBOLDITALICUNDERLINE}                 { return StringLexemeAction(createLexicalAnalyzerContext()); }

<ITALICBOLD>"👨‍🦲"                                { BEGIN(ITALIC); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLD>"📉"                                { BEGIN(ITALICBOLDUNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLD>[\n]+                               { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLD>{NOBOLDITALICUNDERLINE}             { return StringLexemeAction(createLexicalAnalyzerContext()); }

<ITALICBOLDUNDERLINE>"📉"                       { BEGIN(ITALICBOLD); return UnderlineLexemeAction(createLexicalAnalyzerContext());  }
<ITALICBOLDUNDERLINE>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLDUNDERLINE>{NOBOLDITALICUNDERLINE}    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<ITALICUNDERLINE>"📉"                           { BEGIN(ITALIC); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINE>"👨‍🦲"                           { BEGIN(ITALICUNDERLINEBOLD); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINE>[\n]+                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINE>{NOBOLDITALICUNDERLINE}        { return StringLexemeAction(createLexicalAnalyzerContext()); }

<ITALICUNDERLINEBOLD>"👨‍🦲"                       { BEGIN(ITALICUNDERLINE); return BoldLexemeAction(createLexicalAnalyzerContext());  }
<ITALICUNDERLINEBOLD>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINEBOLD>{NOBOLDITALICUNDERLINE}    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINE>"📉"                                 { BEGIN(INITIAL); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>"👨‍🦲"                                 { BEGIN(UNDERLINEBOLD); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>"🤌"                                 { BEGIN(UNDERLINEITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>[\n]+                                { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>{NOBOLDITALICUNDERLINE}              { return StringLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINEBOLD>"👨‍🦲"                             { BEGIN(UNDERLINE); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLD>"🤌"                             { BEGIN(UNDERLINEBOLDITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLD>[\n]+                            { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLD>{NOBOLDITALICUNDERLINE}          { return StringLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINEBOLDITALIC>"🤌"                       { BEGIN(UNDERLINEBOLD); return ItalicLexemeAction(createLexicalAnalyzerContext());  }
<UNDERLINEBOLDITALIC>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLDITALIC>{NOBOLDITALICUNDERLINE}    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINEITALIC>"🤌"                           { BEGIN(UNDERLINE); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALIC>"👨‍🦲"                           { BEGIN(UNDERLINEITALICBOLD); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALIC>[\n]+                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALIC>{NOBOLDITALICUNDERLINE}        { return StringLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINEITALICBOLD>"👨‍🦲"                       { BEGIN(UNDERLINEITALIC); return BoldLexemeAction(createLexicalAnalyzerContext());  }
<UNDERLINEITALICBOLD>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALICBOLD>{NOBOLDITALICUNDERLINE}    { return StringLexemeAction(createLexicalAnalyzerContext()); }

{TEXT}									        { return StringLexemeAction(createLexicalAnalyzerContext()); }
[[:space:]]                                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
.                                               { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"