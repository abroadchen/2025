

namespace DefaultNamespace;

public class MergeSort
{



    static int[] Sort(int[] left, int[] right)
    {
        int[] array = new int[left.Length + right.Length];
        int leftIndex = 0;
        int rightIndex = 0;
        for (int i = 0; i < array.Length; i++)
        {
            if (leftIndex >= left.Length)
            {
                array[i] = right[rightIndex];
                rightIndex++;
            }
            else if (rightIndex >= right.Length)
            {
                array[i] = left[leftIndex];
                leftIndex++;
            }
            else if (left[leftIndex] < right[rightIndex])
            {
                array[i] = left[leftIndex];
                leftIndex++;
            }
            else
            {
                array[i] = right[rightIndex];
                rightIndex++;
            }
        }

        return array;
    }



    static int[] Merge(int[] array)
    {

        if (array.Length < 2)
            return array;
        
        
        
        int mid = array.Length / 2;
        int[] left = new int[mid];
        int[] right = new int[array.Length - mid];
        for (int i = 0; i < array.Length; i++)
        {
            if (i < mid)
                left[i] = array[i];
            else
                right[i - mid] = array[i];
        }

        return Sort(Mege(left), Merge(right));
    }
}