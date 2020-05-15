using System;
using System.Windows.Forms;

namespace ChompWF
{
    public partial class Menu : Form
    {
        public Menu()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
            comboBox2.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Main main = new Main(comboBox1.SelectedIndex + 1, comboBox2.SelectedIndex + 1, radioButton1.Checked);
            Hide();
            if (main.ShowDialog() == DialogResult.Cancel)
                Close();
        }
    }
}
