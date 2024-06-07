#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include <stdio.h>
#include <stdlib.h>

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */

void IgnoredLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

Token TitleLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token Heading1LexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token Heading2LexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token Heading3LexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token PageSkipLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token UnorderedListLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token OrderedListLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token ListItemLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token CellSeparatorLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token ImageLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token BoldLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token ItalicLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token UnderlineLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token TableLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token CodeLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token EscapedLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token EquationLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

Token StringLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

Token UnknownLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

#endif
