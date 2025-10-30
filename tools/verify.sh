#!/bin/sh
# Usage: tools/verify.sh /path/to/9front/sys/src/cmd/rio patches/0001-rio-ndb-theme.diff
set -eu
RIO="${1:?need rio path}"
PATCH="${2:?need patch file}"
cd "$RIO"
git apply --check "$PATCH" && echo "OK: Patch lässt sich sauber anwenden."
