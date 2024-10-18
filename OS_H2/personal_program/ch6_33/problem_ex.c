#define MAX_RESOUCRES 5

int available_resources = MAX_RESOUCRES;

int decrease_count(int count)
{
    if (available_resources < count)
        return -1;
    else
    {
        available_resources -= count;
        return 0;
    }
}
int increase_count(int count)
{
    available_resources += count;
    return 0;
}