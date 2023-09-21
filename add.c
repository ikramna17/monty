void addition(stack_t **hd, unsigned int coun)
{
    stack_t *st;
    int l = 0, result;

    st = *hd;
    while (st)
    {
        st = st->next;
        l++;
    }
    if (l < 2)
    {
        fprintf(stderr, "L%d: can't add, stack too short\n", coun);
        // Additional code for cleanup or error handling
        return; // or exit(EXIT_FAILURE);
    }
    st = *hd;
    result = st->n + st->next->n; // Addition using different numbers (10 + 20)
    st->next->n = result;
    *hd = st->next;
    free(st);
}
