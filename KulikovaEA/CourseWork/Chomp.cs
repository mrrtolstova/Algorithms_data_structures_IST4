using System.Collections.Generic;

namespace ChompWF
{
    class Chomp
    {
        int n, m;

        public Chomp(int _n, int _m)
        {
            n = _n;
            m = _m;
        }

        // Вызов функции вернет доступные ходы для конкретного игрового поля
        private List<List<int>> available_moves(List<List<bool>> board)
        {
            List<List<int>> moves = new List<List<int>>();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    if (board[i][j] && (i != 0 || j != 0))
                        moves.Add(new List<int>() { i, j });
            return moves;
        }

        // Вызов данной функции вернет true если победил игрок, иначе false
        bool has_won(List<List<bool>> board, bool is_maximizing)
        {
            bool sum = false;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (i == 0 && j == 0)
                        continue;
                    sum = sum || board[i][j];
                }
            }
            if (!sum && board[0][0] && !is_maximizing)
                return true;
            return false;
        }

        // Данная функция возвращает true если один из игроков победил
        bool game_is_over(List<List<bool>> board, bool is_maximizing)
        {
            return has_won(board, is_maximizing);
        }

        // Данная функция возвращает оценку при достижении "крайнего случая"
        int evaluate_board(List<List<bool>> board, bool is_maximizing)
        {
            if (has_won(board, is_maximizing))
                return 1;
            return -1;
        }

        // Создает копию доски
        List<List<bool>> deepcopy(List<List<bool>> board)
        {
            List<List<bool>> res = new List<List<bool>>(n);
            for (int i = 0; i < n; i++)
            {
                res.Add(new List<bool>(m));
                for (int j = 0; j < m; j++)
                    res[i].Add(board[i][j]);
            }
            return res;
        }

        // Вызов функции означает выполнение хода игроком на конкретной игровой доске
        bool select_space(List<List<bool>> board, List<int> move)
        {
            if (move[0] >= n || move[1] >= m)
                return false;
            if (board[move[0]][move[1]])
            {
                for (int i = move[0]; i < n; i++)
                    for (int j = move[1]; j < m; j++)
                        board[i][j] = false;
                return true;
            }
            return false;
        }

        public List<int> minimax(List<List<bool>> input_board, int alpha, int beta, bool is_maximizing)
        {
            // Крайний случай рекурсии - игра окончена
            if (game_is_over(input_board, is_maximizing))
                return new List<int>(3) { evaluate_board(input_board, is_maximizing), -1, -1 };
            // Инициализируем значения best_value и best_move
            List<int> best_move = new List<int>(2) { 0, 0 };
            int best_value;
            // Случай, когда ход максимизирующего игрока
            if (is_maximizing)
                best_value = alpha;
            // Случай, когда ход минимизирующего компьютера
            else
                best_value = beta;
            /* Пройдём циклом по всем возможным ходам, для того чтобы выбрать наилучший
            путем рекурсивных вызовов функции minimax с копией игровой доски.
            Как только рекурсия достигнет "крайнего" случая, она вернет значения из [1, -1]
            для функции, которая ее вызвала, до тех пор, пока самая "верхняя" функция в стеке
            вызовов (minimax с текущей игровой доской) не получит свое значение */
            foreach (var move in available_moves(input_board))
            {
                List<List<bool>> new_board = deepcopy(input_board);
                select_space(new_board, move);
                int hypothetical_value;
                if (is_maximizing)
                {
                    hypothetical_value = minimax(new_board, best_value, beta, !is_maximizing)[0];
                    if (hypothetical_value > best_value)
                    {
                        best_value = hypothetical_value;
                        best_move = move;
                    }
                    if (best_value >= beta)
                        return new List<int>() { best_value, best_move[0], best_move[1] };
                }
                else
                {
                    hypothetical_value = minimax(new_board, alpha, best_value, !is_maximizing)[0];
                    if (hypothetical_value < best_value)
                    {
                        best_value = hypothetical_value;
                        best_move = move;
                    }
                    if (best_value <= alpha)
                        return new List<int>() { best_value, best_move[0], best_move[1] };
                }
            }
            return new List<int>() { best_value, best_move[0], best_move[1] };
        }
    }
}
