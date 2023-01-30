# Neue Schl�sselw�rter `override` und `final`

[Zur�ck](../../Readme.md)

---

[Quellcode](VirtualOverrideFinal.cpp)

---

## Schl�sselwort `override`

### Ein Beispiel

```cpp
class Base
{
public:
    virtual void func(int);
};

class Derived : public Base
{
public:
    void func(int) override;
};

void Base::func(int n)
{
public:
    std::cout << "Base::func [" << n << "]" << std::endl;
}

void Derived::func(int n)
{
    std::cout << "Derived::func " << n << "]" << std::endl;
}
```

### Vorteile bez�glich der Verwendung von `override`

H�tten wir einen der folgenden Fehler gemacht, w�rde uns der �bersetzer bei
Verwendung von `override` nun neuerdings darauf aufmerksam machen:

  * In Klasse `Derived`: `void fumc(int) override;` - Tippfehler im Namen der Funktion
  * In Klasse `Derived`: `void func(long) override;` - Fehler bei einem Formalparametertyp
  * In Klasse `Base`: `void func(int);` - Schl�sselwort `virtual` in Klasse `Base` vergessen

---

## Schl�sselwort `final`

Mit dem neuen Schl�sselwort `final` lassen sich Methoden und Klassen markieren,
die nicht mehr �berschrieben werden d�rfen.

### Ein Beispiel

```cpp
class Driver
{
public:
    virtual void send(int) {};
};

class KeyboardDriver : public Driver
{
public:
    void send(int) final {};  // cannot be overriden anymore
};

class MouseDriver final : public Driver // cannot be used as base class anymore
{
public:
    void send(int) {};  // cannot be overriden anymore
};
```

### Beispiele bez�glich der Verwendung von `final`

Unter Verwendung von `final` wird zum Beispiel verhindert, dass die folgenden Anweisungen
zul�ssig sind:

```cpp
class TrackballDriver : public MouseDriver
{};
```

```cpp
class SpecialKeyboardDriver : public KeyboardDriver
{
public:
    void send(int) final;
};
```

---

[Zur�ck](../../Readme.md)

---
