

namespace DefaultNamespace;

public class QuickSort
{
    static void QuickSort(int[] array, int left, int right)
    {
        if (left >= right)
            return;
        
        
        int tempLeft, tempRight, temp;
        temp = array[left];
        tempLeft = left;
        tempRight = right;
        while (tempLeft != tempRight)
        {
            while (tempLeft < tempRight && array[tempRight] > temp)
            {
                tempRight--;
            }

            array[tempLeft] = array[tempRight];

            while (tempLeft < tempRight && array[tempLeft] < temp)
            {
                tempLeft++;
            }
            
            array[tempRight] = array[tempLeft];
        }

        array[tempRight] = temp;

        QuickSort(array, left, tempRight - 1);
        QuickSort(array, tempLeft + 1, right);
    }
}