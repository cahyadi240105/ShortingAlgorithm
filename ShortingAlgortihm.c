#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int NIM;
    char NAMA[100];
} Data;

int BacaData(const char *filename, Data **data)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Gagal membuka file %s\n", filename);
        return -1;
    }

    int count = 0;
    char buffer[150];
    while (fgets(buffer, sizeof(buffer), file))
    {
        count++;
    }
    rewind(file);

    *data = (Data *)malloc(count * sizeof(Data));
    for (int i = 0; i < count; i++)
    {
        fscanf(file, "%d %[^\n]", &(*data)[i].NIM, (*data)[i].NAMA);
    }

    fclose(file);
    return count;
}

void tukar(Data *a, Data *b)
{
    Data temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(Data *data, int low, int high, int ascending, int byNIM)
{
    if (low < high)
    {
        int pivot = byNIM ? data[high].NIM : strcmp(data[high].NAMA, "");
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            int comparison = byNIM ? data[j].NIM : strcmp(data[j].NAMA, data[high].NAMA);
            if ((ascending && comparison <= pivot) || (!ascending && comparison >= pivot))
            {
                i++;
                tukar(&data[i], &data[j]);
            }
        }
        tukar(&data[i + 1], &data[high]);

        quickSort(data, low, i, ascending, byNIM);
        quickSort(data, i + 2, high, ascending, byNIM);
    }
}

void cetakData(Data *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d %s\n", data[i].NIM, data[i].NAMA);
    }
}

void sortAndMeasure(Data *data, int size, int algorithm, int ascending, int byNIM)
{
    clock_t start = clock();
    if (algorithm == 1)
    {
        quickSort(data, 0, size - 1, ascending, byNIM);
    }

    clock_t end = clock();
    cetakData(data, size);
    printf("Total time: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Command error. You need data file as arguments\n");
        return 1;
    }

    Data *data;
    int size = BacaData(argv[1], &data);
    if (size < 0)
        return 1;

    int choice, order, sortBy;
    while (1)
    {
        printf("\nMain Menu\n");
        printf("1. Quick Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Merge Sort\n");
        printf("4. Insertion Sort\n");
        printf("5. Quit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 5)
            break;
        if (choice < 1 || choice > 5)
        {
            printf("Wrong Input. Should only number from number 1 to number 5.\n");
            continue;
        }

        printf("\nOption\n");
        printf("1. Ascending order on NIM\n");
        printf("2. Descending order on NIM\n");
        printf("3. Ascending order on NAMA\n");
        printf("4. Descending order on NAMA\n");
        printf("Your choice: ");
        scanf("%d", &order);

        if (order < 1 || order > 4)
        {
            printf("Wrong input. Should only number from number 1 to number 4\n");
            continue;
        }

        sortBy = (order <= 2);
        int ascending = (order == 1 || order == 3);

        sortAndMeasure(data, size, choice, ascending, sortBy);
    }

    free(data);
    return 0;
}
