[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver APA102C
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/apa102c/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

APA102C für die Steuerung der Dimmung von dreifarbigen RGB-LEDs. Dann IC, unter Verwendung des CMOS-Prozesses, der einen dreifarbigen RGB-LED-Ausgangstreiber bereitstellt, um die Ausgabe mit 256 Graustufen und 32 Helligkeitseinstellungen anzupassen. APA102 mit zwei Ausgangswegen, das CLK-Signal wird synchronisiert, sodass die Ausgangsbewegungen des Kristallkaskadenstücks synchronisiert werden.

LibDriver APA102C ist der voll funktionsfähige Treiber von apa102c, der von LibDriver gestartet wurde. APA102C bietet LED-Schreiben und andere Funktionen. LibDriver entspricht MISRA.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example write](#example-write)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver APA102C-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver APA102C SPI.

/test enthält den Testcode des LibDriver APA102C-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver APA102C-Beispielcode.

/doc enthält das LibDriver APA102C-Offlinedokument.

/Datenblatt enthält APA102C-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example write

```C
#include "driver_apa102c_basic.h"

uint8_t res;
uint32_t i;
static uint32_t gs_rgb[21]; 
static uint8_t gs_temp[1024];

/* init */
res = apa102c_basic_init();
if (res != 0)
{
    return 1;
}

/* write color */
for (i = 0; i < 21; i++)
{
    gs_rgb[i] = APA102C_COLOR(color >> 16, color >> 8, color >> 0, 16);
}

/* write data */
res = apa102c_basic_write(gs_rgb, 21, gs_temp, 1024);
if (res != 0)
{
    (void)apa102c_basic_deinit();

    return 1;
}

/* close the chip */
res = apa102c_basic_deinit();
if (res != 0)
{
    return 1;
}
else
{
    return 0;
}
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/apa102c/index.html](https://www.libdriver.com/docs/apa102c/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.