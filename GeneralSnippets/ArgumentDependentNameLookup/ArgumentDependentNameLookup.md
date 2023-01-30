# Argument-Dependent Name Lookup (ADL) / *Koenig*-Lookup

[Zur�ck](../../Readme.md)

---

[Quellcode](ArgumentDependentNameLookup.cpp)

---

## �berblick

*Argument-Dependent Name* Lookup (ADL), auch als *Koenig*-Lookup bezeichnet,
hat zur Folge, dass eine Funktion (oder ein Operator), die ohne Angabe ihres Namensraums aufgerufen wird,
auch in Namensr�umen gesucht wird,
in denen der Typ des Arguments bzw. der Argumente definiert ist.
Deshalb wird diese Suche auch als *Argument-Dependent Name Lookup* bezeichnet, kurz ADL.

Ein Beispiel hierzu:

```cpp
namespace MyNamespace
{
    class MyClass {};
    void doSomething(MyClass) {}
    void doSomething() {}
}

namespace ArgumentDependentNameLookup
{
    void test_01()
    {
        MyNamespace::MyClass obj;

        // doSomething();              // Error: 'doSomething': identifier not found

        MyNamespace::doSomething();    // works - namespace specified

        doSomething(obj);              // works too - Argument-Dependent Name Lookup
    }
}
```

Im obigen Beispiel gibt es weder eine `using`-Deklaration noch eine `using`-Direktive,
aber dennoch identifiziert der Compiler den nicht qualifizierten Namen `doSomething(obj)`
(letzte Anweisung von `test_01`) korrekt als die im Namensraum `MyNamespace` deklarierte Funktion,
indem er *Argument-Dependent Name Lookup* anwendet.

Der zweite, parameterlose Aufruf von `doSomething()` schl�gt zur �bersetzungszeit fehl,
da der Compiler den Bezeichner `doSomething` nicht findet.
Offensichtlich findet kein Koenig-Lookup statt &ndash; wie auch, diese �berladung von `doSomething` hat keine Parameter.

*Koenig-Lookup* bzw. *Argument-Dependent Name Lookup* weist den Compiler an,
nicht nur den lokalen G�ltigkeitsbereich (Namensraum) bei der Suche nach Bezeichnern zu betrachten,
sondern auch die Namensr�ume, die den Typ des Arguments / der Argumente enthalten.

Somit findet der Compiler im obigen Code, dass das Objekt `obj`, das das Argument einer �berladung der Funktion `doSomething()` ist,
zum Namespace `MyNamespace` geh�rt. Es sucht also in diesem Namensraum nach der Deklaration von `doSomething`.

### Wozu wurde der Koenig-Lookup eingef�hrt?

Ein einfaches Beispiel f�r ADL in C++ stellt die Benutzung der Stream-Klassen (`ostream`, ...) dar:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello World" << std::endl;
}
```

In diesem Beispiel wird der Stream-Operator `operator<<` verwendet, er ist im Namensraum `std` definiert.

Im Gegensatz zu `std::cout` und `std::endl` wird er aber ohne (!) eine Qualifizierung mit `std::` aufgerufen,
das Beispiel ist dennoch �bersetzungsf�hig! Ohne ADL w�re das Beispiel **nicht** �bersetzungsf�hig!

Man m�sste ohne ADL das Beispiel entweder in den `std`-Namensraum verlegen (ergibt keinen Sinn)
oder den Operator `<<` explizit importieren:

```cpp
using std::operator<<;
```

Dies ist ebenfalls nicht anstrebenswert genauso wenig wie ein Verzicht auf die Infix-Schreibweise:

```cpp
std::operator<<(std::cout, "Hello World").operator<<(std::endl);
```

---

[Zur�ck](../../Readme.md)

---
