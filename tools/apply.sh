#!/bin/sh
# Usage: tools/apply.sh /path/to/9front/sys/src/cmd/rio patches/0001-rio-ndb-theme.diff
set -eu
RIO="${1:?need rio path}"
PATCH="${2:?need patch file}"
cd "$RIO"
git apply --index --reject "$PATCH" || {
  echo "Hinweis: Konflikte .rej prüfen."
  exit 1
}
echo "Patch angewendet (Index)."
