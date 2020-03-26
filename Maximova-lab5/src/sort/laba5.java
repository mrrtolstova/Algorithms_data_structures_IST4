package sort;
import java.util.Scanner;

public class laba5 {
       
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);  //Ввод с клавиатуры 
        int K;
        System.out.println("\033[34mПожалуйста введите число больше нуля(количество чисел)\033[0m");
        do
            {
                while(!in.hasNextInt())
                {
                    System.out.println("\033[31mПожалуйста введите число\033[0m");
                    in.next();
                }
                K =in.nextInt();
                if (K <= 0)
                {
                    System.out.println("\033[31mНе пытайтесь вводить что-то другое...Вас попросили ввести число больше нуля, потому что количество не может быть отрицательным.\033[0m");
                    System.out.println("\033[31mПожалуйста введите число больше нуля.\033[0m");
                }

            }while(K <= 0);
        
        System.out.println("\n\033[34mКоличество чисел: \033[0m"+K);
        
        //создаем массив и заполняем его
        int[] Array = new int[K];
        for (int i = 0; i < Array.length; i++) 
        {
            Array[i] = (int) Math.round((Math.random() * 100) - 50);
        }
        
        //вывод массива на экран
        System.out.println("Наши прекрасные числа:"); 
        for(int i=0; i<K; i++)
        {
            System.out.print(Array[i] + "    ");  
        }
        System.out.println(" ");
        
        //нахождение наибольшего числа
        int max=Array[0];
        for (int i = 0; i < K; i++) 
        {
            if (Array[i] > max)
            {
                max = Array[i]; 
            }
        }
        System.out.println(" ");
        System.out.println("Наибольшее число "+max);
        
        //нахождение наименьшего числа
        int min=Array[0];
        for (int i = 0; i < K; i++) 
        {
            if (Array[i] < min) 
            {
                min = Array[i]; 
            }
        }
        System.out.println(" ");
        System.out.println("Наименьшее число "+min);
        
        //нахождение числа наиболее близкого к нулю
        int num  = 0;
        int elem = Array[0];
        for(int i: Array) 
            if(Math.abs(num-i)<max)
            {
                max = Math.abs(num-i);
                elem = i;
            }
        System.out.println(" ");
        System.out.println("Наиболее близкое к нулю: " +elem);
    }
}
