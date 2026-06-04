# Physics Penguin
## Konfiguracja Kontrolera

Użyty mikro kontroler: Arduino Pro micro

### Połączenie komponentów
*UWAGA! W przypadku x,y obu joysticków tak naprawdę piny x i y są zamienione!
ze wglęgu na preferowaną przeze mnie orientację!*

1. Jouystick 1:
    - VR_X **A1**
    - VR_Y **A0**
    - SW **6**
2. Jouystick 2:
    - VR_X **A3**
    - VR_Y **A2**
    - SW **5**
3. IR kontroler:
    - IR **7**
4. Wyświetlacz led:
    - SCL **15**
    - SDA **16**
    - RST **8**
    - DC -> Rezystor 1k -> **9**
    - CS -> Rezystor 1k -> **10**
    - BL -> Rezystor 330 -> VCC
