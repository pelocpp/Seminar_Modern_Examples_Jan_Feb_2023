# Template Template Parameter

[Zur�ck](../../Readme.md)

---

[Quellcode](TemplateTemplateParameter_01.cpp)

---

Als Parameter f�r Templates k�nnen neben realen Typen auch wiederum Klassentemplates fungieren.

Die Syntax derartiger Templates sieht dann so aus:

```cpp
template < template <typename> class T> >
class X
{
};
```

In den Beispielen betrachten wir ein Funktions-Template und ein Klassentemplate,
die beide in den Template-Parametern ein Klassentemplate als Stellvertreter f�r einen STL-Container �bergeben bekommen.

Ein weiteres Beispiel zum Thema *Template Template Parameter* findet sich hier:

https://stackoverflow.com/questions/32351697/optional-range-check-based-on-template-parameter

---

[Zur�ck](../../Readme.md)

---

