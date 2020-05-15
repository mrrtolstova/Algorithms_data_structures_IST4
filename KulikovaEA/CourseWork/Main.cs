using System;
using System.Collections.Generic;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace ChompWF
{
    public partial class Main : Form
    {
        List<List<Button>> labels;
        List<List<bool>> board;
        Chomp chomp;
        int n, m;
        bool player;

        bool PlayerMove(int iter1, int iter2, bool p)
        {
            for (int i = iter1; i < n; i++)
            {
                for (int j = iter2; j < m; j++)
                {
                    labels[i][j].BackColor = Color.FromArgb(255, 255, 255);
                    labels[i][j].Enabled = false;
                    board[i][j] = false;
                }
            }
            if (iter1 == 0 && iter2 == 0)
            {
                if (p)
                    MessageBox.Show("Игра окончена. Вы проиграли.");
                else
                    MessageBox.Show("Игра окончена. Вы победили.");
                return true;
            }
            return false;
        }

        public Main(int _n, int _m, bool p)
        {
            InitializeComponent();
            n = _n; m = _m;
            player = p;
            ClientSize = new Size(248, 248);
            labels = new List<List<Button>>(n);
            board = new List<List<bool>>(n);
            chomp = new Chomp(n, m);
            EventHandler handler = (s, ev) =>
            {
                Button me = (Button)s;
                if (PlayerMove(me.TabIndex / 10, me.TabIndex % 10, true))
                {
                    Close();
                    return;
                }
                Thread.Sleep(1500);
                List<int> res = new List<int>(3);
                res = chomp.minimax(board, int.MinValue, int.MaxValue, true);
                if (PlayerMove(res[1], res[2], false))
                    Close();
            };
            for (int i = 0; i < n; i++)
            {
                labels.Add(new List<Button>(m));
                board.Add(new List<bool>(m));
                for (int j = 0; j < m; j++)
                {
                    board[i].Add(true);
                    labels[i].Add(new Button
                    {
                        BackColor = Color.FromArgb(128, 255, 128),
                        Location = new Point(12 + 46 * j, 12 + 46 * i),
                        Size = new Size(40, 40),
                        TabIndex = i * 10 + j,
                        TabStop = true
                    });
                    labels[i][j].Click += handler;
                    Controls.Add(labels[i][j]);
                }
            }
            labels[0][0].BackColor = Color.FromArgb(255, 128, 128);
            if (!player)
            {
                List<int> res = new List<int>(3);
                res = chomp.minimax(board, int.MinValue, int.MaxValue, true);
                if (PlayerMove(res[1], res[2], false))
                {
                    Load += (se, ee) => Close();
                    return;
                }
            }
        }
    }
}
