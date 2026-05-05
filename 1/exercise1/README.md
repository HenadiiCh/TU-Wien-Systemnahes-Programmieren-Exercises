> **SUBMITTED BY:**
> - **Name:** Henadii Chalyi
> - **Student ID (Matrikelnummer):** [12344365]
> - **E-Mail:** e12344365@student.tuwien.ac.at
> - **Status:** All tasks (1, 2, 3) successfully completed and tested.

---

# Hausübung 1 (2 Punkte)

**Ausgabe**: Dienstag 3. März 2026, vormittags.

**Abgabe bis**: Montag 16. März 2026, Ende des Tages.

**Abgabe via**: git-Repository mit dem Namen **`exercise1`** auf unserem git-Server https://sgit.iue.tuwien.ac.at

---

Dieses Repository enthält drei Programmieraufgaben, die Ihnen helfen, Kompilierung, Laufzeitumgebungen und grundlegende Programmierkonzepte in C, C++ und Python zu erlernen.

## Aufgabe 1: Kompilierungs- und Laufzeitinformationen (keine Punkte)

Aufgabe 1 zeigt, wie Sie Kompilierungs- und Laufzeitinformationen in verschiedenen Programmiersprachen (C, C++ und Python) abrufen und anzeigen können. Jedes Programm schreibt seine Informationen in eine Ausgabedatei im `output/`-Verzeichnis.

### Dateien
- `src/task1.test.c` - C-Programm
- `src/task1.test.cpp` - C++-Programm
- `src/task1.test.py` - Python-Skript

### Was Sie lernen werden
- Wie Sie auf kompillerspezifische Makros zugreifen (`__FILE__`, `__DATE__`, `__TIME__`, `__STDC_VERSION__`, `__cplusplus`)
- Wie Sie den verwendeten Kompilierer erkennen (GCC, Clang, MSVC)
- Wie Sie Details zur Laufzeitumgebung abrufen (Python-Version, Modulversionen)
- Wie Sie Ausgaben in Dateien schreiben

### Kompilieren & Ausführen

Erstellen Sie zunächst die notwendigen Verzeichnisse:

```bash
mkdir -p build output
```

#### C (task1.test.c)
```bash
gcc -std=c11 src/task1.test.c -o build/task1c && ./build/task1c
```
Die Ausgabe wird in `output/task1_output_c.txt` geschrieben und sollte enthalten:
- Namen der Quelldatei
- Kompilierungsdatum und -uhrzeit
- Kompilierversion
- C-Standard-Version (mindestens C11)

#### C++ (task1.test.cpp)
```bash
g++ -std=c++20 src/task1.test.cpp -o build/task1cpp && ./build/task1cpp
```
Die Ausgabe wird in `output/task1_output_cpp.txt` geschrieben und sollte enthalten:
- Namen der Quelldatei
- Kompilierungsdatum und -uhrzeit
- Kompilierversion
- C++-Standard-Version (mindestens C++20)

#### Python (task1.test.py)
```bash
python src/task1.test.py
```
Die Ausgabe wird in `output/task1_output_python.txt` geschrieben und sollte enthalten:
- Skriptdateiname
- Datum und Uhrzeit der Ausführung
- Python-Implementierung und -version
- NumPy-Version
- Matplotlib-Version

### Erwartete Ausgabe
Jedes Programm sollte ausgeben:
- C: `task1.test.c: all asserts passed`
- C++: `task1.test.cpp: all asserts passed`
- Python: `task1.test.py: all asserts passed`

---

## Aufgabe 2: Grundlegende C++-Programmierung (1 Punkt)

Aufgabe 2 ist ein einfaches C++-Programm, das demonstriert, wie man zwei Ganzzahlen mit einer selbstdefinierten Funktion summiert.

### Dateien
- `src/task2.main.cpp` - Hauptprogramm

### Was Sie lernen werden
- Wie man eine einfache Funktion definiert und implementiert
- Wie man Variablen deklariert und initialisiert
- Wie man Funktionen aufruft und Ergebnisse speichert
- Wie man Ausgaben auf der Konsole ausgibt

### Kompilieren & Ausführen

```bash
mkdir -p build
g++ -std=c++20 src/task2.main.cpp -o build/task2 && ./build/task2
```

### Programmstruktur
Das Programm:
1. Definiert eine `add(int a, int b)`-Funktion, die die Summe zweier Ganzzahlen zurückgibt
2. Erstellt zwei Ganzzahl-Variablen (33 und 6600)
3. Ruft die `add`-Funktion auf und speichert das Ergebnis
4. Gibt das Ergebnis (6633) auf der Konsole aus

### Erwartete Ausgabe
```
6633
```

---

## Aufgabe 3: C++-Matematikfunktionsbibliothek (1 Punkt)

Aufgabe 3 implementiert eine kleine Mathematikbibliothek mit mehreren Funktionen für arithmetische Operationen, einschließlich Polynomauswertung.

### Dateien
- `src/task3.hpp` - Header-Datei mit Funktionsdeklarationen
- `src/task3.cpp` - Funktionsimplementationen
- `src/task3.test.cpp` - Testprogramm

### Was Sie lernen werden
- Wie Sie Code in Header- und Implementierungsdateien organisieren
- Wie Sie mathematische Funktionen implementieren und testen
- Wie Sie mit Fließkommaarithmetik arbeiten
- Wie Sie Polynome auswerten

### Funktionsreferenz

| Funktion | Beschreibung | Parameter | Rückgabe |
|----------|-------------|------------|---------|
| `add()` | Summe von drei Werten | $x, y, z$  | $x + y + z$ |
| `mul()` | Produkt von drei Werten | $x, y, z$  | $x \cdot y \cdot z$ |
| `frac()` | Division von zwei Werten | $x, y$  | $\frac{x}{y}$ |
| `mean()` | Durchschnitt von drei Werten | $x, y, z$  | $\frac{x + y + z}{3}$ |
| `squared()` | Quadrat eines Wertes | $x$  | $x^2$ |
| `cubed()` | Kubik eines Wertes | $x$  | $x^3$ |
| `eval()` | Polynomauswertung | $x, a, b, c$  | $a \cdot x^2 + b \cdot x + c$ |

### Kompilieren & Ausführen

```bash
mkdir -p build
g++ -std=c++20 src/task3*.cpp -o build/task3 && ./build/task3
```

### Erwartete Ausgabe
```
task3.test.cpp: all asserts passed
```

---
---
