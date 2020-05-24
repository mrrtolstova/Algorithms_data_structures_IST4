using System;
using System.IO;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace ProjectNetwork
{
    public partial class Main : Form
    {
        SqlConnection connection;
        Dictionary<uint, Node> nodes; // Узлы
        List<Arrow> arrows; // Ребра
        uint current = 1; // Текущий номер узла
        bool flagAddNode = false;
        bool flagAddArrow = false;
        uint r = 15; // Радиус узла
        uint selectedNode = 0; // Узел из которого начинается ребро

        public Main()
        {
            InitializeComponent();
            nodes = new Dictionary<uint, Node>();
            arrows = new List<Arrow>();
            comboBox1.SelectedIndex = 0; // По умолчанию выбран ориентированный граф
            button2.Enabled = false;
            string connectionString = @"Data Source=.\SQLEXPRESS;Initial Catalog=PW;Integrated Security=True";
            connection = new SqlConnection(connectionString);
            connection.Open();
        }

        private void drawGraph()
        {// Отрисовка структуры данных
            Graphics gr = pictureBox1.CreateGraphics();
            foreach (var a in arrows)
            {// Отрисовка всех ребер
                if(a.NodeIn != null && a.NodeOut != null)
                {
                    Pen pen = new Pen(Brushes.Black, 5);
                    int beginX = a.NodeIn.X, beginY = a.NodeIn.Y;
                    // Для деревьев и ориентированного графа ребра оиентированы
                    if (comboBox1.SelectedIndex == 0 || comboBox1.SelectedIndex == 2)
                        pen.EndCap = System.Drawing.Drawing2D.LineCap.ArrowAnchor;
                    // Если затрачиваемые ресурсы отсутствуют, то ребро пунктирное
                    if (a.Resource == "")
                        pen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                    if (a.NodeIn == a.NodeOut) // Если петля
                        gr.DrawArc(pen, beginX - 2 * r, beginY - 2 * r, 2 * r, 2 * r, 90, 270);
                    else
                    {
                        int end = a.NodeOut.X - (int)r;
                        if (a.NodeOut.X < beginX)
                            end = a.NodeOut.X + (int)r;
                        gr.DrawLine(pen, beginX, beginY, end, a.NodeOut.Y);
                    }
                }
            }
            foreach (var n in nodes)
            {// Отрисовка всех узлов
                int x = n.Value.X, y = n.Value.Y;
                gr.FillEllipse(Brushes.White, (x - r), (y - r), 2 * r, 2 * r);
                gr.DrawEllipse(Pens.Black, (x - r), (y - r), 2 * r, 2 * r);
                gr.DrawString(n.Key.ToString(), new Font("Arial", 15), Brushes.Black, new Point(x - 9, y - 11));
            }
        }

        private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
        {// В поле "Время" можно вводить только числа и использовать Backspace
            if (!Char.IsDigit(e.KeyChar) && e.KeyChar != 8)
                e.Handled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {// Добавить событие
            comboBox1.Enabled = false; // Больше нельзя редактировать тип графа
            button4.Enabled = false; // Больше нельзя загрузить структуру данных
            button2.Enabled = false;
            if (flagAddNode)
            {
                label5.Text = "Добавьте узел на поле";
                return;
            }
            nodes.Add(current++, new Node(textBox1.Text));
            flagAddNode = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {// Добавить работу
            comboBox1.Enabled = false; // Больше нельзя редактировать тип графа
            button1.Enabled = false;
            if (flagAddArrow)
            {
                label5.Text = "Добавьте ребро на поле";
                return;
            }
            uint time = 0;
            if (textBox3.Text != "")
                time = Convert.ToUInt32(textBox3.Text);
            arrows.Add(new Arrow(textBox2.Text, time, textBox4.Text));
            flagAddArrow = true;
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {// Клик по полю
            label5.Text = "Ошибки";
            listBox1.Items.Clear();
            if (!flagAddNode && !flagAddArrow)
            {// Информация о событии или работе
                foreach (var n in nodes)
                {
                    if (n.Value.Selected(e.X, e.Y))
                    {
                        listBox1.Items.Add("Событие №" + n.Key.ToString());
                        listBox1.Items.Add(n.Value.State);
                        return;
                    }
                }
                foreach (var a in arrows)
                {
                    if (a.Selected(e.X, e.Y))
                    {
                        uint input = nodes.FirstOrDefault(x => x.Value == a.NodeIn).Key;
                        uint output = nodes.FirstOrDefault(x => x.Value == a.NodeOut).Key;
                        listBox1.Items.Add("Работа из " + input.ToString() + " в " + output.ToString());
                        listBox1.Items.Add("Действие " + a.Action);
                        listBox1.Items.Add("Время(мин) " + a.Time);
                        listBox1.Items.Add("Ресурсы " + a.Resource);
                        return;
                    }
                }
            }
            if (flagAddNode)
            {// Отрисовка события
                nodes.Values.Last().Coordinates(e.X, e.Y);
                flagAddNode = false;
                if (current > 2) // Нельзя добавлять ребра пока узлов меньше 2
                    button2.Enabled = true;
            }
            if (flagAddArrow)
            {// Отрисовка работы
                if (selectedNode == 0)
                {// Выбор выходного узла ребра
                    foreach (var n in nodes)
                    {
                        if (n.Value.Selected(e.X, e.Y))
                        {
                            selectedNode = n.Key;
                            break;
                        }
                    }
                    return; // Первая вершина выбрана
                }
                foreach (var n in nodes)
                {// Выбор входящего узла ребра
                    if (n.Value.Selected(e.X, e.Y))
                    {
                        if (comboBox1.SelectedIndex == 2)
                        {// Если структура данных дерево
                            if (n.Key == 1)
                            {
                                label5.Text = "В корень дерева ребра не входят";
                                return;
                            }
                            if (n.Value.Input || n.Key == selectedNode)
                            {
                                label5.Text = "В дереве не может быть циклов или петель";
                                return;
                            }
                            n.Value.Input = true;
                        }
                        arrows.Last().InOut(nodes[selectedNode], n.Value);
                        selectedNode = 0;
                        flagAddArrow = false;
                        button1.Enabled = true;
                        break;
                    }
                }
            }
            drawGraph();
        }

        private void pictureBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {// При двойном клике выполняется тоже, что и для одного
            pictureBox1_MouseClick(sender, e);
        }

        private void button5_Click(object sender, EventArgs e)
        {// Кнопка отмены добавления
            listBox1.Items.Clear();
            if (flagAddNode)
            {// Отмена узла
                button2.Enabled = true;
                nodes.Remove(--current);
                flagAddNode = false;
            }
            if (flagAddArrow)
            {// Отмена ребра
                button1.Enabled = true;
                arrows.Remove(arrows.Last());
                flagAddArrow = false;
                selectedNode = 0;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {// Запись
            if (radioButton1.Checked)
            {// В файл
                using (StreamWriter sw = new StreamWriter("PN.txt", false, System.Text.Encoding.Default))
                {
                    sw.WriteLine(comboBox1.SelectedIndex);
                    sw.WriteLine(current - 1);
                    foreach (var n in nodes)
                    {// Запись узлов
                        sw.WriteLine(n.Key);
                        sw.WriteLine(n.Value.State);
                        sw.WriteLine(n.Value.X);
                        sw.WriteLine(n.Value.Y);
                        sw.WriteLine(n.Value.Input);
                    }
                    sw.WriteLine(arrows.Count);
                    foreach (var a in arrows)
                    {// Запись ребер
                        sw.WriteLine(a.Action);
                        sw.WriteLine(a.Time);
                        sw.WriteLine(a.Resource);
                        sw.WriteLine(nodes.FirstOrDefault(x => x.Value == a.NodeIn).Key);
                        sw.WriteLine(nodes.FirstOrDefault(x => x.Value == a.NodeOut).Key);
                    }
                }
            }
            else
            {// В базу данных
                // Очищение таблиц данных
                string sql = "TRUNCATE TABLE Arrow";
                SqlCommand command = new SqlCommand(sql, connection);
                command.ExecuteNonQuery();
                sql = "TRUNCATE TABLE Node";
                command = new SqlCommand(sql, connection);
                command.ExecuteNonQuery();

                foreach (var n in nodes)
                {// Запись узлов
                    sql = "INSERT Node VALUES ('" + n.Value.State + "', '" + n.Value.X + "', '"
                        + n.Value.Y + "', '" + n.Value.Input + "', '" + comboBox1.SelectedIndex + "')";
                    command = new SqlCommand(sql, connection);
                    command.ExecuteNonQuery();
                }
                for (int i = 0; i < arrows.Count; i++)
                {// Запись ребер
                    sql = "INSERT Arrow VALUES ('" + arrows[i].Action + "', '" + arrows[i].Time + "', '"
                        + arrows[i].Resource + "', '" + nodes.FirstOrDefault(x => x.Value == arrows[i].NodeIn).Key + "', '"
                        + nodes.FirstOrDefault(x => x.Value == arrows[i].NodeOut).Key + "')";
                    command = new SqlCommand(sql, connection);
                    command.ExecuteNonQuery();
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {// Загрузка
            if (radioButton1.Checked)
            {// Из файла
                using (StreamReader sr = new StreamReader("PN.txt", System.Text.Encoding.Default))
                {
                    comboBox1.SelectedIndex = Convert.ToInt32(sr.ReadLine());
                    current = Convert.ToUInt32(sr.ReadLine());
                    for (uint i = 0; i < current; i++)
                    {// Чтение узлов
                        uint key = Convert.ToUInt32(sr.ReadLine());
                        string state = sr.ReadLine();
                        int x = Convert.ToInt32(sr.ReadLine());
                        int y = Convert.ToInt32(sr.ReadLine());
                        bool input = Convert.ToBoolean(sr.ReadLine());
                        nodes.Add(key, new Node(state));
                        nodes.Values.Last().Coordinates(x, y);
                        nodes.Values.Last().Input = input;
                    }
                    current++;
                    uint arrowsSize = Convert.ToUInt32(sr.ReadLine());
                    for (uint i = 0; i < arrowsSize; i++)
                    {// Чтение ребер
                        string action = sr.ReadLine();
                        uint time = Convert.ToUInt32(sr.ReadLine());
                        string resource = sr.ReadLine();
                        uint nodeIn = Convert.ToUInt32(sr.ReadLine());
                        uint nodeOut = Convert.ToUInt32(sr.ReadLine());
                        arrows.Add(new Arrow(action, time, resource));
                        arrows.Last().InOut(nodes[nodeIn], nodes[nodeOut]);
                    }
                }
            }
            else
            {// Из базы данных
                string sql = "SELECT * FROM Node";
                SqlDataAdapter adapter = new SqlDataAdapter(sql, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds);
                DataTable dt = ds.Tables[0];

                comboBox1.SelectedIndex = Convert.ToInt32(dt.Rows[0][5]);
                current = Convert.ToUInt32(dt.Rows.Count);
                for (int i = 0; i < current; i++)
                {// Чтение узлов
                    uint key = Convert.ToUInt32(dt.Rows[i][0]);
                    string state = dt.Rows[i][1].ToString();
                    int x = Convert.ToInt32(dt.Rows[i][2]);
                    int y = Convert.ToInt32(dt.Rows[i][3]);
                    bool input = Convert.ToBoolean(dt.Rows[i][4]);
                    nodes.Add(key, new Node(state));
                    nodes.Values.Last().Coordinates(x, y);
                    nodes.Values.Last().Input = input;
                }
                current++;

                sql = "SELECT * FROM Arrow";
                adapter = new SqlDataAdapter(sql, connection);
                ds = new DataSet();
                adapter.Fill(ds);
                dt = ds.Tables[0];

                int arrowsSize = Convert.ToInt32(dt.Rows.Count);
                for (int i = 0; i < arrowsSize; i++)
                {// Чтение ребер
                    string action = dt.Rows[i][1].ToString();
                    uint time = Convert.ToUInt32(dt.Rows[i][2]);
                    string resource = dt.Rows[i][3].ToString();
                    resource = resource.Trim();
                    uint nodeIn = Convert.ToUInt32(dt.Rows[i][4]);
                    uint nodeOut = Convert.ToUInt32(dt.Rows[i][5]);
                    arrows.Add(new Arrow(action, time, resource));
                    arrows.Last().InOut(nodes[nodeIn], nodes[nodeOut]);
                }
            }
            comboBox1.Enabled = false;
            if (current > 2)
                button2.Enabled = true;
            button4.Enabled = false;
            drawGraph();
        }
    }
}
