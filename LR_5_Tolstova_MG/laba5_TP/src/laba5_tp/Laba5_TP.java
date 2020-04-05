/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package laba5_tp;
import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;


public class Laba5_TP {

    public static void heapSort(int[] myArray, int length) {
      int temp;
      int size = length-1;
      for (int i = (length / 2); i >= 0; i--) {
        heapify(myArray, i, size);};

      for(int i= size; i>=0; i--) {
         temp = myArray[0];
         myArray[0] = myArray[size];
         myArray[size] = temp;
         size--;
         heapify(myArray, 0, size);
        }

      System.out.println(Arrays.toString(myArray));
    }

   public static void heapify (int [] myArray, int i, int heapSize) {
      int a = 2*i;
      int b = 2*i+1;
      int largestElement;

      if (a<= heapSize && myArray[a] > myArray[i]) {
         largestElement = a;
      } else  {
         largestElement = i;
      }

      if (b <= heapSize && myArray[b] > myArray[largestElement]) {
         largestElement = b;
      }

      if (largestElement != i) {
         int temp = myArray[i];
         myArray[i] = myArray[largestElement];
         myArray[largestElement] = temp;
         heapify(myArray, largestElement, heapSize);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random random= new Random();
        
        int size;
        do { System.out.println("Введите количество элементов массива: ");
        while (!scanner.hasNextInt()) {
        System.out.println("Неверный символ! Введите число: ");
        scanner.next(); 
        }
        size = scanner.nextInt();} while (size <= 0);
        int[] myArray = new int[size];
        for(int i=0; i<size; i++) {
        myArray[i] = random.nextInt(20);
        }

      heapSort(myArray, size);
    }
}
