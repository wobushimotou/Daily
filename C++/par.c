int main()
{
    int i = 0;
    /* int i = 0; */

    /* int n = 0; */
    /* n = i++; */
    /* n = ++i; */

    volatile int n = 0;
    n = i++;
    n = ++i;

    return 0;
}

