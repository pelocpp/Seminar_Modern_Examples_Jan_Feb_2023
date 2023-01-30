# Die C++ Standard Template Library (STL): Erg�nzungen

[Zur�ck](../../Readme.md)

---

[Quellcode](StandardLibrarySTL.cpp)

---

In diesem Code-Snippet werden eine Reihe von bekannten - und auch weniger bekannten -
Erg�nzungen, Neuerungen, Erweiterungen etc. zur C++ Standard Template Library (STL) vorgestellt:

  * 4 neue Container
  * Einfach verkettetete Liste (`std::forward_list`)
  * Integrale Typen mit fester L�nge
  * `std::prev` und `std::next` Funktionen
  * `const`-Iteratoren `std::cbegin` und `std::cend`
  * Konvertierung von Zeichenketten in Zahlen
  * Funktion `std::make_move_iterator`
  * Standardcontainer passend verkleinern: Methode `shrink_to_fit`

---

## 4 neue Container

Es gibt vier neue Container-Klassen:

  * `std::unordered_set`
  * `std::unordered_multiset`
  * `std::unordered_map`
  * `std::unordered_multimap`

Ihre bisherigen, immer noch existierenden Pendants lauten:

  * `std::set`
  * `std::multiset`
  * `std::map`
  * `std::multimap`


*Beispiel*:

```cpp
using IntegerSet = std::unordered_set<int>;
using IntToStringMap = std::unordered_map<int, std::string>;
```

###### Wesentlicher Unterschied dieser Container bei verschiedenen Programmiersprachen

In C++ sind diese Container (ohne `unordered_` Pr�fix)
immer (nach ihrem Schl�ssel) sortiert gehalten. 
Iteriert man �ber die Elemente eines solchen Containers,
dann werden die Elemente automatisch in aufsteigender Reihenfolge
zur�ckgeliefert.

Der tyische Ansatz in der Realisierung dieser Container k�nnte ein
*balancierter Baum* zur Ablage der Elemente sein. Damit h�ngt der Aufwand
in der Suche nach einem Element logarithmisch von der L�nge (Gr��e) der Datenstruktur
ab.

Die neuen Container stellen diesselbe Funktionalit�t zur Verf�gung,
allerdings auf Basis einer Hash-Tabelle bzgl. der internen Realisierung.
Damit bleibt die Zugriffszeit weitestgehend konstant - unabh�ngig von der Gr��e
des Containers.

## Einfach verkettetete Liste (`std::forward_list`)

In Erg�nzung zu

  * `std::list`
  * `std::deque`

gibt es nun auch eine ganz einfache verkettetete Liste zum Speichern
einer variablen Anzahl von Elementen:

  * `std::forward_list`

Nur als ganz kurze Wiederholung:

  * `std::list`
    - Ist im Prinzip eine doppelt verkettete Liste
    - Random Access *nicht* vorhanden
    - Das Einf�gen und L�schen von Elementen erfolgt an jeder Position performant,
      einschlie�lich an den beiden Enden. 

  * `std::deque`
     - Implementierung hat �hnlichkeit zur Klasse `std::vector` (dynamic array)
     - Random Access vorhanden
     - Bietet schnelles Einf�gungen und L�schen sowohl am Ende als auch am Anfang.
     - Das Einf�gen und L�schen von Elementen in der Mitte ist relativ langsam,
       da alle Elemente bis zu einem der beiden Enden verschoben werden m�ssen, um Platz zu schaffen oder eine L�cke zu f�llen.

Die �ffentliche Schnittstelle `std::forward_list` weicht teilweise erheblich
von den anderen Container-APIs ab. Auch gibt es so eine einfache Methode wie `size` nicht,
daf�r aber `empty`.

## Integrale Typen mit fester L�nge

Herk�mmliche Datentypen wie `int` oder auch `long` sind in ihrer exakten Gr��e 
im Standard nicht festgelegt, sodern mit der Formulierung &ldquo;maschinenabh�ngig&rdquo; umschrieben.

Eine Reihe neuer Datentypen

```cpp
int8_t;
int16_t;
int32_t;
int64_t;
uint8_t;
uint16_t;
uint32_t;
uint64_t;
```

erlauben eine Definition mit exakter Gr��e und damit genau definiertem 
Wertebereich auf allen Plattformen.

*Hinweis*:
Plattformabh�ngig k�nnen diese neuen Datentypen nat�rlich auf die herk�mmlichen
Datentypen abgebildet werden. Nur findet diese Abbildung eben auf jedem System
mit den oben aufgef�hrten Randbedingen statt (exakte Gr��e).
Auf meinem Rechner sehen diese Abbildungen so aus:

```cpp
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
```

## `std::prev` und `std::next` Funktionen

Mit `std::prev` und `std::next` kann man die n�chste oder vorhergehende Position
eines Iterators berechnen.


