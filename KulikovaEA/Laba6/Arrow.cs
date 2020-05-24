using System;

namespace ProjectNetwork
{
    class Arrow
    {// Класс Работа
        string action; // Действие
        uint time; // Время
        string resource; // Ресурсы
        Node nodeIn = null; // Узел начала
        Node nodeOut = null; // Узел конца

        public string Action => action;
        public uint Time => time;
        public string Resource => resource;
        public Node NodeIn => nodeIn;
        public Node NodeOut => nodeOut;

        public Arrow(string a, uint t, string r)
        {
            action = a;
            time = t;
            resource = r;
        }
        // Функция заполняющая узлы ребра
        public void InOut(Node n1, Node n2)
        {
            nodeIn = n1;
            nodeOut = n2;
        }
        // Функция проверяющая выбрано ли данное ребро
        public bool Selected(int _x, int _y)
        {
            int p1x = nodeIn.X, p1y = nodeIn.Y;
            int p2x = nodeOut.X, p2y = nodeOut.Y;
            if (nodeIn == nodeOut)
            {// Если петля
                if (_x > p1x - 30 && _x < p1x)
                    if (_y > p1y - 30 && _y < p1y)
                        return true;
            }
            if (Length(p1x, p1y, _x, _y) + Length(p2x, p2y, _x, _y) - Length(p1x, p1y, p2x, p2y) < 1)
                return true;
            return false;
        }
        // Расстояние между двумя точками
        double Length(int x1, int y1, int x2, int y2) =>
            Math.Sqrt(Math.Pow(x1 - x2, 2) + Math.Pow(y1 - y2, 2));
    }
}
