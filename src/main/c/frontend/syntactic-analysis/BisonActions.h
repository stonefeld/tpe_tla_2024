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

Expression* DoubleExpressionSemanticAction(Expression* leftExpression, Expression* rightExpression);
Expression* LonelyExpressionSemanticAction(StartToken startToken, EndToken endToken, Constant* constant);
Expression* FactorExpressionSemanticAction(Factor* factor);

Factor* ListFactorSemanticAction(StartToken startToken, EndToken endToken, List* list);
Factor* LonelyFactorSemanticAction(StartToken startToken, EndToken endToken, Constant* constant);
Factor* BoldFactorSemanticAction(Bold* bold);
Factor* ItalicFactorSemanticAction(Italic* italic);
Factor* UnderlineFactorSemanticAction(Underline* underline);
Factor* TableFactorSemanticAction(Table* table);

List* LonelyListSemanticAction(Constant* constant);
List* DoubleListSemanticAction(List* leftList, List* rightList);

Table* LonelyTableSemanticAction(Constant* constant);
Table* DoubleTableSemanticAction(Table* leftTable, Table* rightTable);

Bold* LonelyBoldSemanticAction(StartToken startToken, EndToken endToken, Constant* constant);
Bold* ItalicFromBoldSemanticAction(BoldItalic* boldItalic);
Bold* UnderlineFromBoldSemanticAction(BoldUnderline* boldUnderline);

BoldItalic* LonelyBoldItalicSemanticAction(Constant* constant);
BoldUnderline* LonelyBoldUnderlineSemanticAction(Constant* constant);

Italic* LonelyItalicSemanticAction(StartToken startToken, EndToken endToken, Constant* constant);
Italic* BoldFromItalicSemanticAction(ItalicBold* italicBold);
Italic* UnderlineFromItalicSemanticAction(ItalicUnderline* italicUnderline);

ItalicBold* LonelyItalicBoldSemanticAction(Constant* constant);
ItalicUnderline* LonelyItalicUnderlineSemanticAction(Constant* constant);

Underline* LonelyUnderlineSemanticAction(StartToken startToken, EndToken endToken, Constant* constant);
Underline* BoldFromUnderlineSemanticAction(UnderlineBold* underlineBold);
Underline* ItalicFromUnderlineSemanticAction(UnderlineItalic* underlineItalic);

UnderlineBold* LonelyUnderlineBoldSemanticAction(Constant* constant);
UnderlineItalic* LonelyUnderlineItalicSemanticAction(Constant* constant);

Constant* StringConstantSemanticAction(const char* value);

#endif