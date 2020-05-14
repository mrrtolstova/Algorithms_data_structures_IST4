﻿using Masyu.Boardsettings;
using System;
using System.Windows.Forms;

namespace Masyu {
    public partial class MasyuForm : Form {
        public int solveDepth;

        public MasyuForm() {
            InitializeComponent();
            masyuPanel.form = this;
            solveDepth = 2;
            logBox.Visible = false;
        }
        // TextBox: Проверяем успешную компиляцию.
        public void UpdateValidity(MasyuValidity validity) {
            if (validity == MasyuValidity.COMPLETE) {
                textBox1.Text = "COMPLETE";
                textBox1.BackColor = System.Drawing.Color.Green;
                textBox1.ForeColor = System.Drawing.Color.White;
            } else if (validity == MasyuValidity.VALID) {
                textBox1.Text = "VALID";
                textBox1.BackColor = System.Drawing.Color.White;
                textBox1.ForeColor = System.Drawing.Color.Black;
            } else {
                textBox1.Text = "INVALID";
                textBox1.BackColor = System.Drawing.Color.Red;
                textBox1.ForeColor = System.Drawing.Color.White;
            }
        }
        // Menu.
        private void Menu_New(object sender, EventArgs e) {
            NewDialog dlg = new NewDialog();
            if (dlg.ShowDialog() == DialogResult.OK) {
                masyuPanel.New(dlg.puzzleWidth, dlg.puzzleHeight);
            }
        }
    }
}
