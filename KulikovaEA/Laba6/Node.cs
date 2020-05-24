namespace ProjectNetwork
{
    class Node
    {// Класс Событие
        string state; // Состояние
        int x; // Координата х
        int y; // Координата у
        bool input; // Есть ли входящие ребра

        public string State => state;
        public int X => x;
        public int Y => y;
        public bool Input { get => input; set => input = value; }

        public Node(string s = "")
        {
            state = s;
            x = -1;
            y = -1;
            input = false;
        }
        // Функция заполняющая координаты узла
        public void Coordinates(int _x, int _y)
        {
            x = _x;
            y = _y;
        }
        // Функция проверяющая выбран ли данный узел
        public bool Selected(int _x, int _y)
        {
            if (_x > x - 15 && _x < x + 15)
                if (_y > y - 15 && _y < y + 15)
                    return true;
            return false;
        }
    }
}
