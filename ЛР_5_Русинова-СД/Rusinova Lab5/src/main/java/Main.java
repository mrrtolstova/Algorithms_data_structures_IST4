
import java.util.Random;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Acer
 */
public class Main {
    
    //Рандомизатор целых чисел на интервале
     private static int getRandomNumberInRange(int min, int max) 
    {
	Random r = new Random();
	return r.nextInt((max - min) + 1) + min;
    }
    //Функция заполнения массива случайнми значениями
      private static int[] getRandomArray(int min, int max,int n,int[] array) 
    {
	
        for(int i=0;i<n;i++){
            array[i]=getRandomNumberInRange(min,max);
        }
	return array;
    }
    //Сортировка по убыванию
      private static int[] DescendingBubbleSort(int[] array, int n){
          int temp=0;
          for(int i=0;i<n;i++){
              for(int j=0;j<n-1;j++){
                  if(array[j]<array[j+1]){
                      temp=array[j];
                      array[j]=array[j+1];
                      array[j+1]=temp;
                  }
                  
              }
          }
          return array;
      }
      //Сортировка по возрастанию
      private static int[] AscendingBubbleSort(int[] array, int n){
          int temp=0;
          for(int i=0;i<n;i++){
              for(int j=0;j<n-1;j++){
                  if(array[j]>array[j+1]){
                      temp=array[j];
                      array[j]=array[j+1];
                      array[j+1]=temp;
                  }
                  
              }
          }
          return array;
      }
      //Вывод массива
      private static void PrintArray(int[] array){
          for(int i=0;i<array.length;i++){
          System.out.print(array[i]+" ");
          }
          System.out.println();
      }
     public static void main(String[] arg){
         //Создание массива
         int[] array= new int[getRandomNumberInRange(8,10)];
         //Заполнение массива
         getRandomArray(0,20,array.length,array);
         //Вывод массива
         System.out.print("Initial array: ");
         PrintArray(array);
         System.out.print("Descending array: ");
         //Сортировка и вывод массива по убыванию
         DescendingBubbleSort(array,array.length);
         PrintArray(array);
         System.out.print("Ascending array: ");
         //Сортировка и вывод массива по возрастанию
         AscendingBubbleSort(array,array.length);
         PrintArray(array);
         
         
     }
}
