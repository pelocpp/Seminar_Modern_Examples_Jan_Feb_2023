# *RValues* und *LValues*

[Zur�ck](../../Readme.md)

---

[Quellcode](RValueLValue.cpp)

---

*RValues* und *LValues* zahlen in C++ zu so genannten *Wertkategorien*.
Auf Basis dieser Wertkategorien gibt es f�r den C++&ndash;�bersetzer Regeln,
die dieser beim Erstellen, Kopieren und Verschieben tempor�rer Objekte
w�hrend der Auswertung eines Ausdrucks befolgen muss.

Unter einem *RValue* verstehen wir

  * Konstante
  * tempor�re Objekte
  * Objekte ohne Namen

```cpp
// 123 ist ein RValue
int n = 123;

// std::string{ "ABC"} ist ein Objekt ohne Namen:
std::string s = std::string{ "ABC"};

// std::string{ "ABC"} + std::string{ "DEF"} ist ein tempor�res Objekt:
std::string a = std::string{ "ABC"} + std::string{ "DEF"};
```

Unter einem *LValue* verstehen wir

  * einen Ausdruck, der eine Referenz eines Objekts beschreibt.
    Zum Beispiel Objekte mit Namen oder auch Objekte,
    die in einem Array �ber einen Index erreichbar sind.

---

*Allgemeines*:

Wenn `X` ein Typ ist, wird `X&&` als *RValue* Referenz auf `X` bezeichnet.
Zur besseren Unterscheidung wird die gew�hnliche Referenz `X&` jetzt auch als *LValue* Referenz bezeichnet.
Eine *RValue* Referenz ist ein Typ, der sich - von einigen Ausnahmen abgesehen - �hnlich
wie die normale *LValue* Referenz `X&` verh�lt.

Das Wichtigste ist, dass *LValue*s bei der Aufl�sung von Funktions�berladungen die
herk�mmlichen *LValue*-Referenzen bevorzugen, w�hrend *RValue*s
die neuen *RValue*-Referenzen bevorzugen:

```cpp
void foo(X& x);   // lvalue reference overload
void foo(X&& x);  // rvalue reference overload

X x;
X foobar();

foo(x);         // argument is lvalue: calls foo(X&)
foo(foobar());  // argument is rvalue: calls foo(X&&)
```

Eine der Kernaussagen bei RValue Referenzen / LValue Referenzen lautet also:
 
Mit *Rvalue*-Referenzen kann eine Funktion zur �bersetzungszeit (mittels �berladung)
unter der Bedingung "*Werde ich f�r einen L-Wert oder einen R-Wert aufgerufen?*" verzweigen.

Siehe weiteres dazu im korrespondieren [Quellcode](RValueLValue.cpp).

---

[Zur�ck](../../Readme.md)

---


