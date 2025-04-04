
# Octavian test - Slot Machine

**Зависимости**

C++17

SFML 3.0.0 (32-bit)

**Структура проекта**

    ├── Game/
    │   ├── Entities/
    │   │   ├── SlotMachine/    # Логика работы слот-машины
    │   │   │   ├── State/
    │   │   │   │   └── SlotMachineState.hpp  # Описание состояний слот-машины, переход между состояниями 
    │   │   │   ├── Reel.hpp          # Логика работы барабана - смещение, анимация прокрутки, "докрутка" барабана до нужной позиции с замедлением
    │   │   │   ├── ReelSymbol.hpp    # Спрайт символа, его id, отрисовка и изменение положения
    │   │   │   └── SlotMachine.hpp   # Общая логика работы слот-машины - начало/конец вращения барабанов, обработка ввода, 
    │   │   └── IEntity.hpp  # Общий интерфейс для всех сущностей (SlotMachine, Reel, ReelSymbol)
    │   ├── GameRule.hpp  # Правила начисления очков в зависимости от положения символов
    │   ├── Command.hpp   # Enum-команды (обработка ввода -> передача команды) 
    │   ├── Random.hpp    # Генерация рандомных целочисленных значений
    │   └── Game.hpp      # Инициализация и игровой цикл
    ├── Graphics/
    │   ├── Scene.hpp        # Добавление Entities, их отрисовка и обновление состояния
    │   └── TexturePool.hpp  # Общий пул текстур 
    └── UI/
        ├── Button.hpp    # Обработка нажаний на кнопки, вызов колбеков по нажатию
        ├── TextField.hpp # Вывод изменяемых текстовых полей на экран
        └── UI.hpp        # Базовый класс для отрисовки интерфейса и обработки кликов
           
**Сборка**

x86-Release
