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

Program* ExpressionProgramSemanticAction(CompilerState* compilerState, Expression* expression);

Expression* TokenExpressionSemanticAction(Token startToken, Token endToken, Constant* contantant,
                                          Expression* expression);
Expression* FactorExpressionSemanticAction(Factor* factor);

Factor* ListFactorSemanticAction(Token startToken, Token endToken, List* list, Factor* factor);
Factor* TokenFactorSemanticAction(Token startToken, Token endToken, Constant* constant, Factor* factor);
Factor* BoldFactorSemanticAction(Bold* bold, Factor* factor);
Factor* ItalicFactorSemanticAction(Italic* italic, Factor* factor);
Factor* UnderlineFactorSemanticAction(Underline* underline, Factor* factor);
Factor* TableFactorSemanticAction(Table* table, Factor* factor);
Factor* ConstantFactorSemanticAction(Constant* constant);

List* ListSemanticAction(Constant* constant, List* list);
List* LonelyListSemanticAction(Constant* constant);

Table* TableSemanticAction(Constant* constant, Table* table);
Table* LonelyTableSemanticAction(Constant* constant);

Bold* LonelyBoldSemanticAction(Token startToken, Token endToken, Constant* constant);
Bold* ItalicFromBoldSemanticAction(BoldItalic* boldItalic);
Bold* UnderlineFromBoldSemanticAction(BoldUnderline* boldUnderline);

BoldItalic* LonelyBoldItalicSemanticAction(Constant* constant);
BoldUnderline* LonelyBoldUnderlineSemanticAction(Constant* constant);

Italic* LonelyItalicSemanticAction(Token startToken, Token endToken, Constant* constant);
Italic* BoldFromItalicSemanticAction(ItalicBold* italicBold);
Italic* UnderlineFromItalicSemanticAction(ItalicUnderline* italicUnderline);

ItalicBold* LonelyItalicBoldSemanticAction(Constant* constant);
ItalicUnderline* LonelyItalicUnderlineSemanticAction(Constant* constant);

Underline* LonelyUnderlineSemanticAction(Token startToken, Token endToken, Constant* constant);
Underline* BoldFromUnderlineSemanticAction(UnderlineBold* underlineBold);
Underline* ItalicFromUnderlineSemanticAction(UnderlineItalic* underlineItalic);

UnderlineBold* LonelyUnderlineBoldSemanticAction(Constant* constant);
UnderlineItalic* LonelyUnderlineItalicSemanticAction(Constant* constant);

Constant* StringConstantSemanticAction(const char* value, Constant* constant);
Constant* LonelyStringSemanticAction(const char* value);

#endif