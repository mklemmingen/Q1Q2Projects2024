# Aufgaben-repo-inf3-SoSe14


Coding-Guidelines

Pro Verstoß wird in der Regel 1 Punkt abgezogen. Mehrfachverstöße sind
möglich. Bei einigen Kriterien können mehrere Punkte abgezogen werden. 
Dies ist nachstehende dokumentiert.

1. Gecodet, dokumentiert und kommentiert wird auf Englisch. Die abzugebende
Dokumentation in RELAX soll auf deutsch geschrieben sein.

2. Code ist weitestgehend selbstdokumentierend und bei Bedarf mit zus¨atzlichen
Kommentaren versehen. Das bedeutet auch, dass Variablen, Methoden
und Klassen sinnvoll benannt sind. Gut lesbarer Code ist dabei wichtiger
als mit Kommentaren gespickter Code. Im Zweifel lieber den Code um-
strukturieren oder Variablen und Methoden umbenennen, um den Code
besser lesbar zu machen. Davon unberührt bleibt Guideline Nr. 3.

3. Die Dokumentation aller Methoden ist auszufüllen (kurze Beschreibung
der Funktion, eventuelle Parameter und Rückgabewerte). Die zu doku-
mentierenden Elemente sind: Methoden jeglicher Art, Konstruktoren sowie
Getter und Setter.

4. Code ist immer strukturiert. Das heißt: Blöcke haben genau einen Ein-
und einen Ausgang. Mehrfache return-Anweisungen sind zu vermeiden. In
Schleifenkörpern gibt es generell weder return- noch break-Anweisungen.

5. Code ist effizient zu schreiben. So sind etwa foreach-Schleifen nur genau
dann zu benutzen, wenn alle Elemente eines Feldes betrachtet werden.

6. Boolsche Variablen werden nicht explizit mit true oder false verglichen.

7. Funktionalität ist zu kapseln, wann immer möglich (Don’t Repeat Your-
self).

8. Bezeichnungen sind einheitlich zu halten: entweder camel-case, oder un-
derscore innerhalb eines Projekts.

9. Auch Blöcke, die nur eine Anweisung beinhalten, sind zu klammern.

10. Z¨ahlvariablen von Schleifen sind nicht zu missbrauchen (= nicht im Schlei-
fenk¨orper zu ver¨andern). Im Zweifelsfall lieber einen Iterator verwenden.

11. Literale Konstanten im Code sind zu vermeiden. Stattdessen sind an
sinnvollen Stellen entsprechende Konstanten anzulegen.

12. Verweise auf referenzierte Dateien (Bibliotheken, Dummy-Daten, Konfig-
urationsdateien, etc.) werden relativ zum Projekt referenziert, niemals
mit absoluten Pfadangaben.

13. Git-Commits haben einen sinnvollen Kommentar zu erhalten, der zumin-
dest kurz beschreibt, was durch den Commit ver¨andert wurde.

14. Die zus¨atzliche Dokumentation in RELAX gibt eine übersicht über den
Code durch Verwendung von Metriken, UML Diagrammen und einer kurzen
Beschreibung der Klassen oder Module. (max. -3 Punkte)

15. Der abgegebene Code ist für die angek¨undigten Entwicklungsumgebun-
gen lauffähig, besitzt eine Main-Methode oder einen Testtreiber (max. - 2
Punkte)

16. Wann immer möglich, verwenden Sie Spezifikation durch Vertrag (erst
nach Einf¨uhrung des Konzepts in der Veranstaltung) (max. -2 Punkte)

17. Sorgen Sie für ein tracing des Programmablaufs. Dazu können Sie geeignete
print-Anweisungen verwenden, oder noch besser ein Logging-Framework
wie Log4J oder das logging-Package.