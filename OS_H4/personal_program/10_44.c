#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGHT 12

void printfunction(int a[], int frame_number)
{
    int t;
    for (t = 0; t < frame_number; t++)
    {
        printf("%2d ", a[t]);
    }
    printf("\n");
}

void printpage_string(int *page_string)
{
    printf("ref : ");
    for (int i = 0; i < MAX_LENGHT; i++)
    {
        printf("%d ", page_string[i]);
    }
    printf("\n");
}

void FIFO(int *page_string, int page_frame)
{

    printpage_string(page_string);
    int fifo_fault = 0;
    int fifo_order = 0; // 最老的
    int turn = 0;       // number of page input
    int frame[page_frame];

    for (int i = 0; i < page_frame; i++)
    {
        frame[i] = -1;
    }
    while (turn < MAX_LENGHT)
    {
        for (int i = 0; i < page_frame; i++)
        {
            if (page_string[turn] == frame[i])
            {
                printf("          ");
                break;
            }
            if (i == (page_frame - 1))
            {
                printf(" [%d f]    ", page_string[turn]);
                fifo_fault++;
                frame[fifo_order] = page_string[turn];
                fifo_order++;
            }
        }
        printfunction(frame, page_frame);

        //		fifo_order++;
        turn++;

        if (fifo_order == page_frame)
        {
            fifo_order = 0; // 輪替，0固定最老
        }
    }

    printf("\nFIFO page fault = %d\n\n", fifo_fault);
}

void LRU(int *page_string, int page_frame)
{

    printpage_string(page_string);
    int frame_LRU[page_frame];
    for (int i = 0; i < page_frame; i++)
    {
        frame_LRU[i] = -1;
    }

    int LRU_fault = 0;
    int turn_LRU = 0;       // number of page input
    int write_position = 0; // 插入值的地方

    int k;
    while (turn_LRU < MAX_LENGHT)
    {
        for (int i = 0; i < page_frame; i++) // 來回巡page_frame個
        {
            if (page_string[turn_LRU] == frame_LRU[i]) // 相同的話
            {
                write_position--;
                for (k = i; k < write_position; k++) // 遞進 stack 前移
                {
                    frame_LRU[k] = frame_LRU[k + 1];
                }
                frame_LRU[write_position] = page_string[turn_LRU]; // 最新使用 放stack末
                write_position++;
                printf("          "); // 將指針移回最末端
                break;
            }

            if (i == (page_frame - 1))
            {
                printf(" [%d f]    ", page_string[turn_LRU]);

                LRU_fault++;
                if (write_position != page_frame)
                {
                    frame_LRU[write_position] = page_string[turn_LRU];
                    write_position++;
                }
                else
                {
                    for (k = 0; k < (page_frame - 1); k++) // 前移
                    {
                        frame_LRU[k] = frame_LRU[k + 1];
                    }
                    frame_LRU[page_frame - 1] = page_string[turn_LRU]; // 放末位
                }
            }
        }
        printfunction(frame_LRU, page_frame);
        turn_LRU++;
    }

    printf("\nLRU page fault = %d\n\n", LRU_fault);
}

void OPT(int *page_string, int page_frame)
{

    printpage_string(page_string);
    int frame_OPT[page_frame];
    for (int i = 0; i < page_frame; i++)
    {
        frame_OPT[i] = -1;
    }

    int OPT_fault = 0;
    int turn_OPT = 0;       // number of page input
    int write_position = 0; // 插入值的地方
    // int k;
    int use_ptr = 0;

    while (turn_OPT < MAX_LENGHT)
    {
        for (int i = 0; i < page_frame; i++) // 來回巡三個
        {
            if (page_string[turn_OPT] == frame_OPT[i])
            {
                printf("          ");
                break;
            }

            if (i == (page_frame - 1))
            {

                printf(" [%d f]    ", page_string[turn_OPT]);

                OPT_fault++;
                if (OPT_fault <= page_frame)
                {
                    frame_OPT[OPT_fault - 1] = page_string[turn_OPT];
                    break;
                }

                int pos = 0;
                int max = -1;
                for (int j = 0; j < page_frame; j++) // 3 個  // 找最遠的
                {

                    int count = -1;
                    int flag = 0;

                    for (int k = turn_OPT; k < MAX_LENGHT; k++)
                    {

                        count++;
                        if (page_string[k] == frame_OPT[j])
                        {

                            if (count > max)
                            {
                                pos = j;
                                max = count;
                            }
                            flag = 1;

                            break;
                        }
                    }

                    if (flag == 0)
                    {
                        pos = j;
                        max = MAX_LENGHT + 10;
                        break;
                    }
                }

                frame_OPT[pos] = page_string[turn_OPT];
            }
        }
        printfunction(frame_OPT, page_frame);
        turn_OPT++;
    }

    printf("\nOPT page fault = %d\n\n", OPT_fault);
}

int main(int argc, char *argv[])
{
    // 先寫死
    // int page_string[MAX_LENGHT] = {1, 2, 3, 4, 5, 3, 4, 1, 5, 6, 7, 8, 7, 8, 9, 7, 8, 9, 6, 5, 4, 3, 4, 2, 7, 8};

    int input = 0;
    if (argc == 1)
    {
        printf("para error!\n");
        return 0;
    }
    else
    {
        input = atoi(argv[1]);

        if ((input < 0))
        {
            printf("\nEnter valid starting position of page frame: !");
            return 0;
        }
    }

    int page_frame = 0;
    page_frame = input;

    int page_string[MAX_LENGHT];
    srand(time(NULL));
    //	int random;
    int i;
    for (i = 0; i < MAX_LENGHT; i++)
    {
        page_string[i] = rand() % 10;
    }
    printf("page reference string is :\n");
    printfunction(page_string, MAX_LENGHT);

    FIFO(page_string, page_frame);
    LRU(page_string, page_frame);
    OPT(page_string, page_frame);

    return 0;
}
