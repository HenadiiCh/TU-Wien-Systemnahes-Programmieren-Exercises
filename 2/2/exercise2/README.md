> **SUBMITTED BY:**
> - **Name:** Henadii Chalyi
> - **Student ID (Matrikelnummer):** [12344365]
> - **E-Mail:** e12344365@student.tuwien.ac.at
> - **Status:** All tasks (1, 2, 3) successfully completed and tested.

--

# Hausübung 2 (2 Punkte)

**Ausgabe**: Dienstag 17. März 2026, vormittags.

**Abgabe bis**: Montag 13. April 2026, Ende des Tages.

**Abgabe via**: git-Repository mit dem Namen **`exercise2`** auf unserem git-Server https://sgit.iue.tuwien.ac.at

# Aufgabenstellung

In dieser Hausübung werden folgende Themen erstmalig einfließen:

- Bedingungen/Verzweigungen und Schleifen
- Übergabe/Rückgabe/Manipulation von Sequenzen in Form eines `std::vector<int>` und `std::vector<double>`
- Übergabe und Rückgabewerte mehrerer Werte mittels `std::tuple<double,double,double>` und `std::tuple<double,double>`

---

### Task 1: Minimum in einem Vector (keine Punkte)

In dieser Aufgabe wird eine Funktion `min` implementiert, die das kleinste Element in einem `std::vector<int>` findet.

* **Kernkonzepte**: `std::vector`, Schleifen und Basis-Algorithmen.
* **Zu bearbeitende Abgabedatei**: `src/task1.main.cpp`.
* **Kompilieren & Ausführen**:
    ```bash
    mkdir -p build && g++ -std=c++20 src/task1.main.cpp -o build/task1 && ./build/task1
    ```


### Task 2: Analyse von Sequenzen (1 Punkt)

Hierbei handelt es sich um eine Sammlung von Funktionen zur Analyse und Manipulation von `double`-Sequenzen (`std::vector<double>`).

* **Funktionen**:
    * `count_gt` / `count_lt`: Zählen von Werten größer oder kleiner als ein Referenzwert.
    * `select_gt` / `select_lt` / `select_gt_and_lt`: Filtern von Werten in einen neuen Vector basierend auf Bedingungen.
    * `mean` / `median`: Statistische Berechnungen (arithmetisches Mittel und Median).
    * `minmax`: Finden von Minimum und Maximum gleichzeitig, Rückgabe als `std::tuple`.


* **Zu bearbeitende Abgabedatei**: `src/task2.cpp`.
* **Kompilieren & Ausführen**:
    ```bash
    mkdir -p build && g++ -std=c++20 src/task2*.cpp -o build/task2 && ./build/task2
    ```

### Task 3: Lösen quadratischer Gleichungen (1 Punkt)

Diese Aufgabe befasst sich mit der Berechnung der realen Nullstellen einer quadratischen Gleichung der Form $ax^2 + bx + c = 0$.

* **Besonderheiten**:
    * Nutzung von Funktionsüberladung (Overloading) für den Typ der Koeffizienten (einmal Einzelwerte, einmal als `std::tuple`).
    * Behandlung von komplexen Lösungen: Falls keine reellen Nullstellen existieren, enthält das Rückgabe-Tuple `NaN` (Not-a-Number).
    * Die Ergebnisse werden aufsteigend sortiert im Tuple zurückgegeben.


* **Zu bearbeitende Abgabedatei**: `src/task3.cpp`.
* **Kompilieren & Ausführen**:
    ```bash
    mkdir -p build && g++ -std=c++20 src/task3*.cpp -o build/task3 && ./build/task3
    ```

