# Perfect Forwarding

[Zur�ck](../../Readme.md)

---

## Ein klassischer �bersetzungsfehler

&#x21D0; [Teil I: Grundlagen zu Perfect Forwarding](PerfectForwarding_01.md)

---

[Quellcode](PerfectForwarding05.cpp): Democode

---

## Motivation

Um das Vorhandensein eines Werts in einem STL-Container zu �berpr�fen,
wenden wir typischerweise den STL-Algorithmus `std::find` an.
`std::find` gibt einen Iterator zur�ck, der auf diesen Wert verweist,
wenn er sich im Container befindet, und `std::end`, wenn dies nicht der Fall ist:

```cpp
std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

using Iterator = std::vector<int>::iterator;
using ValueType = std::vector<int>::value_type;

ValueType value = 5;
Iterator it = std::find(std::begin(vec), std::end(vec), value);

if (it != std::end(vec)) {
    std::cout << "Found value " << value << std::endl;
}
else {
    std::cout << "Value " << value << " not found!" << std::endl;
}
```

Oft ben�tigt der Code dann den von `std::find` zur�ckgegebenen Iterator,
sodass der R�ckgabewert von `std::find` sowohl zum �berpr�fen,
ob sich der Wert in der Auflistung befindet, als auch zum Zugriff auf diesen Wert
verwendet wird, falls dies der Fall ist.

Aber manchmal wollen wir nur wissen, ob sich der Wert in der Sammlung befindet.
Und in diesem Fall ist der obige Code ziemlich l�nglich.
Es w�re sch�ner, eine `contains`-Funktion zu haben, die diese Frage mit
einem `bool`-Wert beantwortet:

```cpp
if (contains(container, 42))
{
    // container contains 42
}
```

Von dieser Funktion `contains` k�nnten verschiedene Arten von STL-Containerklassen profitieren,
darunter `std::vector`, `std::array` und benutzerdefinierte Container.
Also werden wir diese Funktion als Funktionsschablone schreiben mit einem generischen 
Containertyp.

Damit m�ssen wir auch den Wert, nach dem wir suchen, generisch betrachten.
STL-Container haben daf�r einen Alias `value_type`,
und benutzerdefinierte Container sollten auch diesen Alias haben,
da benutzerdefinierte Container den Konventionen der STL folgen sollten.

Damit k�nnte eine erste Version einer Funktion `contains_0` so aussehen:

```cpp
template<typename TCONTAINER>
using ValueTypeEx = typename TCONTAINER::value_type;

template<typename TCONTAINER>
using IteratorEx = typename TCONTAINER::iterator;

template<typename TCONTAINER>
bool contains_0(TCONTAINER&& cont, ValueTypeEx<TCONTAINER> const& value)
{
    IteratorEx<TCONTAINER> it = std::find(std::begin(cont), std::end(cont), value);
    return (it != std::end(cont)) ? true : false;
}
```

Die Funktion erfasst den Container �ber eine *Perfect Forwarding Reference*,
da auf diese Weise Algorithmen f�r Bereiche (*Ranges*) zu entwerfen sind.

Wir schaffen es trotzdem nicht, diese beiden Anweisungen fehlerfrei
�bersetzen zu k�nnen:

```cpp
std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
bool found = contains_0(vec, 6);
```

Die Fehlermeldung lautet:

```
Failed to specialize function template 'bool containsEx(TCONTAINER &&,const TCONTAINER::value_type &)' 
Message 'TCONTAINER=std::vector<int,std::allocator<int>> &'  
```

Das Kleingedruckte muss man genau lesen.
Der Container ist nicht `std::vector<int>`. Er ist `std::vector<int>&`.
Beachten Sie das `&`. Das sagen die letzten Zeilen des �bersetzungsfehlers.
Dies ist ein v�llig anderer Typ. `std::vector<int>` hat einen Werttyp
(zur Erinnerung: `std::vector<int>::value_type`),
aber `std::vector<int>&` hat wie `int&` oder ein anderer Referenztyp keinen derartigen Alias.
Daher der �bersetzungsfehler!

Wenn wir das Problem erkannt haben, ist es nicht mehr schwer,
dieses zu beheben.

Wir m�ssen nur die Referenz entfernen.
Dazu k�nnen wir in C++ 11 `std::remove_reference` oder in C++ 14 das bequemere
`std::remove_reference_t` verwenden.
Da ich bisweilen Quellcode bevorzuge, der ausf�hrlicher (und damit hoffentlich auch verst�ndlicher) gehalten ist,
folgt nun eine C++ 11 Variante mit der Behebung des Fehlers:

```cpp
template<typename TCONTAINER>
using ValueType = typename std::remove_reference<TCONTAINER>::type::value_type;

template<typename TCONTAINER>
using Iterator = typename std::remove_reference<TCONTAINER>::type::iterator;

template<typename TCONTAINER>
bool contains(TCONTAINER&& cont, ValueType<TCONTAINER> const& value)
{
    Iterator<TCONTAINER> it = std::find(std::begin(cont), std::end(cont), value);
    return (it != std::end(cont)) ? true : false;
}

void test() {

    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    bool found = contains(vec, 6);
    std::cout << std::boolalpha << found << std::endl;
}
```

In beiden `using`-Anweisungen `ValueType` und `Iterator` gelangt
`std::remove_reference` zur Anwendung,
die `contains`-Funktion arbeitet nun einwandfrei!

## Literaturhinweis:

Das Beispiel stammt aus dem C++ Blog von *Jonathan Boccara* und ist unter

[A Classic Compilation Error with Dependent Types](https://www.fluentcpp.com/2020/12/11/a-classic-compilation-error-with-dependent-types/)<br>(abgerufen am 13.12.2020).

zu finden.

---

[Zur�ck](../../Readme.md)

---
