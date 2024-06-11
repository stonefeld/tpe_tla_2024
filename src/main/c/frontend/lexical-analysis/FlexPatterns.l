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
%x LISTUNORDEREDITEM
%x ORDEREDLIST
%x LISTORDEREDITEM
%x TABLE
%x CELLSEPARATOR

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

TEXT [][a-zA-Z0-9*@&=+$/?%#_~|<>{}()'"\\!:;.,\- ]+

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
<CANA>.|[\n]+                                   { return StringLexemeAction(createLexicalAnalyzerContext()); }
<CANA>[ ]+                                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<CODE>"💻"                                      { BEGIN(INITIAL); return CodeLexemeAction(createLexicalAnalyzerContext()); }
<CODE>.|[\n ]+                                   { return StringLexemeAction(createLexicalAnalyzerContext()); }

<UNORDEREDLIST>"💥"                             { BEGIN(INITIAL); return UnorderedListLexemeAction(createLexicalAnalyzerContext()); }
<UNORDEREDLIST>"🎯"                             { BEGIN(LISTUNORDEREDITEM); return ListItemLexemeAction(createLexicalAnalyzerContext()); }
<UNORDEREDLIST>[[:space:]]                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNORDEREDLIST>.                                { return StringLexemeAction(createLexicalAnalyzerContext()); }

<LISTUNORDEREDITEM>"🎯"                         { BEGIN(UNORDEREDLIST); return ListItemLexemeAction(createLexicalAnalyzerContext()); }
<LISTUNORDEREDITEM>.|[\n]+                      { return StringLexemeAction(createLexicalAnalyzerContext()); }
<LISTUNORDEREDITEM>[ ]+                         { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<ORDEREDLIST>"🔢"                               { BEGIN(INITIAL); return OrderedListLexemeAction(createLexicalAnalyzerContext()); }
<ORDEREDLIST>"🎯"                               { BEGIN(LISTORDEREDITEM); return ListItemLexemeAction(createLexicalAnalyzerContext()); }
<ORDEREDLIST>[[:space:]]                        { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ORDEREDLIST>.                                  { return StringLexemeAction(createLexicalAnalyzerContext()); }

<LISTORDEREDITEM>"🎯"                           { BEGIN(ORDEREDLIST); return ListItemLexemeAction(createLexicalAnalyzerContext()); }
<LISTORDEREDITEM>.|[\n]+                        { return StringLexemeAction(createLexicalAnalyzerContext()); }
<LISTORDEREDITEM>[ ]+                           { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<TABLE>"📊"                                     { BEGIN(INITIAL); return TableLexemeAction(createLexicalAnalyzerContext()); }
<TABLE>"🤸‍♂️"                                     { BEGIN(CELLSEPARATOR); return CellSeparatorLexemeAction(createLexicalAnalyzerContext()); }
<TABLE>[[:space:]]                              { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<TABLE>.                                        { return StringLexemeAction(createLexicalAnalyzerContext()); }

<CELLSEPARATOR>"🤸‍♂️"                             { BEGIN(TABLE); return CellSeparatorLexemeAction(createLexicalAnalyzerContext()); }
<CELLSEPARATOR>.|[\n]+                          { return StringLexemeAction(createLexicalAnalyzerContext()); }
<CELLSEPARATOR>[ ]+                             { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<BOLD>"👨‍🦲"                                      { BEGIN(INITIAL); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>"🤌"                                      { BEGIN(BOLDITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>"📉"                                      { BEGIN(BOLDUNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>[\n]+                                     { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>{TEXT}                                    { return StringLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>.                                         { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<BOLDITALIC>"🤌"                                { BEGIN(BOLD); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALIC>"📉"                                { BEGIN(BOLDITALICUNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALIC>[\n]+                               { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALIC>{TEXT}                              { return StringLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALIC>.                                   { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<BOLDITALICUNDERLINE>"📉"                       { BEGIN(BOLDITALIC); return UnderlineLexemeAction(createLexicalAnalyzerContext());  }
<BOLDITALICUNDERLINE>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALICUNDERLINE>{TEXT}                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
<BOLDITALICUNDERLINE>.                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<BOLDUNDERLINE>"📉"                             { BEGIN(BOLD); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINE>"🤌"                             { BEGIN(BOLDUNDERLINEITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINE>[\n]+                            { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINE>{TEXT}                           { return StringLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINE>.                                { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<BOLDUNDERLINEITALIC>"🤌"                       { BEGIN(BOLDUNDERLINE); return ItalicLexemeAction(createLexicalAnalyzerContext());  }
<BOLDUNDERLINEITALIC>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINEITALIC>{TEXT}                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
<BOLDUNDERLINEITALIC>.                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<ITALIC>"🤌"                                    { BEGIN(INITIAL); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>"👨‍🦲"                                    { BEGIN(ITALICBOLD); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>"📉"                                    { BEGIN(ITALICUNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>[\n]+                                   { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>{TEXT}                                  { return StringLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>.                                       { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<ITALICBOLD>"👨‍🦲"                                { BEGIN(ITALIC); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLD>"📉"                                { BEGIN(ITALICBOLDUNDERLINE); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLD>[\n]+                               { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLD>{TEXT}                              { return StringLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLD>.                                   { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<ITALICBOLDUNDERLINE>"📉"                       { BEGIN(ITALICBOLD); return UnderlineLexemeAction(createLexicalAnalyzerContext());  }
<ITALICBOLDUNDERLINE>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLDUNDERLINE>{TEXT}                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
<ITALICBOLDUNDERLINE>.                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<ITALICUNDERLINE>"📉"                           { BEGIN(ITALIC); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINE>"👨‍🦲"                           { BEGIN(ITALICUNDERLINEBOLD); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINE>[\n]+                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINE>{TEXT}                         { return StringLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINE>.                              { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<ITALICUNDERLINEBOLD>"👨‍🦲"                       { BEGIN(ITALICUNDERLINE); return BoldLexemeAction(createLexicalAnalyzerContext());  }
<ITALICUNDERLINEBOLD>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINEBOLD>{TEXT}                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
<ITALICUNDERLINEBOLD>.                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINE>"📉"                                 { BEGIN(INITIAL); return UnderlineLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>"👨‍🦲"                                 { BEGIN(UNDERLINEBOLD); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>"🤌"                                 { BEGIN(UNDERLINEITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>[\n]+                                { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>{TEXT}                               { return StringLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINE>.                                    { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINEBOLD>"👨‍🦲"                             { BEGIN(UNDERLINE); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLD>"🤌"                             { BEGIN(UNDERLINEBOLDITALIC); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLD>[\n]+                            { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLD>{TEXT}                           { return StringLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLD>.                                { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINEBOLDITALIC>"🤌"                       { BEGIN(UNDERLINEBOLD); return ItalicLexemeAction(createLexicalAnalyzerContext());  }
<UNDERLINEBOLDITALIC>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLDITALIC>{TEXT}                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEBOLDITALIC>.                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINEITALIC>"🤌"                           { BEGIN(UNDERLINE); return ItalicLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALIC>"👨‍🦲"                           { BEGIN(UNDERLINEITALICBOLD); return BoldLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALIC>[\n]+                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALIC>{TEXT}                         { return StringLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALIC>.                              { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

<UNDERLINEITALICBOLD>"👨‍🦲"                       { BEGIN(UNDERLINEITALIC); return BoldLexemeAction(createLexicalAnalyzerContext());  }
<UNDERLINEITALICBOLD>[\n]+                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALICBOLD>{TEXT}                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
<UNDERLINEITALICBOLD>.                          { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

{TEXT}									        { return StringLexemeAction(createLexicalAnalyzerContext()); }
[[:space:]]                                     { return StringLexemeAction(createLexicalAnalyzerContext()); }
.                                               { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"