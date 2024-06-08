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

Title* TitleSemanticAction(Constant* constant, Tags* tags);
Title* EmptyTitleSemanticAction(Tags* tags);

Tags* TagsSemanticAction(Tag* tag, Tags* tags);
Tags* EndTagSemanticAction(Tag* tag);

Tag* Heading1SemanticAction(Constant* constant);
Tag* Heading2SemanticAction(Constant* constant);
Tag* Heading3SemanticAction(Constant* constant);
Tag* PageSkipSemanticAction(Constant* constant);
Tag* ImageSemanticAction(Constant* constant);
Tag* CodeSemanticAction(Constant* constant);
Tag* EscapeSemanticAction(Constant* constant);
Tag* EquationSemanticAction(Constant* constant);

Tag* UnorderedListSemanticAction(List* list);
Tag* OrderedListSemanticAction(List* list);
Tag* TableSemanticAction(Table* table);

Tag* BoldSemanticAction(Bold* bold);
Tag* BoldConstantSemanticAction(Constant* constant);

Tag* ItalicSemanticAction(Italic* italic);
Tag* ItalicConstantSemanticAction(Constant* constant);

Tag* UnderlineSemanticAction(Underline* underline);
Tag* UnderlineConstantSemanticAction(Constant* constant);

Tag* StringTagSemanticAction(char* value);

List* ItemSemanticAction(Constant* constant, List* list);
List* LonelyItemSemanticAction(Constant* constant);

Table* CellSeparatorSemanticAction(Constant* constant, Table* table);
Table* LonelyCellSeparatorSemanticAction(Constant* constant);

Bold* BoldItalicConstantSemanticAction(Constant* constant);
Bold* BoldItalicSemanticAction(BoldItalic* boldItalic);
Bold* BoldUnderlineConstantSemanticAction(Constant* constant);
Bold* BoldUnderlineSemanticAction(BoldUnderline* boldUnderline);

BoldItalic* BoldItalicUnderlineSemanticAction(Constant* constant);
BoldUnderline* BoldUnderlineItalicSemanticAction(Constant* constant);

Italic* ItalicBoldConstantSemanticAction(Constant* constant);
Italic* ItalicBoldSemanticAction(ItalicBold* italicBold);
Italic* ItalicUnderlineConstantSemanticAction(Constant* constant);
Italic* ItalicUnderlineSemanticAction(ItalicUnderline* italicBold);

ItalicBold* ItalicBoldUnderlineSemanticAction(Constant* constant);
ItalicUnderline* ItalicUnderlineBoldSemanticAction(Constant* constant);

Underline* UnderlineBoldConstantSemanticAction(Constant* constant);
Underline* UnderlineBoldSemanticAction(UnderlineBold* underlineBold);
Underline* UnderlineItalicConstantSemanticAction(Constant* constant);
Underline* UnderlineItalicSemanticAction(UnderlineItalic* underlineItalic);

UnderlineBold* UnderlineBoldItalicSemanticAction(Constant* constant);
UnderlineItalic* UnderlineItalicBoldSemanticAction(Constant* constant);

Constant* StringConstantSemanticAction(char* value);
Constant* EmptyConstantSemanticAction();

#endif