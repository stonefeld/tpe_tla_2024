#! /bin/bash

export LOG_IGNORED_LEXEMES=false
export LOGGING_LEVEL=ALL

set -euo pipefail

BASE_PATH="$(dirname "$0")/../.."
cd "$BASE_PATH"

INPUT="$1"
shift 1
cat "$INPUT" | build/Compiler "$@"
