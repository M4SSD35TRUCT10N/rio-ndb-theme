# English
## DESIGN

### Goals
- Load colors/mouse/border from NDB (system-/user-wide)
- Fallbacks exactly like upstream defaults
- Strict priority: Defaults → NDB → CLI (`-b`) → Menu (**look**)
- K&R/C89, no late declarations, only Plan 9 headers

### Non-goals
- No complex themes, no live changes to existing windows

### NDB format
- Entries with `service=rio`, optional `theme=<name>`
- Keys: `bg`, `fg`, `border`, `selbg`, `selfg`, `mouse` (Hex `#RRGGBB`)
- Backslash `\` allowed for line continuation

### Integration
- Add `theme.c/.h`
- Early init point after `initdraw()`, before image generation
- Existing `-b`/**look** retains priority


# German
## DESIGN

### Ziele
- Farben/Mouse/Border aus NDB laden (system-/nutzerweit)
- Fallbacks exakt wie Upstream-Defaults
- Strikte Priorität: Defaults → NDB → CLI (`-b`) → Menü (**look**)
- K&R/C89, keine späten Deklarationen, nur Plan 9 Headers

### Nicht-Ziele
- Keine komplexen Themes, keine Live-Änderung bestehender Fenster

### NDB-Format
- Einträge mit `service=rio`, optional `theme=<name>`
- Schlüssel: `bg`, `fg`, `border`, `selbg`, `selfg`, `mouse` (Hex `#RRGGBB`)
- Backslash `\` für Zeilenfortsetzung erlaubt

### Integration
- `theme.c/.h` hinzufügen
- Früher Init-Punkt nach `initdraw()`, vor Image-Erzeugung
- Existierende `-b`/**look** behalten Vorrang
