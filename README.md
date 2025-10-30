# English

## rio-ndb-theme
A tiny C89/K&R patch that lets **rio** read its initial colors from NDB, with clean fallbacks.
It is an _optional_ color scheme for **rio**, configurable via NDB file instead of recompiling.  
**Priority:** Defaults → NDB → `-b` (black) → **look** menu.

### Keys
- `bg`, `fg`, `border`, `selbg`, `selfg`, `mouse` – Hex `#RRGGBB`
- Optional: `theme=<name>` to select an entry; enforceable via `RIOTHEME`

### Paths
- System-wide: `/lib/ndb/rio`
- User-wide: `/usr/$user/lib/ndb/rio`

### Example
service=rio 
theme=custom
bg=#101418
fg=#e6e6e6
border=#6c6c6c
selbg=#2e4a6f
selfg=#ffffff
mouse=#ffcc00

# German

## rio-ndb-theme
Ein kleiner C89/K&R-Patch, der es **rio** ermöglicht, seine Initialfarben aus NDB zu lesen, mit sauberen Fallbacks.
Es ist ein _optionales_ Farbschema für **rio**, konfigurierbar via NDB-Datei statt Recompile.  
**Priorität:** Defaults → NDB → `-b` (schwarz) → Menü **look**.

### Schlüssel
- `bg`, `fg`, `border`, `selbg`, `selfg`, `mouse` – Hex `#RRGGBB`
- Optional: `theme=<name>` zur Auswahl eines Eintrags; via `RIOTHEME` erzwingbar

### Pfade
- Systemweit: `/lib/ndb/rio`
- Nutzerweit: `/usr/$user/lib/ndb/rio`

### Beispiel
service=rio 
theme=custom
bg=#101418
fg=#e6e6e6
border=#6c6c6c
selbg=#2e4a6f
selfg=#ffffff
mouse=#ffcc00
