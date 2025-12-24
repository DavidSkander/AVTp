# Vaja – Enostavna spletna stran (HTML)

## Namen vaje
Namen vaje je bil izdelati enostavno spletno stran v jeziku HTML, ki izpisuje
različno veliko in različno postavljeno besedilo. Cilj je bil spoznati osnovno
strukturo HTML dokumenta ter uporabo CSS za oblikovanje besedila.

## Struktura HTML dokumenta
HTML dokument je sestavljen iz osnovnih elementov <!DOCTYPE>, <html>,
<head> in <body>. V razdelku <head> so definirani meta podatki, naslov
strani ter CSS stilna pravila.

## Primer začetka HTML dokumenta
<!DOCTYPE html>
<html>
<head>
    <title>Enostavna spletna stran</title>
</head>
<body>

## Oblikovanje besedila (CSS)
Za različno velikost in postavitev besedila so bili uporabljeni CSS razredi.

<style>
    .naslov {
        text-align: center;
        font-size: 36px;
    }

    .levo {
        text-align: left;
        font-size: 18px;
    }

    .desno {
        text-align: right;
        font-size: 20px;
    }

    .sredina {
        text-align: center;
        font-size: 24px;
        color: blue;
    }
</style>

## Postavitev besedila na strani
Besedilo je postavljeno levo, desno in na sredino z uporabo lastnosti text-align.

<p class="levo">To je manjše besedilo, poravnano levo.</p>
<p class="sredina">To je večje besedilo, poravnano na sredino.</p>
<p class="desno">To besedilo je poravnano desno.</p>

## Ugotovitve
- HTML omogoča enostavno strukturo spletne strani
- CSS omogoča prilagajanje velikosti in poravnave besedila
- Razredi omogočajo ponovno uporabo stilov
- Spletna stran se pravilno prikaže v brskalniku brez dodatnih knjižnic

## Zaključek
V vaji sem izdelal enostavno spletno stran, ki prikazuje različno veliko in
različno postavljeno besedilo. Spoznal sem osnovno strukturo HTML dokumenta
ter uporabo CSS za vizualno oblikovanje spletnih strani.

</body>
</html>