## `const`-Iteratoren `std::cbegin` und `std::cend`

Die Funktionen liefern konstante Iteratoren zur�ck.
Ist `Container` ein C++-Standardcontainer,
dann wird immer eine Variable des Typs `Container::const_iterator` zur�ckgegeben.

*Beispiel*:

```cpp
std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
for (auto it = std::cbegin(vec); it != std::cend(vec); ++it) {
    std::cout << *it << ' ';
    // *it *= 2;   // 'it': you cannot assign to a variable that is const
}
std::cout << std::endl;

for (auto& elem : vec) {
    elem *= 2; 
}

for (auto it = std::cbegin(vec); it != std::cend(vec); ++it) {
    std::cout << *it << ' ';
}
std::cout << std::endl;

for (const auto& elem : vec) {
    std::cout << elem << ' ';
}
```

*Ausgabe*:

```cpp
1 2 3 4 5 6 7 8 9 10
2 4 6 8 10 12 14 16 18 20
2 4 6 8 10 12 14 16 18 20
```

*Hinweis*:
Man beachte, dass die beiden Funktionen *konstante* Iteratoren
f�r einen *nicht-konstanten* Container zur�ckliefern.

## Konvertierung von Zeichenketten in Zahlen

An Stelle der klassischen C-Funktionen zum Konvertieren von Zeichenketten
in Zahlen und zur�ck (wie z.B. `atoi` und `itoa`) enth�lt die Bibliothek
modernisierte Fassungen:

| Funktion | Beschreibung |
|:-------------- |-----------------------------------------|
| `std::stoi`<br/>`std::stol`<br/>`std::stoll` | Converts a string to an unsigned integer  |
| `std::stoul`<br>`std::stoull` |  Converts a string to an unsigned integer |
| `std::stof`<br>`std::stod`<br>`std::stold` | Converts a string to a floating point value |
| `std::strtol`<br>`std::strtoll` | Converts a byte string to an integer value |
| `std::strtoul`<br>`std::strtoull` | Converts a byte string to an unsigned integer value |
| `std::strtoimax`<br>`std::strtoumax` | Converts a byte string to `std::intmax_t` or `std::uintmax_t` |
| `std::from_chars` | Converts a character sequence to an integer or floating-point value |
| `std::atoi`<br>`std::atol`<br>`std::atoll` | Converts a byte string to an integer value |
| `std::to_string` | Converts an integral or floating point value to `std::string` |
| `std::to_wstring` | Converts an integral or floating point value to `std::wstring` |

Tabelle 1. Konvertierungsfunktionen.

Die herk�mmlichen Konvertierungsfunktionen weisen einige Probleme auf:

  * Das Verhalten von `atoi` ist undefiniert, wenn das Argument keine g�ltige Zahl darstellt.
  * `strtol` liefert 0 zur�ck, wenn die Zeichenkette nicht in eine Zahl konvertiert werden kann. Das l�sst sich aber nicht unterscheiden von dem Fall, wenn die Zeichenkette tats�chlich die 0 repr�sentiert.
  * `itoa` kann in ihrer herk�mmlichen Implementierung Puffer�berl�ufe verursachen.
  * `sprintf` ist umst�ndlich und pr�ft die Datentypen der Argumente nicht (Formatspezifizierer in der Formatzeichenkette).

## Funktion `std::make_move_iterator`

M�chte man die Funktionsweise eines `std::copy`-Aufrufs von einem *Kopieren* in ein *Verschieben* umwandeln,
kann man dies mit der `std::make_move_iterator`-Funktion erreichen.

*Hinweis*:
Der Zweck von `std::make_move_iterator` besteht darin, Algorithmen mit *r*-Werten ihrer Eingaben versorgen zu k�nnen.

*Beispiel*:

```cpp
void test()
{
    std::vector<std::string> source{ "C++", "Iterator", "Library", "make_move_iterator" };
    std::vector<std::string> target{ 4 };

    std::copy(
        std::make_move_iterator(source.begin()),
        std::make_move_iterator(source.end()),
        target.begin()
    );

    // target now contains unspecified values, clear them
    source.clear();

    std::cout << "Target:" << std::endl;
        
    for (const std::string& s : target)
        std::cout << s << ' ';
        
    std::cout << std::endl;
}
```

*Ausgabe*:

```cpp
Target:
C++ Iterator Library make_move_iterator
```

## Standardcontainer passend verkleinern: Methode `shrink_to_fit`

*Beispiel*:

```cpp
void test() {
    std::vector<int> vec;
    vec.reserve(100);

    for (int i = 0; i < 50; i++) {
        vec.push_back(i);
    }

    std::cout << "Size:     " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;

    vec.shrink_to_fit();

    std::cout << "Size:     " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
}
```

*Ausgabe*:

```cpp
Size: 50
Capacity: 100
Size: 50
Capacity: 50
```

---

[Zur�ck](../../Readme.md)

---
