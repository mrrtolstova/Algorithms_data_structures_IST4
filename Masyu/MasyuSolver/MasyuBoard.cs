using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Masyu

{
    public class MasyuBoard
    {
        // Знаки необходимые для наглядного восприятия ( Исключений клеток, возможные клетки и т.д.)
        public static char[] CHARS = new char[] { '.', 'Q', 'O', '-', 'X', 'v', '^', '*' };

        // Заметка: Кортеж - это тип данных, которое может хранить набор значений.
        // Объявления кортежа для Шаблона (черных и белых кругов)
        static Tuple<string, string>[] PATTERN_STRING_PAIRS = new Tuple<string, string>[]
        {
            // Завершение линий через круги.
            new Tuple<string, string>("....\nQ-..\n....", "..X.\nQ-.-\n..X."),
            new Tuple<string, string>("...\n-O.\n...", ".X.\n-O-\n.X."),
            // Продолжение линий через "x".
            new Tuple<string, string>("...\nX*X\n.-.", ".-.\nX.X\n.-."),
            new Tuple<string, string>(".X.\nX*.\n.-.", ".X.\nX.-\n.-."),
            // Помещаем "x" заблокированные клетки  вокруг кругов .
            new Tuple<string, string>(".-.\n-*.\n...", ".-.\n-.X\n.X."),
            new Tuple<string, string>(".-.\n.*.\n.-.", ".-.\nX.X\n.-."),
            new Tuple<string, string>(".X.\nX*X\n...", ".X.\nX.X\n.X."),
            // Правило для черных кругов .
            new Tuple<string, string>("-Q.", "-QX"),
            // Кортеж блокировки черных кругов .
            new Tuple<string, string>(".....\nXQ...\n.....", "...X.\nXQ-.-\n...X."),
            new Tuple<string, string>(".......\nX..Q...\n.......", ".....X.\nX.XQ-.-\n.....X."),
            new Tuple<string, string>(".........\n...Q.Q...\n.........", ".X.....X.\n-.-QXQ-.-\n.X.....X."),
            new Tuple<string, string>(".....-\n...Q..\n......", ".X...-\n-.-QX.\n.X...."),
            new Tuple<string, string>("..........\n...Q...O.O\n..........", ".X........\n-.-QX..O.O\n.X........"),
            new Tuple<string, string>("O...O\n.....\n..Q..\n.....\n.....\n.....", "O...O\n..X..\n..Q..\n..-..\n.X.X.\n..-.."),
            // Правило для белых кругов .
            new Tuple<string, string>("-.-O...", "-.-O-.X"),
            // Кортеж блокировки белых кругов .
            new Tuple<string, string>("...\n.O.\n.X.", ".X.\n-O-\n.X."),
            new Tuple<string, string>(".......\n.O.O.O.\n.......", ".-.-.-.\nXOXOXOX\n.-.-.-."),
            new Tuple<string, string>(".......\n-..O.O.\n.......", "...-.-.\n-.XOXOX\n...-.-."),
            new Tuple<string, string>(".......\n-..O..-\n.......", "...-...\n-.XOX.-\n...-..."),
            // вход / выход / стены 
            new Tuple<string, string>("v-.", "v-^"),
            new Tuple<string, string>("^-.", "^-v"),
            new Tuple<string, string>("vX.", "vXv"),
            new Tuple<string, string>("^X.", "^X^"),
            new Tuple<string, string>("v.^", "v-^"),
            new Tuple<string, string>("^.v", "^-v"),
            new Tuple<string, string>("v.v", "vXv"),
            new Tuple<string, string>("^.^", "^X^"),
        };

        // Изначальное состояние структуры.
        private bool valid = true;
        
        // Объявления массивов и списков и т.д.

        // Обьявления доски в виде двухмерный массив целцелочисленных данных .
        // Заметка: Ключевое слово "byte" - используются для удобства преобразования типа данных.
        private byte[,] board;
        // Пременная "Число активных циклов"
        private int activeLoopCount;
        // Массив целцелочисленных данных "Окончания цикла" 
        private int[] loopEnds;
        // Представить длинный массив простейший список однотипных объектов. 
        private List<int[]> loopEndLookups;

        // Допольнительные ресурсы 
 
        // Двухмерный массив целцелочисленных данных "Таблица поиска соседей петли"
        private int[][] loopNeighborLookupTable;
        // Список поиска шаблонов.
        private List<MasyuPattern>[,,] patternLookupTable;



        public MasyuBoard(int width, int height) {
            // Заполните доску, добавив X и Out по периметру.
            int arrWidth = width * 2 + 1, arrHeight = height * 2 + 1;
            board = new byte[arrWidth, arrHeight];
            for (int x = 0; x < arrWidth; x++) {
                for (int y = 0; y < arrHeight; y++) {
                    if (x != 0 && x != arrWidth - 1 && y != 0 && y != arrHeight - 1) {
                        continue;
                    }
                    // Если условие board[x, y] имеет значение true, вычисляет и возвращает 6-bit, в противном случае вычисляет и возвращает 4-bit.
                    board[x, y] = (x + y) % 2 == 0 ? (byte)6 : (byte)4;
                }
            }
            // Инициализация структуры данных цикла.
            loopEnds = new int[arrWidth * arrHeight];
            loopEndLookups = new List<int[]>();
            loopEndLookups.Add(new int[] { -1, -1 });
            loopNeighborLookupTable = new int[arrWidth * arrHeight][];
            for (int y = 0; y < arrHeight; y++) {
                for (int x = 0; x < arrWidth; x++) {
                    int i = y * arrWidth + x;
                    if ((x + y) % 2 != 1) {
                        // Игнорировать непроходные клетки.
                        continue;
                    }
                    // Создайте массив всех соседей и пути этой ячейки.
                    loopNeighborLookupTable[i] = Util.GetPathNeighbors(x, y, arrWidth, arrHeight);
                }
            }
            // Список "Таблица поиска шаблонов"
            patternLookupTable = new List<MasyuPattern>[arrWidth, arrHeight, 7];
            for (int x = 0; x < patternLookupTable.GetLength(0); x++) {
                for (int y = 0; y < patternLookupTable.GetLength(1); y++) {
                    for (int z = 0; z < patternLookupTable.GetLength(2); z++) {
                        patternLookupTable[x, y, z] = new List<MasyuPattern>();
                    }
                }
            }
            // Реализация вычисления координат. Путем центрирования и смещения шаблона.
            foreach (Tuple<string, string> patternStringPair in PATTERN_STRING_PAIRS) {
                Debug.Assert(patternStringPair.Item1.Length == patternStringPair.Item2.Length);
                Tuple<int, int, byte>[] checkPattern = Util.ParsePatternString(patternStringPair.Item1);
                Tuple<int, int, byte>[] setPattern = Util.ParsePatternString(patternStringPair.Item2);
                List<Tuple<int, int, byte, bool>> combined = new List<Tuple<int, int, byte, bool>>(checkPattern.Select(t => new Tuple<int, int, byte, bool>(t.Item1, t.Item2, t.Item3, false)));
                combined.AddRange(setPattern.Except(checkPattern).Select(t => new Tuple<int, int, byte, bool>(t.Item1, t.Item2, t.Item3, true)));
                Tuple<int, int, byte, bool>[][] patternRotations = Util.AllPatternRotationsAndReflections(combined);
                //
                foreach (Tuple<int, int, byte, bool>[] rotation in patternRotations) {
                    int maxX = rotation.Max(t => t.Item1);
                    int maxY = rotation.Max(t => t.Item2);
                    Tuple<int, int, byte>[] check = rotation.Where(t => !t.Item4).Select(t => new Tuple<int, int, byte>(t.Item1, t.Item2, t.Item3)).ToArray();
                    Tuple<int, int, byte>[] set = rotation.Where(t => t.Item4).Select(t => new Tuple<int, int, byte>(t.Item1, t.Item2, t.Item3)).ToArray();
                    // Для каждого отмеченного объекта создайте шаблон с ним в центре.
                    foreach (Tuple<int, int, byte> checkFeature in check) {
                        if (checkFeature.Item3 == 7) {
                            continue;
                        }
                        // Проверяем наличие специального символа '*', который должен быть помещен в круг.
                        Tuple<int, int, byte> starTuple = check.FirstOrDefault(t => t.Item3 == 7);
                        // Перецентрируйте шаблон.
                        Tuple<int, int, byte>[] offsetCheck = check.Where(t => t != checkFeature && t.Item3 != 7).Select(t => new Tuple<int, int, byte>(t.Item1 - checkFeature.Item1, t.Item2 - checkFeature.Item2, t.Item3)).ToArray();
                        Tuple<int, int, byte>[] offsetSet = set.Select(t => new Tuple<int, int, byte>(t.Item1 - checkFeature.Item1, t.Item2 - checkFeature.Item2, t.Item3)).ToArray();
                        MasyuPattern pattern = new MasyuPattern(offsetCheck, offsetSet);
                        int rightMargin = maxX - checkFeature.Item1;
                        int bottomMargin = maxY - checkFeature.Item2;
                        for (int x = checkFeature.Item1; x < patternLookupTable.GetLength(0) - rightMargin; x++) {
                            for (int y = checkFeature.Item2; y < patternLookupTable.GetLength(1) - bottomMargin; y++) {
                                if (starTuple != null) {
                                    int cx = x - checkFeature.Item1 + starTuple.Item1, cy = y - checkFeature.Item2 + starTuple.Item2;
                                    bool isCircleSpace = (cx % 2 == 1) && (cy % 2 == 1);
                                    if (!isCircleSpace) {
                                        continue;
                                    }
                                }
                                patternLookupTable[x, y, checkFeature.Item3].Add(pattern);
                            }
                        }
                    }
                }
            }
        }

        public void Solve(Action<string> Log, int depth) {
            Clear();
            PropagateConstraintsImpl(null);
            if (depth >= 0) {
                SolveImpl(Log, depth);
            }
        }
        public void SolveImpl(Action<string> Log, int depth) {
            // Для каждого пути попробуйте заполнить пустое пространство.
            bool changed = false;
            for (byte feature = 3; feature <= 4; feature++) {
                for (int y = 1; y < board.GetLength(1) - 1; y++) {
                    for (int x = 1 + (y % 2); x < board.GetLength(0) - 1; x += 2) {
                        if (board[x, y] != 0) {
                            continue;
                        }
                        if (board[x - 1, y] == 2 || board[x, y - 1] == 2) {
                            // Заметка: не нужно проверять обе стороны белого круга.
                            continue;
                        }
                        var backup = BackupState();
                        board[x, y] = feature;
                        PropagationResult result = PropagateConstraintsImpl(new Tuple<int, int>(x, y));
                        if (result != PropagationResult.CONTRADICTION && CheckNonPatternContradictions()) {
                            result = PropagationResult.CONTRADICTION;
                        }
                        if (result != PropagationResult.CONTRADICTION && depth > 0) {
                            SolveImpl(Log, depth - 1);
                            if (!valid) {
                                result = PropagationResult.CONTRADICTION;
                            }
                        }
                        RestoreBackup(backup);

                        if (result == PropagationResult.CONTRADICTION) {
                            board[x, y] = feature == 3 ? (byte)4 : (byte)3;
                            PropagateConstraintsImpl(new Tuple<int, int>(x, y));
                            changed = true;
                        }
                    }
                }
            }
            if (changed) {
                SolveImpl(Log, depth);
                return;
            }
            valid = PropagateConstraintsImpl(null) != PropagationResult.CONTRADICTION;
        }
        private Tuple<byte[,], int, int[], List<int[]>> BackupState() {
            byte[,] backupBoard = new byte[board.GetLength(0), board.GetLength(1)];
            Array.Copy(board, backupBoard, board.Length);
            int[] backupLoopEnds = new int[loopEnds.Length];
            Array.Copy(loopEnds, backupLoopEnds, backupLoopEnds.Length);
            List<int[]> backupLoopEndLookups = loopEndLookups.ConvertAll(arr => new int[] { arr[0], arr[1] });
            return new Tuple<byte[,], int, int[], List<int[]>>(backupBoard, activeLoopCount, backupLoopEnds, backupLoopEndLookups);
        }
        // Функция восстановления резервной копии
        private void RestoreBackup(Tuple<byte[,], int, int[], List<int[]>> backup) {
            board = backup.Item1;
            activeLoopCount = backup.Item2;
            loopEnds = backup.Item3;
            loopEndLookups = backup.Item4;
        }
        // Функция очистки доски.
        public void Clear()
        {
            for (int y = 1; y < board.GetLength(1) - 1; y++)
            {
                for (int x = 1; x < board.GetLength(0) - 1; x++)
                {
                    if (board[x, y] > 2)
                    {
                        board[x, y] = 0;
                    }
                }
            }
            Array.Clear(loopEnds, 0, loopEnds.Length);
            activeLoopCount = 0;
            loopEndLookups.Clear();
            loopEndLookups.Add(new int[] { -1, -1 });
        }
        // Ограничения.
        private PropagationResult PropagateConstraintsImpl(Tuple<int, int> placed)
        {
            bool constraintsApplied = false;
            Queue<Tuple<int, int>> newFeatureCoors = new Queue<Tuple<int, int>>();
            if (placed != null)
            {
                newFeatureCoors.Enqueue(placed);
                if (board[placed.Item1, placed.Item2] == 3) {
                    Tuple<int, int> shortCircuit = AddSegment(placed.Item1, placed.Item2);
                    if (shortCircuit != null) {
                        if (shortCircuit.Item1 == -1) {
                            return PropagationResult.CONTRADICTION;
                        }
                        newFeatureCoors.Enqueue(shortCircuit);
                    }
                }
            }
            // Если координаты не указаны, рассмотрим все круги.
            else
            {
                for (int x = 1; x < board.GetLength(0) - 1; x++)
                {
                    for (int y = 1; y < board.GetLength(1) - 1; y++)
                    {
                        if (board[x, y] > 0)
                        {
                            newFeatureCoors.Enqueue(new Tuple<int, int>(x, y));
                        }
                    }
                }
                // Также добавьте несколько угловых "x" для всех вариант.
                newFeatureCoors.Enqueue(new Tuple<int, int>(0, 1));
                newFeatureCoors.Enqueue(new Tuple<int, int>(0, board.GetLength(1) - 2));
                newFeatureCoors.Enqueue(new Tuple<int, int>(board.GetLength(0) - 1, 1));
                newFeatureCoors.Enqueue(new Tuple<int, int>(board.GetLength(0) - 1, board.GetLength(1) - 2));
            }
            // Распространение.
            while (newFeatureCoors.Count > 0)
            {
                Tuple<int, int> coor = newFeatureCoors.Dequeue();
                byte featureType = board[coor.Item1, coor.Item2];
                foreach (MasyuPattern pattern in patternLookupTable[coor.Item1, coor.Item2, featureType])
                {
                    // Проверить, относится ли шаблон к новой функции.
                    bool applies = true;
                    for (int i = 0; i < pattern.check.Length; i++)
                    {
                        if (board[coor.Item1 + pattern.check[i].Item1, coor.Item2 + pattern.check[i].Item2] != pattern.check[i].Item3)
                        {
                            applies = false;
                            break;
                        }
                    }
                    if (!applies)
                    {
                        continue;
                    }
                    // Используюем ранее проверенные шаблоны.
                    for (int i = 0; i < pattern.set.Length; i++)
                    {
                        Tuple<int, int, byte> currentPattern = pattern.set[i];
                        int x = coor.Item1 + currentPattern.Item1;
                        int y = coor.Item2 + currentPattern.Item2;
                        byte present = board[x, y];
                        if (present > 0 && present != currentPattern.Item3)
                        {
                            return PropagationResult.CONTRADICTION;
                        } else if (present == 0)
                        {
                            board[x, y] = currentPattern.Item3;
                            newFeatureCoors.Enqueue(new Tuple<int, int>(x, y));
                            constraintsApplied = true;
                            if (currentPattern.Item3 == 3) {
                                Tuple<int, int> shortCircuit = AddSegment(x, y);
                                if (shortCircuit != null) {
                                    if (shortCircuit.Item1 == -1) {
                                        return PropagationResult.CONTRADICTION;
                                    }
                                    newFeatureCoors.Enqueue(shortCircuit);
                                }
                            }
                        }
                    }
                }
            }
            return constraintsApplied ? PropagationResult.CONSTRAINTS_APPLIED : PropagationResult.NO_CONSTRAINTS_APPLIED;
        }
        private Tuple<int, int> AddSegment(int x, int y) {
            int index = x + y * board.GetLength(0);
            // Посмотрите все соседние сегменты в loopEnds.
            int[] adjacentPaths = loopNeighborLookupTable[index];
            int connectionCount = 0;
            int mergedNeighbor = 0;
            foreach (int adjacentPath in adjacentPaths) {
                int adjacentIndex = loopEnds[adjacentPath];
                if (adjacentIndex == 0) {
                    continue;
                }
                connectionCount++;
                if (connectionCount == 1) {
                    // Найден первый связанный конец цикла, расширьте его и обновите loopEnds.
                    mergedNeighbor = adjacentIndex;
                    loopEnds[index] = mergedNeighbor;
                    int[] loopLookup = loopEndLookups[mergedNeighbor];
                    if (loopLookup[0] != loopLookup[1]) {
                        loopEnds[adjacentPath] = 0;
                    }
                    if (loopLookup[0] == adjacentPath) {
                        loopLookup[0] = loopLookup[1];
                        loopLookup[1] = index;
                    } else {
                        loopLookup[1] = index;
                    }
                } else if (connectionCount == 2) {
                    // Найден конец второго цикла, объедините его в первый найденный цикл.
                    int[] firstLoopLookup = loopEndLookups[mergedNeighbor];
                    int[] loopLookup = loopEndLookups[adjacentIndex];
                    loopEnds[adjacentPath] = 0;
                    loopEnds[index] = 0;
                    if (loopLookup[0] == adjacentPath) {
                        firstLoopLookup[1] = loopLookup[1];
                    } else {
                        firstLoopLookup[1] = loopLookup[0];
                    }
                    loopEnds[firstLoopLookup[1]] = mergedNeighbor;
                    loopLookup[0] = -1;
                    loopLookup[1] = -1;
                    activeLoopCount--;
                } else {
                    // Третий конец цикла найден ... получили противоречие.
                    return new Tuple<int, int>(-1, -1);
                }
            }
            // Если мы не нашли связанных концов цикла, создайте новый цикл.
            if (connectionCount == 0) {
                loopEnds[index] = loopEndLookups.Count;
                loopEndLookups.Add(new int[] { index, index });
                activeLoopCount++;
            }
            // Если мы нашли один или несколько, сверяем последний объединенный цикл с предварительно рассчитанным ресурсом, чтобы найти сегмент, который присоединится к нему.
            // Если такой сегмент существует, пометьте его знаком X.
            // Проверим есть ли неиспользованные круги.
            else if (activeLoopCount > 1) {
                int[] lookup = loopEndLookups[mergedNeighbor];
                if (lookup[0] == -1) {
                    return new Tuple<int, int>(-1, -1);
                }
                // Предварительные вычисления.
                foreach (int intersection in loopNeighborLookupTable[lookup[0]].Intersect(loopNeighborLookupTable[lookup[1]])) {
                    int rx = intersection % board.GetLength(0);
                    int ry = intersection / board.GetLength(0);
                    if (board[rx, ry] == 0) {
                        board[rx, ry] = 4;
                        return new Tuple<int, int>(rx, ry);
                    }
                }
            }

            return null;
        }

        private bool CheckNonPatternContradictions() {
            return false;
        }

        // Функция SetCircle - задаем круги на доске.
        public void SetCircle(int x, int y, MasyuCircle circle)
        {
            int bx = x * 2 + 1, by = y * 2 + 1;
            if (board[bx, by] != 0)
            {
                board[bx, by] = 0;
                return;
            }
            int index = Array.IndexOf(CHARS, (char)circle);
            board[bx, by] = (byte)index;
        }
        // Функция GetCircle - установка кругов на доске.
        public MasyuCircle GetCircle(int x, int y)
        {
            int bx = x * 2 + 1, by = y * 2 + 1;
            byte val = board[bx, by];
            if (val == 1)
            {
                return MasyuCircle.BLACK;
            }
            if (val == 2)
            {
                return MasyuCircle.WHITE;
            }
            Debug.Assert(val == 0);
            return MasyuCircle.NONE;
        }
        // Объединение функции  GetCircle и SetCircle.
        public bool IsLine(int x, int y, bool horizontal)
        {
            int bx = horizontal ? x * 2 + 2 : x * 2 + 1;
            int by = horizontal ? y * 2 + 1 : y * 2 + 2;
            return board[bx, by] == 3;
        }
        public bool IsX(int x, int y, bool horizontal)
        {
            int bx = horizontal ? x * 2 + 2 : x * 2 + 1;
            int by = horizontal ? y * 2 + 1 : y * 2 + 2;
            return board[bx, by] == 4;
        }
        // Функция выхода.
        public MasyuInOut GetInOut(int x, int y) {
            int bx = x * 2 + 2, by = y * 2 + 2;
            byte val = board[bx, by];
            if (val == 5) {
                return MasyuInOut.IN;
            }
            if (val == 6) {
                return MasyuInOut.OUT;
            }
            Debug.Assert(val == 0);
            return MasyuInOut.UNKNOWN;
        }
        // Функция получения состояния.
        public MasyuValidity GetValidity() {
            if (valid) {
                return IsComplete() ? MasyuValidity.COMPLETE : MasyuValidity.VALID;
            }
            return MasyuValidity.INVALID;
        }
        // Функция завершения.(Успешной компиляции)
        private bool IsComplete() {
            if (activeLoopCount > 0) {
                return false;
            }
            bool empty = true;
            for (int y = 1; y < board.GetLength(1) - 1; y += 2) {
                for (int x = 1; x < board.GetLength(0) - 1; x += 2) {
                    if (board[x, y] == 0) {
                        continue;
                    }
                    empty = false;
                    int count = 0;
                    count += board[x - 1, y] == 3 ? 1 : 0;
                    count += board[x + 1, y] == 3 ? 1 : 0;
                    count += board[x, y - 1] == 3 ? 1 : 0;
                    count += board[x, y + 1] == 3 ? 1 : 0;
                    if (count != 2) {
                        return false;
                    }
                }
            }
            return !empty;
        }

        // Построение строки.
        private StringBuilder sb;
        // Изменения свойств строки.
        public override string ToString()
        {
            if (sb == null)
            {
                sb = new StringBuilder();
            }
            for (int y = 0; y < board.GetLength(1); y++)
            {
                for (int x = 0; x < board.GetLength(0); x++)
                {
                    sb.Append(CHARS[board[x, y]]);
                }
                sb.AppendLine();
            }
            string output = sb.ToString();
            sb.Clear();
            return output;
        }
    }

    // Проверка производительности структуры.
    public class MasyuPattern
    {
        public Tuple<int, int, byte>[] check, set;

        public MasyuPattern(Tuple<int, int, byte>[] check, Tuple<int, int, byte>[] after)
        {
            this.check = check;
            this.set = after;
        }
    }

    // Списоки перечислителей.
    public enum MasyuCircle
    {
        NONE = '.', BLACK = 'Q', WHITE = 'O'
    }
    public enum MasyuInOut {
        UNKNOWN, IN, OUT
    }
    enum PropagationResult {
        CONSTRAINTS_APPLIED, NO_CONSTRAINTS_APPLIED, CONTRADICTION
    }
    public enum MasyuValidity {
        INVALID, VALID, COMPLETE
    }
}