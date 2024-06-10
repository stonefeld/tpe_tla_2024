#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include <stdlib.h>

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

Program* ProgramSemanticAction(CompilerState* compilerState, Title* title);

Title* LonelyTitleSemanticAction(Text* text);
Title* TitleSemanticAction(Text* text, Tags* tags);
Title* EmptyTitleSemanticAction(Tags* tags);

Tags* TagsSemanticAction(Tag* tag, Tags* tags);
Tags* EndTagSemanticAction(Tag* tag);

Tag* Heading1SemanticAction(Text* text);
Tag* Heading2SemanticAction(Text* text);
Tag* Heading3SemanticAction(Text* text);
Tag* PageSkipSemanticAction(Text* text);
Tag* ImageSemanticAction(Text* text);
Tag* CodeSemanticAction(char* language, Text* text);
Tag* EscapeSemanticAction(Text* text);

Tag* UnorderedListSemanticAction(List* list);
Tag* OrderedListSemanticAction(List* list);
Tag* TableSemanticAction(char* cols, Table* table);

Tag* BoldSemanticAction(Bold* bold);
Tag* BoldTextSemanticAction(Text* text);

Tag* ItalicSemanticAction(Italic* italic);
Tag* ItalicTextSemanticAction(Text* text);

Tag* UnderlineSemanticAction(Underline* underline);
Tag* UnderlineTextSemanticAction(Text* text);

Tag* StringTagSemanticAction(char* value);

List* ItemSemanticAction(Text* text, List* list);
List* LonelyItemSemanticAction(Text* text);

Table* CellSeparatorSemanticAction(Text* text, Table* table);
Table* LonelyCellSeparatorSemanticAction(Text* text);

Bold* BoldItalicTextSemanticAction(Text* text);
Bold* BoldItalicSemanticAction(BoldItalic* boldItalic);
Bold* BoldUnderlineTextSemanticAction(Text* text);
Bold* BoldUnderlineSemanticAction(BoldUnderline* boldUnderline);

BoldItalic* BoldItalicUnderlineSemanticAction(Text* text);
BoldUnderline* BoldUnderlineItalicSemanticAction(Text* text);

Italic* ItalicBoldTextSemanticAction(Text* text);
Italic* ItalicBoldSemanticAction(ItalicBold* italicBold);
Italic* ItalicUnderlineTextSemanticAction(Text* text);
Italic* ItalicUnderlineSemanticAction(ItalicUnderline* italicBold);

ItalicBold* ItalicBoldUnderlineSemanticAction(Text* text);
ItalicUnderline* ItalicUnderlineBoldSemanticAction(Text* text);

Underline* UnderlineBoldTextSemanticAction(Text* text);
Underline* UnderlineBoldSemanticAction(UnderlineBold* underlineBold);
Underline* UnderlineItalicTextSemanticAction(Text* text);
Underline* UnderlineItalicSemanticAction(UnderlineItalic* underlineItalic);

UnderlineBold* UnderlineBoldItalicSemanticAction(Text* text);
UnderlineItalic* UnderlineItalicBoldSemanticAction(Text* text);

Text* StringTextSemanticAction(char* value, Text* text);
Text* EmptyTextSemanticAction();

#endif